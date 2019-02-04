// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#include "stdafx.h"
#include "pigeoncast.h"
#include "pigeoncastCtrl.h"
#include "pigeoncastPropPage.h"
#include "Simple.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CpigeoncastCtrl, COleControl)


BEGIN_MESSAGE_MAP(CpigeoncastCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()



BEGIN_DISPATCH_MAP(CpigeoncastCtrl, COleControl)
END_DISPATCH_MAP()


BEGIN_EVENT_MAP(CpigeoncastCtrl, COleControl)
END_EVENT_MAP()



BEGIN_PROPPAGEIDS(CpigeoncastCtrl, 1)
	PROPPAGEID(CpigeoncastPropPage::guid)
END_PROPPAGEIDS(CpigeoncastCtrl)



// the CLASS ID
// use this ID for <OBJECT clsid: >
IMPLEMENT_OLECREATE_EX(CpigeoncastCtrl, "PIGEONCAST.pigeoncastCtrl.1",
	0x88c9cfcf, 0x362d, 0x4de4, 0x92, 0x9c, 0x22, 0x45, 0xc3, 0x8b, 0x5b, 0xb4)


IMPLEMENT_OLETYPELIB(CpigeoncastCtrl, _tlid, _wVerMajor, _wVerMinor)


// Interface ID

const IID BASED_CODE IID_Dpigeoncast =
		{ 0xD8BC263B, 0xD805, 0x4C36, { 0xA9, 0xD3, 0x38, 0x1E, 0x41, 0x29, 0x19, 0x4F } };
const IID BASED_CODE IID_DpigeoncastEvents =
		{ 0x3A9ABC26, 0xDD9A, 0x42DD, { 0x8A, 0x8A, 0xE8, 0xFF, 0x11, 0xB3, 0x84, 0x58 } };


static const DWORD BASED_CODE _dwpigeoncastOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CpigeoncastCtrl, IDS_PIGEONCAST, _dwpigeoncastOleMisc)



BOOL CpigeoncastCtrl::CpigeoncastCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PIGEONCAST,
			IDB_PIGEONCAST,
			afxRegApartmentThreading,
			_dwpigeoncastOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CpigeoncastCtrl::CpigeoncastCtrl

CpigeoncastCtrl::CpigeoncastCtrl()
{
	InitializeIIDs(&IID_Dpigeoncast, &IID_DpigeoncastEvents);

}


CpigeoncastCtrl::~CpigeoncastCtrl()
{
	// stop peercasting.
	quit_pigeoncast();

	// destroy my dialog.
	if (theApp.m_pMainDlg) {
		if (::IsWindow(theApp.m_pMainDlg->m_hWnd)) theApp.m_pMainDlg->DestroyWindow();
		delete theApp.m_pMainDlg;
		theApp.m_pMainDlg = NULL;
	}
}


// window size and position adjusting.
void CpigeoncastCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	if (theApp.m_pMainDlg && ::IsWindow(theApp.m_pMainDlg->m_hWnd))
		theApp.m_pMainDlg->MoveWindow(&rcBounds);
}

// property exchange
void CpigeoncastCtrl::DoPropExchange(CPropExchange* pPX)
{
	CString tmp;
	char url [1024];
	
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);


	PX_String(pPX, _T("SRC"), m_strSrcURL);	// <PARAM NAME="SRC" VALUE="peercast://`">
	if (strncmp( _T("peercast://pls/"), m_strSrcURL, 15)==0) {
		tmp = m_strSrcURL.Mid(strlen(_T("peercast://")));
		tmp = tmp.Left(32); // fixed length?
		this->m_strStreamID =tmp;
	}
	else if (strncmp( _T("peercast://") , m_strSrcURL, 11)==0) {
		tmp = m_strSrcURL.Mid(strlen(_T("peercast://")));
		tmp = tmp.Left(32); // fixed length?
		this->m_strStreamID =tmp;
	}
	else
		return; // ERROR.
	
	// OK
	strncpy(url, m_strSrcURL, 1023);
	run_pigeoncast( url );
	// peercast://4439EF84DE244F967B529763C547BDD2.wmv/?tip=192.168.128.99:7144
}


void CpigeoncastCtrl::OnResetState()
{
	COleControl::OnResetState();
}


int CpigeoncastCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (theApp.m_pMainDlg) {
		// renew dialog.
		delete theApp.m_pMainDlg;
		theApp.m_pMainDlg = NULL;
	}
	CMainDlg* pDlg = new CMainDlg;
	if (! pDlg->Create(IDD_MAINDLG,this)) // CMainDlg::OnInitDialog() will called here.
		return -1;

	theApp.m_pMainDlg = (CWnd*) pDlg;
	pDlg->m_pParentCtrl = this;
	return 0;
}
