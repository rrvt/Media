// Find Media by Title Dialog


#pragma once
#include "Resource.h"


// FindDlg dialog

class FindDlg : public CDialogEx {

  DECLARE_DYNAMIC(FindDlg)

public:
Cstring explanation;
Cstring target;

           FindDlg(CWnd* pParent = nullptr);            // standard constructor
  virtual ~FindDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_FindByTitle };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);      // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFindTitle();
  afx_msg void onFindChannel();
  afx_msg void onFindDate();
  afx_msg void onFindComment();
  };
