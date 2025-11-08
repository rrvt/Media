// EditQstnDlg.cpp : implementation file


#include "stdafx.h"
#include "Media.h"
#include "afxdialogex.h"
#include "EditQstnDlg.h"


// EditQstnDlg dialog

IMPLEMENT_DYNAMIC(EditQstnDlg, CDialogEx)


BEGIN_MESSAGE_MAP(EditQstnDlg, CDialogEx)
    ON_BN_CLICKED(IDC_Cancel,   &OnCancel)
    ON_BN_CLICKED(ID_DoNotEdit, &onDoNotEdit)
END_MESSAGE_MAP()


EditQstnDlg::EditQstnDlg(CWnd* pParent) : CDialogEx(IDD_EditQstn, pParent), maureen(_T(""))
, bob(_T(""))
{ }

EditQstnDlg::~EditQstnDlg() { }

void EditQstnDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TitleStg, title);
    DDX_Text(pDX, IDC_ChannelStg, channel);
    DDX_Text(pDX, IDC_DateTime, dateTime);
    DDX_Text(pDX, IDC_Maureen, maureen);
    DDX_Text(pDX, IDC_Bob, bob);
}


void EditQstnDlg::onDoNotEdit() {EndDialog(IDRETRY);}
