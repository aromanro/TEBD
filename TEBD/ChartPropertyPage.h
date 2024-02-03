#pragma once

#include "NumberEdit.h"

// CChartPropertyPage dialog

class CChartPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CChartPropertyPage)

public:
	CChartPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_PROPPAGE };
#endif

private:
	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double minY;
	double maxY;

	CNumberEdit minYEdit;
	CNumberEdit maxYEdit;

	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


	void ApplyValues();
	BOOL OnApply() override;
	afx_msg void OnEnChangeEdit();
};
