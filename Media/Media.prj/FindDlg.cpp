// FindDlg.cpp : implementation file


#include "stdafx.h"
#include "FindDlg.h"


// FindDlg dialog

IMPLEMENT_DYNAMIC(FindDlg, CDialogEx)


BEGIN_MESSAGE_MAP(FindDlg, CDialogEx)
  ON_BN_CLICKED(IDC_FindTitle,   &onFindTitle)
  ON_BN_CLICKED(IDC_FindChannel, &onFindChannel)
  ON_BN_CLICKED(IDC_FindComment, &onFindComment)
END_MESSAGE_MAP()


FindDlg::FindDlg(CWnd* pParent) : CDialogEx(IDD_FindByTitle, pParent),
                                                            explanation(_T("")), target(_T("")) { }

FindDlg::~FindDlg() { }


void FindDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Explanation, explanation);
  DDX_Text(pDX, IDC_Target,      target);
  }


void FindDlg::onFindTitle()   {UpdateData(); EndDialog(IDC_FindTitle);}
void FindDlg::onFindChannel() {UpdateData(); EndDialog(IDC_FindChannel);}
void FindDlg::onFindComment() {UpdateData(); EndDialog(IDC_FindComment);}
