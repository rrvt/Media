// Media.h : main header file for the Media application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class MediaDoc;
class MediaView;


// Media:
// See Media.cpp for the implementation of this class

class Media : public CApp {

bool sysClose;

public:

               Media() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

    MediaDoc*  doc()  {return (MediaDoc*)  CApp::getDoc();}
    MediaView* view() {return (MediaView*) CApp::getView();}
    MainFrame* mainFrm() {return (MainFrame*) m_pMainWnd;}

    void       setSysClose() {sysClose = true;}
    bool       isSysClose()  {return sysClose;}

  DECLARE_MESSAGE_MAP()

//  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern Media theApp;

inline void       invalidate() {theApp.invalidate();}
inline MediaDoc*  doc()        {return theApp.doc();}
inline MediaView* view()       {return theApp.view();}
inline MainFrame* mainFrm()    {return theApp.mainFrm();}
inline MyToolBar& getToolBar() {return mainFrm()->getToolBar();}

