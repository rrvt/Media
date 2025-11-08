// MediaDlg.cpp : implementation file


#include "stdafx.h"
#include "MediaDlg.h"
#include "Channels.h"
#include "resource.h"


// MediaDlg dialog

IMPLEMENT_DYNAMIC(MediaDlg, CDialogEx)


BEGIN_MESSAGE_MAP(MediaDlg, CDialogEx)
    ON_BN_CLICKED(IDC_Delete, &MediaDlg::onDelete)
  ON_NOTIFY(NM_KILLFOCUS, IDC_Date, &MediaDlg::OnNMKillfocusDate)
END_MESSAGE_MAP()


MediaDlg::MediaDlg(bool addRcd, CWnd* pParent) :
                                               CDialogEx(IDD_Media, pParent), addRecord(addRcd) { }

MediaDlg::~MediaDlg() { }


// The upper date limit is 12/31/3000. The lower limit is 1/1/1970 12:00:00 AM GMT.

BOOL MediaDlg::OnInitDialog() {
ChnIter  iter(channels);
Channel* chn;
CTime    minDate(1970,1,1,12,0,0);
CTime    maxDate(3000,12,31,0, 0, 0);

  CDialogEx::OnInitDialog();

  for (chn = iter(); chn; chn = iter++) channelCtl.AddString(chn->name);

  dateCtl.SetRange(&minDate, &maxDate);
  dateCtl.SetFormat(_T("MM/dd/yyyy HH:mm"));

  if (!addRecord) GetDlgItem(IDC_Delete)->ShowWindow(SW_SHOW);

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


void MediaDlg::OnOK() {
  if (checkDate()) CDialogEx::OnOK();}





void MediaDlg::onDelete() {EndDialog(IDABORT);}


void MediaDlg::OnNMKillfocusDate(NMHDR* pNMHDR, LRESULT* pResult) {checkDate();   *pResult = 0;}


bool MediaDlg::checkDate() {
Date dt;
Date today;

  dateCtl.GetTime(date);    dt = date;    today.getToday();

  if (dt <= today) return true;

  dt = today;   date = dt;   dateCtl.SetTime(date);   dateCtl.SetFocus();   return false;
  }

