
// TEBDDoc.cpp : implementation of the CTEBDDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TEBD.h"
#endif

#include "TEBDDoc.h"
#include "TEBDView.h"

#include <propkey.h>

#include <cmath>
#include <limits>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CTEBDDoc

IMPLEMENT_DYNCREATE(CTEBDDoc, CDocument)

BEGIN_MESSAGE_MAP(CTEBDDoc, CDocument)
	ON_COMMAND(ID_FILE_START, &CTEBDDoc::OnFileStart)
	ON_UPDATE_COMMAND_UI(ID_FILE_START, &CTEBDDoc::OnUpdateFileStart)
END_MESSAGE_MAP()


// CTEBDDoc construction/destruction

CTEBDDoc::CTEBDDoc()
	: thread(nullptr)
{
	// TODO: add one-time construction code here
}

CTEBDDoc::~CTEBDDoc()
{
	delete thread;
}

BOOL CTEBDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	m_Chart.useSpline = false;
	

	m_Chart.XAxisLabel = "Time";
	m_Chart.YAxisLabel = "m";

	SetTitle(L"No data");


	m_Chart.XAxisMin = 0;
	SetAxisRange();


	return TRUE;
}




// CTEBDDoc serialization

void CTEBDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTEBDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CTEBDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTEBDDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTEBDDoc diagnostics

#ifdef _DEBUG
void CTEBDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTEBDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTEBDDoc commands



bool CTEBDDoc::IsFinished()
{
	if (!thread || thread->terminated) return true;

	return false;
}

CTEBDView* CTEBDDoc::GetView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CTEBDView)))
			return dynamic_cast<CTEBDView*>(pView);
	}

	return NULL;
}

void CTEBDDoc::SetAxisRange()
{
	m_Chart.SetNumBigTicksX(theApp.options.bigTicksX);
	m_Chart.SetNumBigTicksY(theApp.options.bigTicksY);
	m_Chart.SetNumTicksX(theApp.options.bigTicksX * theApp.options.smallTicksX);
	m_Chart.SetNumTicksY(theApp.options.bigTicksY * theApp.options.smallTicksY);

	m_Chart.YAxisMin = theApp.options.minY;
	m_Chart.YAxisMax = theApp.options.maxY;

	m_Chart.XAxisMax = theApp.options.maxTime;
}

void CTEBDDoc::UpdateChartData()
{
	if (!thread || !thread->terminated) return;

	double startTime = 0.001;
	std::vector<std::pair<double, double>> data;
	data.reserve(thread->m_iTEBDobj.m_Results.size());
	for (const auto& val : thread->m_iTEBDobj.m_Results)
	{
		if (val.size() == 2)
			data.push_back(std::make_pair(startTime, val[0] - val[1]*val[1]));
		else
			data.push_back(std::make_pair(startTime, val[0]));

		startTime += 0.001;
	}
	SetTitle(L"Finished");

	m_Chart.clear();

	SetAxisRange();

	m_Chart.AddDataSet(&data, 2, RGB(255,0,0));

	delete thread;
	thread = nullptr;
}



void CTEBDDoc::StartComputing()
{
	if (thread) return;

	SetTitle(L"Computing");

	CTEBDView* view = GetView();
	if (view) view->StartTimer();			

	thread = new TEBDComputationThread(theApp.options);
	thread->Start();
}


void CTEBDDoc::OnFileStart()
{
	if (!IsFinished()) return;

	StartComputing();
}


void CTEBDDoc::OnUpdateFileStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsFinished() ? TRUE : FALSE);
	pCmdUI->SetCheck(IsFinished() ? FALSE : TRUE);
}
