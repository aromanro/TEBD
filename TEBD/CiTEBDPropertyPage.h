#pragma once

#include "NumberEdit.h"

// CiTEBDPropertyPage dialog

class CiTEBDPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CiTEBDPropertyPage)

public:
	CiTEBDPropertyPage();
	virtual ~CiTEBDPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEBD_PROPPAGE };
#endif

protected:
	int chi;
	double maxTime;

	int StartState;
	int MeasureOp;

	CNumberEdit maxTimeEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedRadio();
};
