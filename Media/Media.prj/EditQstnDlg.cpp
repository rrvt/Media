// EditQstnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Media.h"
#include "afxdialogex.h"
#include "EditQstnDlg.h"


// EditQstnDlg dialog

IMPLEMENT_DYNAMIC(EditQstnDlg, CDialogEx)


BEGIN_MESSAGE_MAP(EditQstnDlg, CDialogEx)
END_MESSAGE_MAP()


EditQstnDlg::EditQstnDlg(CWnd* pParent) : CDialogEx(IDD_EditQstn, pParent),
                                                                        title(_T("")), channel(_T("")) { }

EditQstnDlg::~EditQstnDlg() { }

void EditQstnDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_TitleStg,   title);
  DDX_Text(pDX, IDC_ChannelStg, channel);
  }

