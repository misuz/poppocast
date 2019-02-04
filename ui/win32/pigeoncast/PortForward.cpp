// How to use:
//	 #include "PortForward.h"
//   CPortForward portforward
//	 portforward.SetupForward('t' or 'u', int externalport, int internalport, LPCTSTR ipaddress, LPCTSTR appname);
//
//  This requires Windows 2003 Server Platform SDK (or Windows XP SP2 SDK)

#include "stdafx.h"
#include "bstr.h"
#include "WindowsFirewall.h"
#include "PortForward.h"

CPortForward::CPortForward() {

	m_pNat        = NULL;
	m_pCollection = NULL;
	m_pMapping    = NULL;
}

CPortForward::~CPortForward() {

	if (m_pMapping)    { m_pMapping->Release();    m_pMapping    = NULL; }
	if (m_pCollection) { m_pCollection->Release(); m_pCollection = NULL; }
	if (m_pNat)        { m_pNat->Release();        m_pNat        = NULL; }
}

bool CPortForward::SetupForward(char protocol, int externalport, int internalport, LPCTSTR ipaddress, LPCTSTR name)
{
	// Enable the UPnP service in Windows Firewall
	CWindowsFirewall firewall;
	firewall.SetupService(NET_FW_SERVICE_UPNP);

	// Connect to the COM object, and have it begin talking UPnP to the router
	if (!Access()) return false;

	// Remove any forward the router has for the given protocol and port
	Remove(protocol, externalport); // Even if remove fails, we still want to try to add

	// Add a fresh port mapping with the right name and a checked box
	if (!Add(protocol, externalport, internalport, ipaddress, name)) return false;

	// Everything worked
	return true;
}

bool CPortForward::RemoveForward(char protocol, int externalport)
{

	// Enable the UPnP service in Windows Firewall
	CWindowsFirewall firewall;
	firewall.SetupService(NET_FW_SERVICE_UPNP);

	// Connect to the COM object, and have it begin talking UPnP to the router
	if (!Access()) return false;

	// Remove any forward the router has for the given protocol and port
	return Remove(protocol, externalport);
}

// Get access to the COM objects
// Returns true if it works, false if there was an error
bool CPortForward::Access() {

	// Initialize COM itself so this thread can use it
	HRESULT result = CoInitialize(NULL); // Must be NULL
	if (FAILED(result)) TRACE("PortForward::Access CoInitialize failed");
	if (FAILED(result)) return false;

	// Access the IUPnPNAT COM interface, has Windows send UPnP messages to the NAT router
	result = CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&m_pNat);
	if (FAILED(result)) TRACE("PortForward::Access CoCreateInstance IUPnPNAT failed");
	else if (!m_pNat)      TRACE("PortForward::Access CoCreateInstance succeeded, but left Nat null");
	if (FAILED(result) || !m_pNat) return false;

	// Get the collection of forwarded ports from it, has Windows send UPnP messages to the NAT router
	result = m_pNat->get_StaticPortMappingCollection(&m_pCollection); // Won't work if the NAT has UPnP turned off
	if (FAILED(result))   TRACE("PortForward::Access m_pNat->get_StaticPortMappingCollection failed");
	else if (!m_pCollection) TRACE("PortForward::Access m_pNat->get_StaticPortMappingCollection succeeded, but left Collection null");
	if (FAILED(result) || !m_pCollection) return false; // Frequently, result is S_OK but Collection is null

	// Everything worked
	return true;
}

// Takes a protocol 't' for TCP or 'u' for UDP, the ports to forward externally and internally, and the program name and description
// Talks UPnP to the router to setup port forwarding
// Returns false if there was an error
bool CPortForward::Add(char protocol, int externalport, int internalport, LPCTSTR ipaddress, LPCTSTR name) {

	// Make a local BSTR with the protocol described in text
	Beaster p;
	if (protocol == 'u') p.Set("UDP");
	else                 p.Set("TCP");

	// Express the name and description as BSTRs
	Beaster i(ipaddress);
	Beaster n(name);

	// Have Windows send UPnP messages to the NAT router to get it to forward a port
	if (m_pMapping) { m_pMapping->Release(); m_pMapping = NULL; } // Reuse the mapping interface pointer
	HRESULT result = m_pCollection->Add( // Create a new port mapping, and add it to the collection
		externalport, // The port to forward
		p.m_buf,          // The protocol as the text "TCP" or "UDP" in a BSTR
		internalport, // This computer's internal LAN port to forward to, like 192.168.1.100:internalport
		i.m_buf,          // Internal IP address to forward to, like "192.168.1.100"
		true,         // True to start forwarding now
		n.m_buf,          // Description text the router can show in its Web configuration interface
		&m_pMapping);    // Access to the IStaticPortMapping interface, if this works
	if (FAILED(result)) TRACE("PortForward::Add Collection->Add failed");
	else if (!m_pMapping)  TRACE("PortForward::Add Collection->Add succeeded, but left Mapping null");
	if (FAILED(result) || !m_pMapping) return false;
	return true;
}

// Takes a protocol 't' for TCP or 'u' for UDP, and a port being forwarded
// Talks UPnP to the router to remove the forwarding
// Returns false if there was an error
bool CPortForward::Remove(char protocol, int externalport) {

	// Make a local BSTR with the protocol described in text
	Beaster b;
	if (protocol == 'u') b.Set("UDP");
	else                 b.Set("TCP");

	// Have Windows send UPnP messages to the NAT router to get it to stop forwarding a port
	HRESULT result = m_pCollection->Remove( // Remove the specified port mapping from the collection
		externalport,                    // The port being forwarded
		b.m_buf);                            // The protocol as the text "TCP" or "UDP" in a BSTR
	if (FAILED(result)) TRACE("PortForward::Remove Collection->Remove failed");
	if (FAILED(result)) return false;    // Returns S_OK even if there was nothing there to remove
	return true;
}
