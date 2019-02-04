// MainDlg.cpp
// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#include "stdafx.h"
#include <wininet.h>
#include <Winsock2.h>
#include "pigeoncast.h"
#include "MainDlg.h"
#include "PortForward.h" // port forwarding using UPnP framework.


IMPLEMENT_DYNAMIC(CMainDlg, CDialog)
CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	m_pParentCtrl = NULL;	// parent ocx control.
}

CMainDlg::~CMainDlg()
{
	m_pParentCtrl = NULL;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_wmp); // Windows Media Player ocx control.
	DDX_Control(pDX, IDC_STATIC_MSG, m_staticMsg); // a static control for showing error messages.
}

/* message map */
BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	// make portforwarding on your UPnP router.
	char hostname[MAX_COMPUTERNAME_LENGTH + 1];
	
	if (gethostname(hostname, MAX_COMPUTERNAME_LENGTH) == 0) {

		TRACE(_T("hostname = %s\n"), hostname );

		PHOSTENT he = gethostbyname(hostname);
		if( ! he) {
			TRACE(_T("Obtaining local IP address failed.\n"));
		}
		else {
			CPortForward	pf;
			IN_ADDR       ip;

			memcpy(&ip, he->h_addr, 4);
			pf.SetupForward('t', 7144, 7144,		// TCP/7144 static routing.
				inet_ntoa(ip), _T("PigeonTV") );
		}
	}


	// see http://msdn.microsoft.com/en-us/library/aa387927.aspx for further information of WMP controls.
	m_wmp.put_uiMode( _T("mini") );
	m_wmp.put_enableContextMenu( FALSE );
	m_wmp.put_windowlessVideo( FALSE );

	// delay of start playing.
	SetTimer(TMID_STARTWMP, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
}

// ActiveX re-sizing
void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// don't use IsWindow() for WMP controls because it always returns NULL.
	if(m_wmp.GetControlUnknown() != NULL)
		m_wmp.SetWindowPos(NULL, 0,0,cx,cy, SWP_NOZORDER);
}

// timer messages
void CMainDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == TMID_STARTWMP) {
		KillTimer(TMID_STARTWMP);
		if (m_pParentCtrl!=NULL && !m_pParentCtrl->m_strStreamID.IsEmpty()) {
			CString tmp;
			tmp.Format( _T("http://localhost:7144/stream/%s.wmv") , m_pParentCtrl->m_strStreamID);
			m_wmp.put_URL(tmp);
		}
		else {
			// fatal error.
			m_wmp.put_uiMode( _T("invisible") );
			m_staticMsg.SetWindowText( _T("Bad SRC parameter in OBJECT tag. Check your HTML code."));
			m_staticMsg.ShowWindow(SW_SHOW);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMainDlg::OnDestroy()
{
	CDialog::OnDestroy();

	CPortForward	pf;
	pf.RemoveForward('t', 7144);
}
