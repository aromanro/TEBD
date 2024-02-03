#pragma once


// COptionsPropertySheet

class COptionsPropertySheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(COptionsPropertySheet)
	DECLARE_MESSAGE_MAP()
public:
	COptionsPropertySheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	COptionsPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	~COptionsPropertySheet() override;

private:
	HICON hIcon;

	BOOL OnInitDialog() override;
};


