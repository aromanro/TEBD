// ImaginaryTimeHamiltonianPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "TEBD.h"
#include "ImaginaryTimeHamiltonianPropertyPage.h"
#include "afxdialogex.h"


// CImaginaryTimeHamiltonianPropertyPage dialog

IMPLEMENT_DYNAMIC(CImaginaryTimeHamiltonianPropertyPage, CMFCPropertyPage)

CImaginaryTimeHamiltonianPropertyPage::CImaginaryTimeHamiltonianPropertyPage()
	: CMFCPropertyPage(IDD_IMAGINARY_HAMILTONIAN_PROPPAGE)
{
	JxStart = theApp.options.JxStart;
	JyStart = theApp.options.JyStart;
	JzStart = theApp.options.JzStart;

	BxStart = theApp.options.BxStart;
	BzStart = theApp.options.BzStart;
}

CImaginaryTimeHamiltonianPropertyPage::~CImaginaryTimeHamiltonianPropertyPage()
{
}

void CImaginaryTimeHamiltonianPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, JxStartEdit);
	DDX_Control(pDX, IDC_EDIT2, JyStartEdit);
	DDX_Control(pDX, IDC_EDIT3, JzStartEdit);
	DDX_Control(pDX, IDC_EDIT4, BxStartEdit);
	DDX_Control(pDX, IDC_EDIT5, BzStartEdit);

	DDX_Text(pDX, IDC_EDIT1, JxStart);
	DDX_Text(pDX, IDC_EDIT2, JyStart);
	DDX_Text(pDX, IDC_EDIT3, JzStart);
	DDX_Text(pDX, IDC_EDIT4, BxStart);
	DDX_Text(pDX, IDC_EDIT5, BzStart);
}


BEGIN_MESSAGE_MAP(CImaginaryTimeHamiltonianPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, &CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT4, &CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, &CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit)
END_MESSAGE_MAP()


// CImaginaryTimeHamiltonianPropertyPage message handlers


void CImaginaryTimeHamiltonianPropertyPage::ApplyValues()
{
	theApp.options.JxStart = JxStart;
	theApp.options.JyStart = JyStart;
	theApp.options.JzStart = JzStart;

	theApp.options.BxStart = BxStart;
	theApp.options.BzStart = BzStart;
		
	theApp.options.Save();
}


BOOL CImaginaryTimeHamiltonianPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}





void CImaginaryTimeHamiltonianPropertyPage::OnEnChangeEdit()
{
	SetModified();
}


