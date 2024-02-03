#pragma once

#include "NumberEdit.h"

// CRealTimeHamiltonianPropertyPage dialog

class CRealTimeHamiltonianPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CRealTimeHamiltonianPropertyPage)
	DECLARE_MESSAGE_MAP()
public:
	CRealTimeHamiltonianPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REAL_TIME_HAMILTONIAN_PROPPAGE };
#endif

protected:
	double JxEvol;
	double JyEvol;
	double JzEvol;

	double BxEvol;
	double BzEvol;

	CNumberEdit JxEvolEdit;
	CNumberEdit JyEvolEdit;
	CNumberEdit JzEvolEdit;

	CNumberEdit BxEvolEdit;
	CNumberEdit BzEvolEdit;
	
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	void ApplyValues();
	BOOL OnApply() override;
	afx_msg void OnEnChangeEdit();
};
