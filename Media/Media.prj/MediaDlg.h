// MediaDlg dialog


#pragma once


class MediaDlg : public CDialogEx {

  DECLARE_DYNAMIC(MediaDlg)

public:

bool          addRecord{true};
Cstring       title{};
Cstring       channel{};
COleDateTime  date{};
Cstring       comment{};
BOOL          firstNamePrsnt{false};
Cstring       firstName{};
BOOL          secondNamePrsnt{false};
Cstring       secondName{};

CComboBox     channelCtl;
CDateTimeCtrl dateCtl;

               MediaDlg(bool addRcd, CWnd* pParent = nullptr);   // standard constructor
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

private:

  bool checkDate();

public:

  afx_msg void onDelete();
  afx_msg void OnNMKillfocusDate(NMHDR* pNMHDR, LRESULT* pResult);
  };


