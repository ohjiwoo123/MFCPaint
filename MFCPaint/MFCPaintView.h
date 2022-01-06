﻿
// MFCPaintView.h: CMFCPaintView 클래스의 인터페이스
//

#pragma once


class CMFCPaintView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCPaintView() noexcept;
	DECLARE_DYNCREATE(CMFCPaintView)

// 특성입니다.
public:
	CMFCPaintDoc* GetDocument() const;

// 작업입니다.
public:
	CPoint m_ptStart;
	CPoint m_ptEnd;
	BOOL m_bDrag;

	int m_nShape;
	BOOL m_bFill;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnFill();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFill(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // MFCPaintView.cpp의 디버그 버전
inline CMFCPaintDoc* CMFCPaintView::GetDocument() const
   { return reinterpret_cast<CMFCPaintDoc*>(m_pDocument); }
#endif

