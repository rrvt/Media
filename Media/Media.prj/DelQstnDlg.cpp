// DelQstnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DelQstnDlg.h"
#include "Media.h"


// DelQstnDlg dialog

IMPLEMENT_DYNAMIC(DelQstnDlg, CDialogEx)


BEGIN_MESSAGE_MAP(DelQstnDlg, CDialogEx)
END_MESSAGE_MAP()


DelQstnDlg::DelQstnDlg(CWnd* pParent) : CDialogEx(IDD_DelQstn, pParent),title(_T("")), channel(_T("")),
                                                            date(_T("")), name1(_T("")), name2(_T("")) { }

DelQstnDlg::~DelQstnDlg() { }


void DelQstnDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_TitleStg,   title);
  DDX_Text(pDX, IDC_ChannelStg, channel);
  DDX_Text(pDX, IDC_Date,       date);
  DDX_Text(pDX, IDC_Maureen,    name1);
  DDX_Text(pDX, IDC_Bob,        name2);
  }


// DelQstnDlg message handlers
