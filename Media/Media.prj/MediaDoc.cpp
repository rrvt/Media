 // MediaDoc.cpp : implementation of the MediaDoc class


#include "stdafx.h"
#include "MediaDoc.h"
#include "Channels.h"
#include "ClipLine.h"
#include "CopyFile.h"
#include "DelQstnDlg.h"
#include "EditQstnDlg.h"
#include "ExtraResource.h"
#include "filename.h"
#include "FindDlg.h"
#include "GetPathDlg.h"
#include "match.h"
#include "Media.h"
#include "MediaDlg.h"
#include "MediaView.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"


static TCchar* Expl =_T("This is an unachored search of the title screen with the regular expression ")
                     _T("target in the edit box below.\n\n")
                     _T("  ^  - At beginning of line indicates an achored match\n")
                     _T("  $  - At end of line must match the end of the line\n")
                     _T("  .  - Matches any character\n")
                     _T("  [] - Set, Collection of characters to match at the position in the line\n")
                     _T("  *  - Kleene Closure of preceding pattern (Tchar, metachar or set\n")
                     _T("  \\  - Escape, next character used literally\n")
                     _T("  \\t - Tab character\n\n")
                     _T("  Sets (i.e. [...])\n")
                     _T("  ^  - When First character in set, indicates match is not a character in set\n")
                     _T("  -  - When not first character indicates an inclusive range of characters\n")
                     _T("  \\  - Escape, When not last character in set, include next character in set");


IMPLEMENT_DYNCREATE(MediaDoc, CDoc)


BEGIN_MESSAGE_MAP(MediaDoc, CDoc)
  ON_COMMAND(ID_Find,      &onFind)
  ON_COMMAND(ID_AddMedia,  &onAddMedia)
  ON_COMMAND(ID_EditMedia, &onEditMedia)
  ON_COMMAND(ID_DelMedia,  &onDelMedia)
  ON_COMMAND(ID_Refresh,   &onRefresh)
  ON_COMMAND(ID_File_Save, &onFileSave)
  ON_COMMAND(ID_Options,   &OnOptions)
END_MESSAGE_MAP()


// MediaDoc construction/destruction


MediaDoc::MediaDoc() noexcept : dataSource(NotePadSrc) { }


MediaDoc::~MediaDoc() {if (!theApp.isSysClose()) {channels.store();   saveData(StoreSrc);}}


void MediaDoc::onFind() {
String      target;
StoreSearch srch(store);
Datum*      dtm;
int         i;

  target = clipLine.clipped;   srch.setFld(getSrchTgt(target));

  notePad.clear();

  for (dtm = srch(target), i = 0; dtm; dtm = srch++, i++) {if (i) notePad << nCrlf;    dtm->display();}

  if (i) clipLine.clear();   display(NotePadSrc);
  }


void MediaDoc::onAddMedia() {
MediaDlg dlg;
Datum    d;

  notePad << nSetTab(10);

  dlg.bobPresent = dlg.maureenPresent = true;

  if (dlg.DoModal() == IDOK) {

    channels.add(dlg.channel.str());

    d.title   = dlg.title;
    d.channel = dlg.channel;
    Date x    = dlg.date;
    d.date    = dlg.date;
    d.comment = dlg.comment; d.bobPresent = dlg.bobPresent;  d.maureenPresent = dlg.maureenPresent;
    store.add(d);

    onRefresh(); return;
    }

  display(NotePadSrc);
  }


void MediaDoc::onEditMedia() {
String      target;
StoreSearch srch(store);
Datum*      dtm;
bool        modMade = false;

  target = clipLine.clipped;   srch.setFld(getSrchTgt(target));

  for (dtm = srch(target); dtm; dtm = srch++) dtm->recentEdit = false;

  for (dtm = srch(target); dtm; dtm = srch++) {

    if (dtm->recentEdit) continue;

    EditQstnDlg qstn;
    qstn.title = dtm->title;   qstn.channel = dtm->channel;

    if (qstn.DoModal() == IDOK) {
      MediaDlg med;
      med.title          = dtm->title;
      med.channel        = dtm->channel;
      med.date           = dtm->date;
      med.comment        = dtm->comment;
      med.bobPresent     = dtm->bobPresent;
      med.maureenPresent = dtm->maureenPresent;

      if (med.DoModal() == IDOK) {
        srch.del(dtm);
        Datum d;
        d.title          = med.title;
        d.channel        = med.channel;
        d.date           = med.date;
        d.comment        = med.comment;
        d.bobPresent     = med.bobPresent;
        d.maureenPresent = med.maureenPresent;
        d.recentEdit     = true;
        store.add(d);   modMade = true;    clipLine.clear();
        }
      }
    }

  if (modMade) onRefresh();
  }


void MediaDoc::onDelMedia() {
String      target;
StoreSearch srch(store);
Datum*      dtm;
bool        modMade = false;

  target = clipLine.clipped;   srch.setFld(getSrchTgt(target));

  for (dtm = srch(target); dtm; dtm = srch++) dtm->recentEdit = false;

  for (dtm = srch(target); dtm; dtm = srch++) {

    if (dtm->recentEdit) continue;

    DelQstnDlg qstn;

    qstn.title   = dtm->title;
    qstn.channel = dtm->channel;
    qstn.date    = dtm->date.format(_T("%m/%d/%y"));
    qstn.name1   = dtm->maureenPresent ? _T("Maureen") : _T("");
    qstn.name2   = dtm->bobPresent     ? _T("Bob")     : _T("");

    if (qstn.DoModal() == IDOK) {srch.del(dtm);   modMade = true;}
    }

  if (modMade) onRefresh();
  }


StrSrchFld MediaDoc::getSrchTgt(String& target) {
FindDlg    dlg;
StrSrchFld srchFld;

  dlg.explanation = Expl;   dlg.target = target;

  switch (dlg.DoModal()) {
    case IDC_FindChannel : srchFld = StrSrchChn;   break;
    case IDC_FindComment : srchFld = StrSrchCom;   break;
    case IDC_FindTitle   : srchFld = StrSrchTitle; break;
    default              : srchFld = StrSrchNil;   break;
    }

  target = dlg.target;  return srchFld;
  }


void MediaDoc::onRefresh() {store.display();   display(NotePadSrc);}


void MediaDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void MediaDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void MediaDoc::loadData(TCchar* path) {
DataSource stk = dataSource;   dataSource = StoreSrc;

  dataPath = path;  OnOpenDocument(path);   dataSource = stk;

  store.display();
  }


void MediaDoc::onFileSave() {
DataSource stk = dataSource;

  dataSource = NotePadSrc;   if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);   dataSource = stk;
  }


void MediaDoc::saveData(DataSource src) {
DataSource stk = dataSource;

  backupFile(dataPath, 10);   dataSource = src;   OnSaveDocument(dataPath);

  dataSource = stk;
  }


void MediaDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
      case StoreSrc   : store.store(ar); return;
      default         : return;
      }

  else
    switch(dataSource) {
      case FontSrc  :
      case StoreSrc : store.load(ar); return;
      default       : return;
      }
  }


// MediaDoc diagnostics

#ifdef _DEBUG
void MediaDoc::AssertValid()          const {CDocument::AssertValid();}
void MediaDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG

