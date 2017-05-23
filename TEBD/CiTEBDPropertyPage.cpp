// CiTEBDPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "TEBD.h"
#include "CiTEBDPropertyPage.h"
#include "afxdialogex.h"


// CiTEBDPropertyPage dialog

IMPLEMENT_DYNAMIC(CiTEBDPropertyPage, CMFCPropertyPage)

CiTEBDPropertyPage::CiTEBDPropertyPage()
	: CMFCPropertyPage(IDD_ITEBD_PROPPAGE)
{
	chi = theApp.options.chi;
	maxTime = theApp.options.maxTime;

	StartState = theApp.options.StartState;
	MeasureOp = theApp.options.MeasureOp;
}

CiTEBDPropertyPage::~CiTEBDPropertyPage()
{
}

void CiTEBDPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, maxTimeEdit);

	DDX_Text(pDX, IDC_EDIT1, maxTime);
	DDX_Text(pDX, IDC_EDIT2, chi);

	DDX_Radio(pDX, IDC_RADIO1, StartState);
	DDX_Radio(pDX, IDC_RADIO4, MeasureOp);
}


BEGIN_MESSAGE_MAP(CiTEBDPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CiTEBDPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CiTEBDPropertyPage::OnEnChangeEdit)
	ON_BN_CLICKED(IDC_RADIO1, &CiTEBDPropertyPage::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CiTEBDPropertyPage::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO4, &CiTEBDPropertyPage::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO5, &CiTEBDPropertyPage::OnBnClickedRadio)
END_MESSAGE_MAP()


// CiTEBDPropertyPage message handlers


void CiTEBDPropertyPage::ApplyValues()
{
	theApp.options.chi = chi;
	theApp.options.maxTime = maxTime;

	theApp.options.StartState = StartState;
	theApp.options.MeasureOp = MeasureOp;

	theApp.options.Save();
}


BOOL CiTEBDPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}


BOOL CiTEBDPropertyPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CiTEBDPropertyPage::OnEnChangeEdit()
{
	SetModified();
}




void CiTEBDPropertyPage::OnBnClickedRadio()
{
	SetModified();
}

