// MediaView.h : interface of the MediaView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class MediaDoc;


class MediaView : public CScrView {
protected:

  MediaView() noexcept;

  DECLARE_DYNCREATE(MediaView)

public:

  virtual ~MediaView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void displayHeader(DevBase& dev);
  virtual void displayFooter(DevBase& dev);

  virtual void onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void printHeader(DevBase& dev, int pageNo);
  virtual void printFooter(DevBase& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  MediaDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  };


#ifndef _DEBUG  // debug version in MediaView.cpp
inline MediaDoc* MediaView::GetDocument() const
   { return reinterpret_cast<MediaDoc*>(m_pDocument); }
#endif




#if 1
#else
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
#endif

