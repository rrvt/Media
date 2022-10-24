// MediaView.h : interface of the MediaView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class MediaDoc;


class MediaView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;

protected: // create from serialization only

  MediaView() noexcept;

  DECLARE_DYNCREATE(MediaView)

public:

  virtual ~MediaView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  MediaDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  };


#ifndef _DEBUG  // debug version in MediaView.cpp
inline MediaDoc* MediaView::GetDocument() const
   { return reinterpret_cast<MediaDoc*>(m_pDocument); }
#endif


