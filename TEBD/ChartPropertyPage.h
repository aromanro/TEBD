#pragma once

#include "NumberEdit.h"

// CChartPropertyPage dialog

class CChartPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CChartPropertyPage)

public:
	CChartPropertyPage();
	virtual ~CChartPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_PROPPAGE };
#endif

protected:
	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double minY;
	double maxY;

	CNumberEdit minYEdit;
	CNumberEdit maxYEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEdit();
};
