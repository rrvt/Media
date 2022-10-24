// Edit Question Dialog


#pragma once
#include "Resource.h"


// EditQstnDlg dialog

class EditQstnDlg : public CDialogEx {

  DECLARE_DYNAMIC(EditQstnDlg)

public:

CString title;
CString channel;

           EditQstnDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~EditQstnDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_EditQstn };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
};
