// ChartPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "TEBD.h"
#include "ChartPropertyPage.h"
#include "afxdialogex.h"
#include "resource.h"

#include "MainFrm.h"
#include "TEBDDoc.h"
#include "TEBDView.h"


// CChartPropertyPage dialog

IMPLEMENT_DYNAMIC(CChartPropertyPage, CMFCPropertyPage)

CChartPropertyPage::CChartPropertyPage()
	: CMFCPropertyPage(IDD_CHART_PROPPAGE)
{
	bigTicksX = theApp.options.bigTicksX;
	bigTicksY = theApp.options.bigTicksY;
	smallTicksX = theApp.options.smallTicksX;
	smallTicksY = theApp.options.smallTicksY;

	minY = theApp.options.minY;
	maxY = theApp.options.maxY;
}

void CChartPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, minYEdit);
	DDX_Control(pDX, IDC_EDIT2, maxYEdit);

	DDX_Text(pDX, IDC_EDIT1, minY);
	DDX_Text(pDX, IDC_EDIT2, maxY);
	DDX_Text(pDX, IDC_EDIT3, bigTicksX);
	DDX_Text(pDX, IDC_EDIT4, smallTicksX);
	DDX_Text(pDX, IDC_EDIT5, bigTicksY);
	DDX_Text(pDX, IDC_EDIT6, smallTicksY);
}


BEGIN_MESSAGE_MAP(CChartPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CChartPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CChartPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, &CChartPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT4, &CChartPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, &CChartPropertyPage::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT6, &CChartPropertyPage::OnEnChangeEdit)
END_MESSAGE_MAP()


// CChartPropertyPage message handlers


void CChartPropertyPage::ApplyValues()
{
	theApp.options.bigTicksX = bigTicksX;
	theApp.options.bigTicksY = bigTicksY;
	theApp.options.smallTicksX = smallTicksX;
	theApp.options.smallTicksY = smallTicksY;

	theApp.options.minY = minY;
	theApp.options.maxY = maxY;

	theApp.options.Save();

	CMainFrame *frm = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);
	if (frm)
	{
		CTEBDDoc* doc = frm->GetDocument();
		doc->SetAxisRange();
		CTEBDView* view = doc->GetView();
		if (view) view->Invalidate();
	}
}



BOOL CChartPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}


void CChartPropertyPage::OnEnChangeEdit()
{
	SetModified();
}


