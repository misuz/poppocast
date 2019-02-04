#pragma once

#include <netfw.h>

class CWindowsFirewall
{
public:
	CWindowsFirewall();
	~CWindowsFirewall();
	bool SetupService(NET_FW_SERVICE_TYPE service);
	bool SetupProgram(LPCTSTR path, LPCTSTR name);
	bool Access();
	bool IsProgramListed(LPCTSTR path, bool *listed);
	bool IsServiceEnabled(NET_FW_SERVICE_TYPE service, bool *enabled);
	bool IsProgramEnabled(LPCTSTR path, bool *enabled);
	bool AddProgram(LPCTSTR path, LPCTSTR name);
	bool EnableService(NET_FW_SERVICE_TYPE service);
	bool EnableProgram(LPCTSTR path);


protected:
	// COM interfaces accessed with the object
    INetFwMgr                    *m_pManager;
    INetFwPolicy                 *m_pPolicy;
	INetFwProfile                *m_pProfile;
	INetFwServices               *m_pServiceList;
	INetFwAuthorizedApplications *m_pProgramList;
    INetFwOpenPorts              *m_pPortList;

	// COM interfaces accessed in methods
	INetFwService               *m_pService;
	INetFwAuthorizedApplication *m_pProgram;
    INetFwOpenPort              *m_pPort;
};
