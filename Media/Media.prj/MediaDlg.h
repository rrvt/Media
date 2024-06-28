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


