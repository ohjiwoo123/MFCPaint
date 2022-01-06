
// MFCPaintView.cpp: CMFCPaintView 클래스의 구현

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCPaint.h"
#endif

#include "MFCPaintDoc.h"
#include "MFCPaintView.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCPaintView

IMPLEMENT_DYNCREATE(CMFCPaintView, CView)

BEGIN_MESSAGE_MAP(CMFCPaintView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_LINE, &CMFCPaintView::OnLine)
	ON_COMMAND(ID_RECTANGLE, &CMFCPaintView::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CMFCPaintView::OnEllipse)
	ON_COMMAND(ID_FILL, &CMFCPaintView::OnFill)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CMFCPaintView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CMFCPaintView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CMFCPaintView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_FILL, &CMFCPaintView::OnUpdateFill)
END_MESSAGE_MAP()

// CMFCPaintView 생성/소멸

CMFCPaintView::CMFCPaintView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptStart.x = 0;
	m_ptStart.y = 0;
	m_ptEnd.x = 0;
	m_ptEnd.y = 0;
	m_bDrag = FALSE;
	m_nShape = 0;
	m_bFill = FALSE;
}

CMFCPaintView::~CMFCPaintView()
{
}

BOOL CMFCPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCPaintView 그리기

void CMFCPaintView::OnDraw(CDC* /*pDC*/)
{
	CMFCPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCPaintView 인쇄

BOOL CMFCPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCPaintView 진단

#ifdef _DEBUG
void CMFCPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPaintDoc* CMFCPaintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPaintDoc)));
	return (CMFCPaintDoc*)m_pDocument;
}
#endif //_DEBUG

// CMFCPaintView 메시지 처리기

void CMFCPaintView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//				   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//				   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CBrush* OldBrush = NULL;
	//// MyBrush 빨강색으로 
	CBrush MyBrush(RGB(255, 0, 0));

	if (m_bFill)
	{
		// 빨간색 
		OldBrush = dc.SelectObject(&MyBrush);
	}

	////////////////////////////////////////////////////
	switch (m_nShape) 
	{
		case 0:		// 직선
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			break;
		case 1:		// 사각형
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptEnd.x, m_ptEnd.y);
			break;
		case 2:		// 원
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptEnd.x, m_ptEnd.y);
			break;
	}
	////////////////////////////////////////////////////	
	if (m_bFill)
	{
		dc.SelectObject(OldBrush);
	}
}


void CMFCPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_bDrag = TRUE;
	m_ptStart = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bDrag)
	{
		m_ptEnd = point;
		RedrawWindow();
	}

	CView::OnMouseMove(nFlags, point);
}


void CMFCPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		m_ptEnd = point;
		RedrawWindow();
		m_bDrag = FALSE;
	}	

	CView::OnLButtonUp(nFlags, point);
}


void CMFCPaintView::OnLine()
{
	m_nShape = 0;
}


void CMFCPaintView::OnRectangle()
{
	m_nShape = 1;
}


void CMFCPaintView::OnEllipse()
{
	m_nShape = 2;

}


void CMFCPaintView::OnFill()
{
	if (m_bFill == FALSE)
	{
		m_bFill = TRUE;
	}
	else
	{
		m_bFill = FALSE;
	}
}


void CMFCPaintView::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 0)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CMFCPaintView::OnUpdateRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 1)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CMFCPaintView::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_nShape == 2)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CMFCPaintView::OnUpdateFill(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bFill) // m_bFill 이 True이면 
	{
		// 채우기를 시작함. 
		pCmdUI->SetText(_T("채우기 취소"));
		pCmdUI->SetCheck(1);
	}
	else
	{
		// 채우기 안함.
		pCmdUI->SetText(_T("채우기"));
		pCmdUI->SetCheck(0);
	}
}
