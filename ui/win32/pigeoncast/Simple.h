// pigeoncast.ocx ActiveX control based on Peercast for html embedding WMV streaming video.
// M.Suzawa Grid Solutions Inc.
// see http://www.peercast.org/ for further information.
//
#ifndef __SIMPLECASTSERV_H_
#define __SIMPLECASTSERV_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "stdafx.h"
#include <windows.h>

#include "channel.h"
#include "servent.h"
#include "servmgr.h"
#include "win32/wsys.h"
#include "peercast.h"

// ---------------------------------
class MyPeercastInst : public PeercastInstance
{
public:
	virtual Sys * APICALL createSys();
};
// ---------------------------------
class MyPeercastApp : public PeercastApplication
{
public:
	MyPeercastApp ()
	{
	}

	virtual const char * APICALL getIniFilename();
	virtual const char * APICALL getClientTypeOS();
	virtual const char * APICALL getPath();

};

void run_pigeoncast(char* chanURL);
void quit_pigeoncast(void);


#endif

