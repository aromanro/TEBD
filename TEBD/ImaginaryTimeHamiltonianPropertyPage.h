#pragma once

#include "NumberEdit.h"

// CImaginaryTimeHamiltonianPropertyPage dialog

class CImaginaryTimeHamiltonianPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CImaginaryTimeHamiltonianPropertyPage)

public:
	CImaginaryTimeHamiltonianPropertyPage();
	virtual ~CImaginaryTimeHamiltonianPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGINARY_HAMILTONIAN_PROPPAGE };
#endif

protected:
	double JxStart;
	double JyStart;
	double JzStart;

	double BxStart;
	double BzStart;

	CNumberEdit JxStartEdit;
	CNumberEdit JyStartEdit;
	CNumberEdit JzStartEdit;

	CNumberEdit BxStartEdit;
	CNumberEdit BzStartEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEdit();
};
