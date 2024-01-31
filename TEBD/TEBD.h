
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
	BOOL InitInstance() override;

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	Options options;

private:
	ULONG_PTR gdiplusToken;

	void PreLoadState() override;
	void LoadCustomState() override;
	void SaveCustomState() override;
	int ExitInstance() override;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTEBDApp theApp;

