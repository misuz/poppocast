// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#pragma once

class CpigeoncastCtrl : public COleControl
{
	DECLARE_DYNCREATE(CpigeoncastCtrl)

public:
	CpigeoncastCtrl();
	CString		m_strSrcURL;// <PARAM NAME="SRC" VALUE="peercast://`">
	CString		m_strStreamID; // 32 bytes ascii characters.

public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

protected:
	~CpigeoncastCtrl();

	DECLARE_OLECREATE_EX(CpigeoncastCtrl) 
	DECLARE_OLETYPELIB(CpigeoncastCtrl)  
	DECLARE_PROPPAGEIDS(CpigeoncastCtrl)
	DECLARE_OLECTLTYPE(CpigeoncastCtrl)

	DECLARE_MESSAGE_MAP()

	DECLARE_DISPATCH_MAP()

	DECLARE_EVENT_MAP()

public:
	enum {
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

