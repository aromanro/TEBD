#pragma once

#include "NumberEdit.h"

// CRealTimeHamiltonianPropertyPage dialog

class CRealTimeHamiltonianPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CRealTimeHamiltonianPropertyPage)

public:
	CRealTimeHamiltonianPropertyPage();
	virtual ~CRealTimeHamiltonianPropertyPage();

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
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEdit();
};
