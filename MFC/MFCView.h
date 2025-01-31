
// MFCView.h : interface of the CMFCView class
//

#pragma once


class CMFCView : public CView
{
protected: // create from serialization only
	CMFCView() noexcept;
	DECLARE_DYNCREATE(CMFCView)

// Attributes
public:
	CMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
#endif

protected:
	void PrintRect(CDC* pDC, CRect* pRect, CPen* pPen);

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CRect* m_pPaintRect;
	CFont* m_pNewFont;
};

#ifndef _DEBUG  // debug version in MFCView.cpp
inline CMFCDoc* CMFCView::GetDocument() const
   { return reinterpret_cast<CMFCDoc*>(m_pDocument); }
#endif

