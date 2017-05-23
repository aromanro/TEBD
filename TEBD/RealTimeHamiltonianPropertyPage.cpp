// RealTimeHamiltonianPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "TEBD.h"
#include "RealTimeHamiltonianPropertyPage.h"
#include "afxdialogex.h"


// CRealTimeHamiltonianPropertyPage dialog

IMPLEMENT_DYNAMIC(CRealTimeHamiltonianPropertyPage, CMFCPropertyPage)

CRealTimeHamiltonianPropertyPage::CRealTimeHamiltonianPropertyPage()
	: CMFCPropertyPage(IDD_REAL_TIME_HAMILTONIAN_PROPPAGE)
{
	JxEvol = theApp.options.JxEvol;
	JyEvol = theApp.options.JyEvol;
	JzEvol = theApp.options.JzEvol;

	BxEvol = theApp.options.BxEvol;
	BzEvol = theApp.options.BzEvol;
}

CRealTimeHamiltonianPropertyPage::~CRealTimeHamiltonianPropertyPage()
{
}

void CRealTimeHamiltonianPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, JxEvolEdit);
	DDX_Control(pDX, IDC_EDIT2, JyEvolEdit);
	DDX_Control(pDX, IDC_EDIT3, JzEvolEdit);
	DDX_Control(pDX, IDC_EDIT4, BxEvolEdit);
	DDX_Control(pDX, IDC_EDIT5, BzEvolEdit);

	DDX_Text(pDX, IDC_EDIT1, JxEvol);
	DDX_Text(pDX, IDC_EDIT2, JyEvol);
	DDX_Text(pDX, IDC_EDIT3, JzEvol);
	DDX_Text(pDX, IDC_EDIT4, BxEvol);
	DDX_Text(pDX, IDC_EDIT5, BzEvol);
}


BEGIN_MESSAGE_MAP(CRealTimeHamiltonianPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CRealTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CRealTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, &CRealTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT4, &CRealTimeHamiltonianPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, &CRealTimeHamiltonianPropertyPage::OnEnChangeEdit)
END_MESSAGE_MAP()


// CRealTimeHamiltonianPropertyPage message handlers


void CRealTimeHamiltonianPropertyPage::ApplyValues()
{
	theApp.options.JxEvol = JxEvol;
	theApp.options.JyEvol = JyEvol;
	theApp.options.JzEvol = JzEvol;

	theApp.options.BxEvol = BxEvol;
	theApp.options.BzEvol = BzEvol;
	
	theApp.options.Save();
}





BOOL CRealTimeHamiltonianPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}


void CRealTimeHamiltonianPropertyPage::OnEnChangeEdit()
{
	SetModified();
}


