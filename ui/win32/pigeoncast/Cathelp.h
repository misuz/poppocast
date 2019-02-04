// ActiveX marking as a 'safe' control.
// see http://support.microsoft.com/kb/161873/ja
// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#ifndef __COMCAT_H__
#define __COMCAT_H__

#include "stdafx.h"
#include <comcat.h>

// Helper function to create a component category and associated
// description
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);

// Helper function to register a CLSID as belonging to a component
// category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

#endif
