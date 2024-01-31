#pragma once

#include "NumberEdit.h"

// CiTEBDPropertyPage dialog

class CiTEBDPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CiTEBDPropertyPage)
	DECLARE_MESSAGE_MAP()
public:
	CiTEBDPropertyPage();
	~CiTEBDPropertyPage() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEBD_PROPPAGE };
#endif

private:
	int chi;
	double maxTime;

	int StartState;
	int MeasureOp;

	CNumberEdit maxTimeEdit;

	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	void ApplyValues();
	BOOL OnApply() override;
	BOOL OnInitDialog() override;
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedRadio();
};
