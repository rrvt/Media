// MediaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MediaDlg.h"
#include "Channels.h"
#include "resource.h"


// MediaDlg dialog

IMPLEMENT_DYNAMIC(MediaDlg, CDialogEx)


BEGIN_MESSAGE_MAP(MediaDlg, CDialogEx)
END_MESSAGE_MAP()


MediaDlg::MediaDlg(CWnd* pParent) : CDialogEx(IDD_Media, pParent), title(_T("")), channel(_T("")),
                                    comment(_T("")), date(COleDateTime::GetCurrentTime()),
                                    bobPresent(FALSE), maureenPresent(FALSE) { }
MediaDlg::~MediaDlg() { }


BOOL MediaDlg::OnInitDialog() {
ChnIter  iter(channels);
Channel* chn;

  CDialogEx::OnInitDialog();

  for (chn = iter(); chn; chn = iter++) channelCtl.AddString(chn->name);

  return TRUE;
  }


void MediaDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(        pDX, IDC_Title,   title);
  DDX_CBString(    pDX, IDC_Channel, channel);
  DDX_Control(     pDX, IDC_Channel, channelCtl);
  DDX_Control(     pDX, IDC_Date,    dateCtl);
  DDX_DateTimeCtrl(pDX, IDC_Date,    date);
  DDX_Text(        pDX, IDC_Comment, comment);
  DDX_Check(       pDX, IDC_Bob,     bobPresent);
  DDX_Check(       pDX, IDC_Maureen, maureenPresent);
  }


void MediaDlg::OnOK() {CDialogEx::OnOK();}







#if 0
    DDX_Text(pDX, IDC_AuthorID, authorID);
    DDX_Text(pDX, IDC_EDIT7, author);
    DDX_Text(pDX, IDC_EDIT8, authorLast);

    DDX_Text(pDX, IDC_Aurthor2ID, author2ID);
    DDX_Text(pDX, IDC_EDIT9, author2);
    DDX_Text(pDX, IDC_EDIT10, author2Last);

    DDX_Text(pDX, IDC_ProtagID, protagID);
    DDX_Text(pDX, IDC_EDIT1, protag);
    DDX_Text(pDX, IDC_EDIT2, protagLast);

    DDX_Text(pDX, IDC_Protag2ID, protag2ID);
    DDX_Text(pDX, IDC_EDIT3, protag2);
    DDX_Text(pDX, IDC_EDIT4, protag2Last);

    DDX_Text(pDX, IDC_EDIT5, location);
    DDX_Text(pDX, IDC_EDIT6, title);
    DDX_Text(pDX, IDC_EDIT11, pubDate);
    DDX_Text(pDX, IDC_EDIT12, comment);

    DDX_Control(pDX, IDC_AuthorID, authorIDctrl);
    DDX_Control(pDX, IDC_EDIT7, authFNctrl);
    DDX_Control(pDX, IDC_EDIT8, authLNctrl);
    DDX_Control(pDX, IDC_Aurthor2ID, author2IDctrl);
    DDX_Control(pDX, IDC_EDIT9, auth2FNctrl);
    DDX_Control(pDX, IDC_EDIT10, auth2LNctrl);
    DDX_Control(pDX, IDC_ProtagID, protagIDctrl);
    DDX_Control(pDX, IDC_EDIT1, prtgFNctrl);
    DDX_Control(pDX, IDC_EDIT2, prtgLNctrl);
    DDX_Control(pDX, IDC_Protag2ID, protag2IDctrl);
    DDX_Control(pDX, IDC_EDIT3, prtg2FNctrl);
    DDX_Control(pDX, IDC_EDIT4, prtg2LNctrl);
#endif
#if 0
void MediaDlg::OnLeaveAuthorID() {  load(AuthorTyp, authorIDctrl,  authFNctrl,  authLNctrl);}
void MediaDlg::OnLeaveAurthor2ID() {load(AuthorTyp, author2IDctrl, auth2FNctrl, auth2LNctrl);}
void MediaDlg::OnLeaveProtagID() {  load(ProtagTyp, protagIDctrl,  prtgFNctrl,  prtgLNctrl);}
void MediaDlg::OnLeaveProtag2ID() { load(ProtagTyp, protag2IDctrl, prtg2FNctrl, prtg2LNctrl);}
#endif
#if 0
void MediaDlg::load(PerTyp typ, CEdit& idCtrl, CEdit& fnCtrl, CEdit& lnCtrl) {
int      n;
Tchar    buf[12];
int      id;
uint     x;
Person*  person;

  n = idCtrl.GetLine(0, buf, noElements(buf));   if (!n) return;

  String s(buf, n);    id = s.stoi(x);

  person = persons.find(typ, id);

  if (person) {fnCtrl.SetWindowText(person->fName);   lnCtrl.SetWindowText(person->lName);}
  }
#endif
//author(_T("")), pubDate(_T("")), authorID(_T("")), author2ID(_T("")), protagID(_T("")),
// protag2ID(_T(""))
//  ON_EN_KILLFOCUS(IDC_AuthorID,   &MediaDlg::OnLeaveAuthorID)
//  ON_EN_KILLFOCUS(IDC_Aurthor2ID, &MediaDlg::OnLeaveAurthor2ID)
//  ON_EN_KILLFOCUS(IDC_ProtagID,   &MediaDlg::OnLeaveProtagID)
//  ON_EN_KILLFOCUS(IDC_Protag2ID,  &MediaDlg::OnLeaveProtag2ID)

