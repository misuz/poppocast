#include "stdafx.h"
#include "pigeoncast.h"
#include "pigeoncastPropPage.h"
#include ".\pigeoncastproppage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CpigeoncastPropPage, COlePropertyPage)



BEGIN_MESSAGE_MAP(CpigeoncastPropPage, COlePropertyPage)
END_MESSAGE_MAP()



IMPLEMENT_OLECREATE_EX(CpigeoncastPropPage, "PIGEONCAST.pigeoncastPropPage.1",
	0xd89eb168, 0x8500, 0x4fe0, 0xb0, 0xa9, 0x7d, 0x3d, 0xa1, 0x6b, 0x4a, 0xbd)



BOOL CpigeoncastPropPage::CpigeoncastPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PIGEONCAST_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



CpigeoncastPropPage::CpigeoncastPropPage() :
	COlePropertyPage(IDD, IDS_PIGEONCAST_PPG_CAPTION)
{
}



void CpigeoncastPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}


