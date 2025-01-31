
// MFCView.cpp : implementation of the CMFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCView

IMPLEMENT_DYNCREATE(CMFCView, CView)

BEGIN_MESSAGE_MAP(CMFCView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCView construction/destruction

CMFCView::CMFCView() noexcept
{	
	// TODO: add construction code here
	m_pPaintRect = new CRect(0,0,0,0);

	LOGFONT* pLogFont = new LOGFONT;
	memset(pLogFont, 0, sizeof(LOGFONT));

	pLogFont->lfCharSet = DEFAULT_CHARSET;
	pLogFont->lfWidth = 6;
	pLogFont->lfHeight = 100; // 10px
	pLogFont->lfWeight = FW_NORMAL;

	CString sFontFaceName("Arial");

	lstrcpyn(pLogFont->lfFaceName, sFontFaceName, sFontFaceName.GetLength() + 1);
	m_pNewFont = new CFont;
	if (!(m_pNewFont->CreatePointFontIndirect(pLogFont)))
		TRACE0("Could Not create font...\n");

}

CMFCView::~CMFCView()
{
	delete m_pPaintRect;
	delete m_pNewFont;
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCView drawing

void CMFCView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
	GetClientRect(m_pPaintRect);
	CView::OnPrepareDC(pDC, pInfo);
}

void CMFCView::OnDraw(CDC* pDC)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	pDC->TextOut(10, 10, CString("This is my first MFC app"));

	CFont* pOldFont = pDC->SelectObject(m_pNewFont);
	pDC->TextOut(10, 30, CString("This is my first MFC app"));
	pDC->TextOut(10, 50, CString("This is my first MFC app"));

	CPen* pPen1 = new CPen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pPen2 = new CPen(PS_SOLID, 2, RGB(0,0, 255));
	CPen* oldPen = pDC->SelectObject(pPen1);
	pDC->MoveTo(50, 40);
	pDC->LineTo(150, 200);

	pDC->SelectObject(pPen2);
	pDC->MoveTo(150, 200);
	pDC->LineTo(400, 50);


	CRect rect;//left top right bottom
	//PrintRect(pDC, &rect, pPen2);
	int temp = (int)(m_pPaintRect->Width() *0.2);
	rect.left = m_pPaintRect->Width() >> 1 - temp;
	rect.right = m_pPaintRect->Width() >> 1 + temp;

	temp = (int)(m_pPaintRect->Height() *0.2);
	rect.top = m_pPaintRect->Height() / 2 - temp;
	rect.bottom = m_pPaintRect->Height() / 2 + temp;



	CBrush* pBrush = new CBrush(RGB(255,255,0));
	CBrush* pOldBrush = pDC->SelectObject(pBrush);
	pDC->Rectangle(&rect);

	pDC->SelectObject(pOldFont);
	delete pPen1;
	delete pPen2;
}

void CMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CMFCView::OnMouseMove(UINT nFlags, CPoint point) {
	CString str;
	str.Format(L"x = %d y = %d", point.x, point.y);


	CWnd* pWnd = GetParentFrame();
	pWnd->SetWindowTextW(str);
	CView::OnMouseMove(nFlags, point);

}
// CMFCView diagnostics

#ifdef _DEBUG
void CMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
	return (CMFCDoc*)m_pDocument;
}
#endif //_DEBUG

void CMFCView::PrintRect(CDC* pDC, CRect* pRect, CPen* pPen) {
	CPen* pOldPen = pDC->SelectObject(pPen);
	pDC->MoveTo(pRect->left, pRect->top);
	pDC->LineTo(pRect->right, pRect->top);
	pDC->LineTo(pRect->right, pRect->bottom);
	pDC->LineTo(pRect->left, pRect->bottom);
	pDC->LineTo(pRect->left, pRect->top);

	pDC->SelectObject(pOldPen);
}
// CMFCView message handlers
