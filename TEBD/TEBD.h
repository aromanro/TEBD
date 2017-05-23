
// TEBD.h : main header file for the TEBD application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib,"Gdiplus.lib")


#include "Options.h"

// CTEBDApp:
// See TEBD.cpp for the implementation of this class
//

class CTEBDApp : public CWinAppEx
{
public:
	CTEBDApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	Options options;

private:
	ULONG_PTR gdiplusToken;

public:
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CTEBDApp theApp;

