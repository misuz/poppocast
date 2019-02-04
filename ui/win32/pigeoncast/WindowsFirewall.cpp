#include "stdafx.h"
#include "bstr.h"
#include "WindowsFirewall.h"

CWindowsFirewall::CWindowsFirewall() {

	m_pManager     = NULL;
	m_pPolicy      = NULL;
	m_pProfile     = NULL;
	m_pServiceList = NULL;
	m_pProgramList = NULL;
	m_pPortList    = NULL;
	m_pService     = NULL;
	m_pProgram     = NULL;
	m_pPort        = NULL;
}

CWindowsFirewall::~CWindowsFirewall() {

	if (m_pPort)        { m_pPort->Release();        m_pPort        = NULL; }
	if (m_pProgram)     { m_pProgram->Release();     m_pProgram     = NULL; }
	if (m_pService)     { m_pService->Release();     m_pService     = NULL; }
	if (m_pPortList)    { m_pPortList->Release();    m_pPortList    = NULL; }
	if (m_pProgramList) { m_pProgramList->Release(); m_pProgramList = NULL; }
	if (m_pServiceList) { m_pServiceList->Release(); m_pServiceList = NULL; }
	if (m_pProfile)     { m_pProfile->Release();     m_pProfile     = NULL; }
	if (m_pPolicy)      { m_pPolicy->Release();      m_pPolicy      = NULL; }
	if (m_pManager)     { m_pManager->Release();     m_pManager     = NULL; }
}

bool CWindowsFirewall::SetupService(NET_FW_SERVICE_TYPE service) {

	if (! m_pManager)
		if (! Access()) return false;

	bool enabled;
	if (!IsServiceEnabled(service, &enabled)) return false;
	if (!enabled)
	{
		// Check its checkbox
		if (!EnableService(service)) return false;
	}

	return true;
}

bool CWindowsFirewall::SetupProgram(LPCTSTR path, LPCTSTR name) {

	// Make sure the COM interfaces have been accessed
	if (!m_pManager) if (!Access()) return false;

	// If the program isn't on the Windows Firewall exceptions list
	bool listed, enabled;
	if (!IsProgramListed(path, &listed)) return false;
	if (!listed) {

		// Add it to the list with a checked checkbox
		if (!AddProgram(path, name)) return false;
	}

	// If the program is on the list, but its checkbox isn't checked
	if (!IsProgramEnabled(path, &enabled)) return false;
	if (!enabled) {

		// Check the checkbox
		if (!EnableProgram(path)) return false;
	}

	// The program is listed and checked
	return true;
}

// Get access to the COM objects
bool CWindowsFirewall::Access() {

	// Initialize COM itself so this thread can use it
	HRESULT result = CoInitialize(NULL); // Must be NULL
	if (FAILED(result)) return false;

	// Create an instance of the firewall settings manager
	result = CoCreateInstance(__uuidof(NetFwMgr), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwMgr), (void **)&m_pManager);
	if (FAILED(result)) TRACE("WindowsFirewall CoCreateInstance INetFwMgr failed.");
	else if (!m_pManager)  TRACE("WindowsFirewall CoCreateInstance INetFwMgr succeeded. m_pManager is NULL.");
	if (FAILED(result) || !m_pManager) return false;

	// Retrieve the local firewall policy
	result = m_pManager->get_LocalPolicy(&m_pPolicy);
	if (FAILED(result)) TRACE("WindowsFirewall get_LocalPolicy failed.");
	else if (!m_pPolicy)   TRACE("WindowsFirewall get_LocalPolicy succeeded. m_pPolicy is NULL.");
	if (FAILED(result) || !m_pPolicy) return false;

	// Retrieve the firewall profile currently in effect
	result = m_pPolicy->get_CurrentProfile(&m_pProfile);
	if (FAILED(result)) TRACE("WindowsFirewall get_CurrentProfile failed.");
	else if (!m_pProfile)  TRACE("WindowsFirewall get_CurrentProfile succeeded. m_pPolicy is NULL.");
	if (FAILED(result) || !m_pProfile) return false;

	// Retrieve the allowed services collection
	result = m_pProfile->get_Services(&m_pServiceList);
	if (FAILED(result))    TRACE("WindowsFirewall get_Services failed.");
	else if (!m_pServiceList) TRACE("WindowsFirewall::Access get_Services succeeded. m_pServiceList is NULL.");
	if (FAILED(result) || !m_pServiceList) return false;

	// Retrieve the authorized application collection
	result = m_pProfile->get_AuthorizedApplications(&m_pProgramList);
	if (FAILED(result))    TRACE("WindowsFirewall get_AuthorizedApplications failed.");
	else if (!m_pProgramList) TRACE("WindowsFirewall get_AuthorizedApplications succeeded. m_pProgramList is NULL.");
	if (FAILED(result) || !m_pProgramList) return false;

	// Retrieve the globally open ports collection
	result = m_pProfile->get_GloballyOpenPorts(&m_pPortList);
	if (FAILED(result)) TRACE("WindowsFirewall get_GloballyOpenPorts failed.");
	else if (!m_pPortList) TRACE("WindowsFirewall get_GloballyOpenPorts succeeded. m_pPortList is NULL.");
	if (FAILED(result) || !m_pPortList) return false;

	// Everything worked
	return true;
}

// Takes a program path and file name, like "C:\Folder\Program.exe"
// Determines if it's listed in Windows Firewall
// Returns true if it works, and writes the answer in listed
bool CWindowsFirewall::IsProgramListed(LPCTSTR path, bool *listed) {

	// Look for the program in the list
	if (m_pProgram) { m_pProgram->Release(); m_pProgram = NULL; }
	Beaster p(path); // Express the name as a BSTR
	HRESULT result = m_pProgramList->Item(p.m_buf, &m_pProgram); // Try to get the interface for the program with the given name
	if (SUCCEEDED(result)) {

		// The program is in the list
		*listed = true;
		return true;

	// The ProgramList->Item call failed
	} else {

		// The error is not found
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {

			// The program is not in the list
			*listed = false;
			return true;

		// Some other error occurred
		} else {

			// Report it
			TRACE("WindowsFirewall m_pProgramList->Item failed with an error other than not found");
			return false;
		}
	}
}

// Takes a service type, like NET_FW_SERVICE_UPNP
// Determines if the listing for that service in Windows Firewall is checked or unchecked
// Returns true if it works, and writes the answer in enabled
bool CWindowsFirewall::IsServiceEnabled(NET_FW_SERVICE_TYPE service, bool *enabled) {

	// Look for the service in the list
	if (m_pService) { m_pService->Release(); m_pService = NULL; }
	HRESULT result = m_pServiceList->Item(service, &m_pService);
	if (FAILED(result)) TRACE("WindowsFirewall m_pServiceList->Item failed");
	if (FAILED(result)) return false; // Services can't be removed from the list

	// Find out if the service is enabled
	VARIANT_BOOL v;
	result = m_pService->get_Enabled(&v);
	if (FAILED(result)) TRACE("WindowsFirewall Service->get_Enabled failed");
	if (FAILED(result)) return false;
	if (v == VARIANT_FALSE) {

		// The service is on the list, but the checkbox next to it is cleared
		*enabled = false;
		return true;

	} else {

		// The service is on the list and the checkbox is checked
		*enabled = true;
		return true;
	}
}

// Takes a program path and file name like "C:\Folder\Program.exe"
// Determines if the listing for that program in Windows Firewall is checked or unchecked
// Returns true if it works, and writes the answer in enabled
bool CWindowsFirewall::IsProgramEnabled(LPCTSTR path, bool *enabled) {

	// First, make sure the program is listed
	bool listed;
	if (!IsProgramListed(path, &listed)) return false; // This sets the Program interface we can use here
	if (!listed) return false; // The program isn't in the list at all

	// Find out if the program is enabled
	VARIANT_BOOL v;
	HRESULT result = m_pProgram->get_Enabled(&v);
	if (FAILED(result)) TRACE("WindowsFirewall Program->get_Enabled failed");
	if (FAILED(result)) return false;
	if (v == VARIANT_FALSE) {

		// The program is on the list, but the checkbox next to it is cleared
		*enabled = false;
		return true;

	} else {

		// The program is on the list and the checkbox is checked
		*enabled = true;
		return true;
	}
}

// Takes a path and file name like "C:\Folder\Program.exe" and a name like "My Program"
// Lists and checks the program on Windows Firewall, so now it can listed on a socket without a warning popping up
// Returns false on error
bool CWindowsFirewall::AddProgram(LPCTSTR path, LPCTSTR name) {

	// Create an instance of an authorized application, we'll use this to add our new application
	if (m_pProgram) { m_pProgram->Release(); m_pProgram = NULL; }
	HRESULT result = CoCreateInstance(__uuidof(NetFwAuthorizedApplication), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(INetFwAuthorizedApplication), (void **)&m_pProgram);
	if (FAILED(result)) TRACE("WindowsFirewall CoCreateInstance INetFwAuthorizedApplication failed");
	if (FAILED(result)) return false;

	// Set the text
	Beaster p(path);                                 // Express the text as BSTRs
	result = m_pProgram->put_ProcessImageFileName(p.m_buf); // Set the process image file name
	if (FAILED(result)) TRACE("WindowsFirewall Program->put_ProcessImageFileName failed");
	if (FAILED(result)) return false;
	Beaster n(name);
	result = m_pProgram->put_Name(n.m_buf);                 // Set the program name
	if (FAILED(result)) TRACE("WindowsFirewall Program->put_Name failed");
	if (FAILED(result)) return false;

	// Get the program on the Windows Firewall accept list
	result = m_pProgramList->Add(m_pProgram); // Add the application to the collection
	if (FAILED(result)) TRACE("WindowsFirewall Program->Add failed");
	if (FAILED(result)) return false;
	return true;
}

// Takes a service type, like NET_FW_SERVICE_UPNP
// Checks the checkbox next to its listing in Windows Firewall
// Returns false on error
bool CWindowsFirewall::EnableService(NET_FW_SERVICE_TYPE service) {

	// Look for the service in the list
	if (m_pService) { m_pService->Release(); m_pService = NULL; }
	HRESULT result = m_pServiceList->Item(service, &m_pService);
	if (FAILED(result)) TRACE("WindowsFirewall ServiceList->Item failed");
	if (FAILED(result)) return false; // Services can't be removed from the list

	// Check the box next to the service
	VARIANT_BOOL v = true;
	result = m_pService->put_Enabled(v);
	if (FAILED(result)) TRACE("WindowsFirewall Service->put_Enabled failed");
	if (FAILED(result)) return false;
	return true;
}

// Takes a program path and file name like "C:\Folder\Program.exe"
// Checks the checkbox next to its listing in Windows Firewall
// Returns false on error
bool CWindowsFirewall::EnableProgram(LPCTSTR path) {

	// First, make sure the program is listed
	bool listed;
	if (!IsProgramListed(path, &listed)) return false; // This sets the Program interface we can use here
	if (!listed) return false; // The program isn't on the list at all

	// Check the box next to the program
	VARIANT_BOOL v = true;
	HRESULT result = m_pProgram->put_Enabled(v);
	if (FAILED(result)) TRACE("WindowsFirewall Program->put_Enabled failed");
	if (FAILED(result)) return false;
	return true;
}
