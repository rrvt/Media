// MediaDlg dialog


#pragma once


class MediaDlg : public CDialogEx {

  DECLARE_DYNAMIC(MediaDlg)

public:

Cstring       title;
Cstring       channel;
COleDateTime  date;
Cstring       comment;
BOOL          bobPresent;
BOOL          maureenPresent;

CComboBox     channelCtl;
CDateTimeCtrl dateCtl;

               MediaDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~MediaDlg();
  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Media };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
};






#if 0
CString title;
CString authorID;
CEdit   authorIDctrl;
CString author;
CEdit   authFNctrl;
CString authorLast;
CEdit   authLNctrl;

CString author2ID;
CEdit   author2IDctrl;
CString author2;
CEdit   auth2FNctrl;
CString author2Last;
CEdit   auth2LNctrl;

CString protagID;
CEdit   protagIDctrl;
CString protag;
CEdit   prtgFNctrl;
CString protagLast;
CEdit   prtgLNctrl;

CString protag2ID;
CEdit   protag2IDctrl;
CString protag2;
CEdit   prtg2FNctrl;
CString protag2Last;
CEdit   prtg2LNctrl;

CString location;
CString pubDate;
CString comment;
#endif
#if 0
  afx_msg void OnLeaveAuthorID();
  afx_msg void OnLeaveAurthor2ID();
  afx_msg void OnLeaveProtagID();
  afx_msg void OnLeaveProtag2ID();
#endif

//  void        load(PerTyp typ, CEdit& idCtrl, CEdit& fnCtrl, CEdit& lnCtrl);

