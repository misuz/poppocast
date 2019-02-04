// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//
#pragma once
#include "ocx1.h"

#include "pigeoncastCtrl.h"
#include "afxwin.h"


class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);
	virtual ~CMainDlg();

	CpigeoncastCtrl* m_pParentCtrl;

	enum { IDD = IDD_MAINDLG };
	enum { TMID_STARTWMP = 1001 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	COcx1 m_wmp;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	CStatic m_staticMsg;
	afx_msg void OnDestroy();
};
