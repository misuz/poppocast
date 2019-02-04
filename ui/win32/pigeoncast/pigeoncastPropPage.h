#pragma once
#include "afxwin.h"


class CpigeoncastPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CpigeoncastPropPage)
	DECLARE_OLECREATE_EX(CpigeoncastPropPage)

public:
	CpigeoncastPropPage();

	enum { IDD = IDD_PROPPAGE_PIGEONCAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

protected:
	DECLARE_MESSAGE_MAP()
public:
};

