// pigeoncast.cpp : CpigeoncastApp
// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#include "stdafx.h"
#include "pigeoncast.h"

#ifdef _DEBUG 
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////
// marking this ocx as 'Safe' control.
#include "CatHelp.h"

const CATID CATID_SafeForScripting     =
{0x7dd95801,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};
const CATID CATID_SafeForInitializing  =
{0x7dd95802,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};

// see pigeonastCtrl.cpp
// CLSID: 88C9CFCF-362D-4DE4-929C-2245C38B5BB4

const GUID CDECL BASED_CODE _ctlid =
{ 0x88C9CFCF, 0x362D, 0x4DE4,
        { 0x92, 0x9c, 0x22, 0x45, 0xc3, 0x8b, 0x5b, 0xb4 } };

////////////////////////////////////////////////////////////



CpigeoncastApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x24183123, 0x9083, 0x4EDB, { 0xA4, 0x72, 0x4B, 0xC4, 0xBF, 0x4E, 0xF7, 0x9E } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CpigeoncastApp::InitInstance - DLL initialization

BOOL CpigeoncastApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		AfxEnableControlContainer(); // to embed WMP ocx control inside this ocx.
		m_pMainDlg = NULL;
	}

	return bInit;
}



// CpigeoncastApp::ExitInstance - DLL de-initialization

int CpigeoncastApp::ExitInstance()
{
	return COleControlModule::ExitInstance();
}


///////////////////////////////////////////////////////////////
// customized DllRegisterServer/DllUnregisterServer
//   to be recognized it as a 'Safe' control.

STDAPI DllRegisterServer(void)
{
    AFX_MANAGE_STATE(_afxModuleAddrThis);

    if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
        return ResultFromScode(SELFREG_E_TYPELIB);

    if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
        return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( CreateComponentCategory(
            CATID_SafeForScripting,
            L"Controls that are safely scriptable") ))
        return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( CreateComponentCategory(
            CATID_SafeForInitializing,
            L"Controls safely initializable from persistent data") ))
        return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( RegisterCLSIDInCategory(
            _ctlid, CATID_SafeForScripting) ))
        return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( RegisterCLSIDInCategory(
            _ctlid, CATID_SafeForInitializing) ))
        return ResultFromScode(SELFREG_E_CLASS);

    return NOERROR;
}

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


///////////////////////////////////////////////////////////////