
// TEBDView.h : interface of the CTEBDView class
//

#pragma once


class CTEBDView : public CView
{
protected: 
	CTEBDView(); // create from serialization only

	DECLARE_DYNCREATE(CTEBDView)
	DECLARE_MESSAGE_MAP()

	BOOL OnPreparePrinting(CPrintInfo* pInfo) override;
	void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;
	void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;

	UINT_PTR timer;

public:
	~CTEBDView() override;

	void StartTimer();

	CTEBDDoc* GetDocument() const;

	void OnDraw(CDC* pDC) override;  // overridden to draw this view
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

protected:
// Generated message map functions
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	

	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL) override;
};

#ifndef _DEBUG  // debug version in TEBDView.cpp
inline CTEBDDoc* CTEBDView::GetDocument() const
   { return reinterpret_cast<CTEBDDoc*>(m_pDocument); }
#endif

