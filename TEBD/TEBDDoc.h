
// TEBDDoc.h : interface of the CTEBDDoc class
//


#pragma once

#include "Chart.h"

class CTEBDView;
class TEBDComputationThread;

class CTEBDDoc : public CDocument
{
protected: // create from serialization only
	CTEBDDoc();
	DECLARE_DYNCREATE(CTEBDDoc)
	DECLARE_MESSAGE_MAP()
public:
	Chart m_Chart;

	CTEBDView* GetView();

	bool IsFinished();
	void UpdateChartData();
	void StartComputing();
	void SetAxisRange();

	afx_msg void OnFileStart();
	afx_msg void OnUpdateFileStart(CCmdUI* pCmdUI);

	~CTEBDDoc() override;

private:
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

	BOOL OnNewDocument() override;
	void Serialize(CArchive& ar) override;
#ifdef SHARED_HANDLERS
	void InitializeSearchContent() override;
	void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) override;
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	TEBDComputationThread *thread;
};
