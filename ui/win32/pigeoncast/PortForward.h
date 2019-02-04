#pragma once

#include <natupnp.h>

class CPortForward
{
public:
	CPortForward();
	~CPortForward();
	bool SetupForward(char protocol, int externalport, int internalport, LPCTSTR ipaddress, LPCTSTR name);
	bool RemoveForward(char protocol, int externalport);

protected:
	// COM interfaces
	IUPnPNAT                     *m_pNat;
	IStaticPortMappingCollection *m_pCollection;
	IStaticPortMapping           *m_pMapping;

	bool Remove(char protocol, int externalport);
	bool Access();
	bool Add(char protocol, int externalport, int internalport, LPCTSTR ipaddress, LPCTSTR name);
};
