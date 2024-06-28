// MediaDlg.cpp : implementation file


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




