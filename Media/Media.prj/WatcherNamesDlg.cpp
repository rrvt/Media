// Set Watcher Names Dialog


#include "pch.h"
#include "WatcherNamesDlg.h"
#include "Resource.h"


// WatcherNamesDlg dialog

IMPLEMENT_DYNAMIC(WatcherNamesDlg, CDialogEx)


WatcherNamesDlg::WatcherNamesDlg(CWnd* pParent) : CDialogEx(IDD_SetWatcherNames, pParent),
                                                    firstWatcher(_T("")), secondWatcher(_T("")) { }
WatcherNamesDlg::~WatcherNamesDlg() { }


void WatcherNamesDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_FirstWatcher,  firstWatcher);
  DDX_Text(pDX, IDC_SecondWatcher, secondWatcher);
  }


BEGIN_MESSAGE_MAP(WatcherNamesDlg, CDialogEx)
END_MESSAGE_MAP()

