// MediaView.cpp : implementation of the MediaView class


#include "stdafx.h"
#include "MediaView.h"
#include "Channels.h"
#include "ClipLine.h"
#include "Media.h"
#include "MediaDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgOne.h"


// MediaView

IMPLEMENT_DYNCREATE(MediaView, CScrView)


BEGIN_MESSAGE_MAP(MediaView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


MediaView::MediaView() noexcept {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL MediaView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void MediaView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void MediaView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl00 = _T("Media:");

  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {prtNote.prtrOrietn = printer.toOrient(dlg.ntpd);   saveNoteOrietn();}
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void MediaView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    }
  }


void MediaView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this); break;
    }
  }


void MediaView::displayHeader(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
    }
  }


void MediaView::displayFooter(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
    }
  }


void MediaView::printHeader(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void MediaView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
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


void MediaView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  clipLine.set(point);   RedrawWindow();   clipLine.load();

  CScrView::OnLButtonDblClk(nFlags, point);
  }


// MediaView diagnostics

#ifdef _DEBUG

void MediaView::AssertValid()          const {CScrollView::AssertValid();}
void MediaView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
MediaDoc* MediaView::GetDocument() const
           {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MediaDoc))); return (MediaDoc*)m_pDocument;}

#endif //_DEBUG




