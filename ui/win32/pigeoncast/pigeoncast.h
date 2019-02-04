// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#pragma once

#if !defined( __AFXCTL_H__ )
#error you must includeÅA'afxctl.h'
#endif

#include "resource.h"


class CpigeoncastApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
	CWnd*	m_pMainDlg;
};


extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

extern CpigeoncastApp theApp;
