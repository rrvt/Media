// Set Watcher Names Dialog


#pragma once


// WatcherNamesDlg dialog

class WatcherNamesDlg : public CDialogEx {

  DECLARE_DYNAMIC(WatcherNamesDlg)

public:
CString firstWatcher;
CString secondWatcher;

           WatcherNamesDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~WatcherNamesDlg();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SetWatcherNames };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
