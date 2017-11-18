
// TEBDView.cpp : implementation of the CTEBDView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TEBD.h"
#endif

#include "TEBDDoc.h"
#include "TEBDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTEBDView

IMPLEMENT_DYNCREATE(CTEBDView, CView)

BEGIN_MESSAGE_MAP(CTEBDView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTEBDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTEBDView construction/destruction

CTEBDView::CTEBDView()
: timer(NULL)
{
	// TODO: add construction code here

}

CTEBDView::~CTEBDView()
{
}

BOOL CTEBDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTEBDView drawing

void CTEBDView::OnDraw(CDC* pDC)
{
	CTEBDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);

	pDoc->m_Chart.Draw(pDC, rect);
}


// CTEBDView printing


void CTEBDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTEBDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTEBDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTEBDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTEBDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTEBDView::OnContextMenu(CWnd* /* pWnd */, CPoint /*point*/)
{
#ifndef SHARED_HANDLERS
#endif
}


// CTEBDView diagnostics

#ifdef _DEBUG
void CTEBDView::AssertValid() const
{
	CView::AssertValid();
}

void CTEBDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTEBDDoc* CTEBDView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTEBDDoc)));
	return dynamic_cast<CTEBDDoc*>(m_pDocument);
}
#endif //_DEBUG


// CTEBDView message handlers


void CTEBDView::OnDestroy()
{
	CView::OnDestroy();

	if (timer) KillTimer(timer);
}


BOOL CTEBDView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}


BOOL CTEBDView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CTEBDDoc* pDoc = GetDocument();

	if (pDoc && !pDoc->IsFinished())
	{
		RestoreWaitCursor();

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CTEBDView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	CTEBDDoc* pDoc = GetDocument();

	if (pDoc->IsFinished())
	{
		KillTimer(timer);
		timer = 0;

		pDoc->UpdateChartData();

		EndWaitCursor();
		Invalidate();
	}
}


void CTEBDView::StartTimer()
{
	if (!timer) timer = SetTimer(1, 1000, NULL);
	BeginWaitCursor();
}


void CTEBDView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnPrepareDC(pDC, pInfo);

	if (pDC->IsPrinting())
	{
		CRect rect;
		GetClientRect(rect);

		pDC->SetMapMode(MM_ISOTROPIC);

		int cx = pDC->GetDeviceCaps(HORZRES);
		int cy = pDC->GetDeviceCaps(VERTRES);
		
		pDC->SetWindowExt(rect.Width(), rect.Height());
		pDC->SetViewportExt(cx, cy);
		pDC->SetViewportOrg(0, 0);
	}
}
