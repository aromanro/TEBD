
// TEBDDoc.h : interface of the CTEBDDoc class
//


#pragma once

#include "Chart.h"
#include "TEBDComputationThread.h"

class CTEBDView;

class CTEBDDoc : public CDocument
{
protected: // create from serialization only
	CTEBDDoc();
	DECLARE_DYNCREATE(CTEBDDoc)

// Attributes
public:
	Chart m_Chart;

// Operations
// Overrides
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
	virtual ~CTEBDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	TEBDComputationThread *thread;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CTEBDView* GetView();

	bool IsFinished();
	void UpdateChartData();
	void StartComputing();
	void SetAxisRange();

	afx_msg void OnFileStart();
	afx_msg void OnUpdateFileStart(CCmdUI *pCmdUI);
};
