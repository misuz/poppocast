// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//

#include "StdAfx.h"
#include "simple.h"
#include <shlobj.h> //SHGetSpecialFolderPath

// PeerCast globals

static int currNotify=0;
String iniFileName;
int		seenNewVersionTime=0;
ChanInfo chanInfo;
bool chanInfoIsRelayed;
GnuID	lastPlayID;

// ---------------------------------
Sys * APICALL MyPeercastInst::createSys()
{
	return new WSys(NULL);
}
// ---------------------------------
const char * APICALL MyPeercastApp ::getIniFilename()
{
	return iniFileName.cstr();
}

// ---------------------------------
const char *APICALL MyPeercastApp ::getClientTypeOS() 
{
	return PCX_OS_WIN32;
}

// ---------------------------------
const char *APICALL MyPeercastApp ::getPath() 
{
	static char pszAppdataPath [MAX_PATH + 1] = {0};

	if (! pszAppdataPath[0]) {
		if (! SHGetSpecialFolderPath(NULL, (LPTSTR)pszAppdataPath, CSIDL_APPDATA , TRUE)) {
			strcpy(pszAppdataPath, ".\\");
		}
		else {
			strcat(pszAppdataPath, "\\");
		}
	}
	return pszAppdataPath;
}

/*
** start peercast instance
*/
void run_pigeoncast(char* chanURL)
{
	const char* path;

	peercastInst = new MyPeercastInst();
	peercastApp = new MyPeercastApp();
	path = peercastApp->getPath();
	iniFileName.set( path );
	iniFileName.append(_T("PoppoCastTV.ini"));

	peercastInst->init();

	if (chanURL) {
		ChanInfo info;
		servMgr->procConnectArgs(chanURL,info);
		chanMgr->findAndPlayChannel(info,true);
	}
}


void quit_pigeoncast(void)
{
	peercastInst->saveSettings();
	peercastInst->quit();
	Sleep(1000); // wait for quitting thread
}

