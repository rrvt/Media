// MediaView.cpp : implementation of the MediaView class


#include "stdafx.h"
#include "MediaView.h"
#include "Channels.h"
#include "ClipLine.h"
#include "Media.h"
#include "MediaDoc.h"
#include "Options.h"
#include "Resource.h"
#include "Resources.h"


// MediaView

IMPLEMENT_DYNCREATE(MediaView, CScrView)


BEGIN_MESSAGE_MAP(MediaView, CScrView)
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


MediaView::MediaView() noexcept :
                                    dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL MediaView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void MediaView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void MediaView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc : prtNote.print(*this);  break;
      }

  else
    switch(ds) {
      case NotePadSrc : dspNote.display(*this);  break;
      }


  CScrView::onPrepareOutput(printing);
  }


void MediaView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void MediaView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
    }
  }


void MediaView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void MediaView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void MediaView::OnLButtonDown(UINT nFlags, CPoint point)
                        {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void MediaView::OnLButtonDblClk(UINT nFlags, CPoint point)
  {clipLine.set(point);   RedrawWindow();   clipLine.load();   CScrView::OnLButtonDblClk(nFlags, point);}


// MediaView diagnostics

#ifdef _DEBUG

void MediaView::AssertValid() const {CScrollView::AssertValid();}

void MediaView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
MediaDoc* MediaView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MediaDoc))); return (MediaDoc*)m_pDocument;}

#endif //_DEBUG




#if 0
dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()),
#endif
#if 0
      case StoreSrc   : prtStore.print(*this); break;
#endif
#if 0
      case StoreSrc   : dspStore.display(*this); break;
#endif
#if 0
    case StoreSrc   : prtStore.footer(dev, pageNo); break;
#endif

#if 0
void MediaView::OnAppExit() {                   //ID_APP_EXIT

#if 1
  int rslt = DefWindowProc(WM_COMMAND, ID_APP_EXIT, 0);
  String s; s.format(_T("Def Rslt = %i"), rslt);
  messageBox(s);
#else
  PostQuitMessage(0);
  if (PostMessage(0, WM_COMMAND, ID_APP_EXIT, 0)) return;

  lastErr = GetLastError();   notePad << _T("Last Error = ") << lastErr << nCrlf;   display(NotePadSrc);
#endif
  }
#endif


#if 0
void MediaView::OnSysCommand(UINT nID, LPARAM lParam) {

  theApp.setSysClose();

  // TODO: Add your message handler code here and/or call default

  CScrView::OnSysCommand(nID, lParam);
  }
#endif


