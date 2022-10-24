// Delete Question Dialog


#pragma once
#include "Resource.h"


// DelQstnDlg dialog

class DelQstnDlg : public CDialogEx {

  DECLARE_DYNAMIC(DelQstnDlg)

public:

CString title;
CString channel;
CString date;
CString name1;
CString name2;

           DelQstnDlg(CWnd* pParent = nullptr);         // standard constructor
  virtual ~DelQstnDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DelQstn };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
