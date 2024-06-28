// Media.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "Media.h"
#include "AboutDlg.h"
#include "Channels.h"
#include "ResourceExtra.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "MediaDoc.h"
#include "MediaView.h"


Media   theApp;                         // The one and only Media object
IniFile iniFile;


// Media

BEGIN_MESSAGE_MAP(Media, CWinAppEx)
//  ON_COMMAND(ID_FILE_PRINT_SETUP, &OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
END_MESSAGE_MAP()


// Media initialization

BOOL Media::InitInstance() {
String path;

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  path = iniFile.getAppDataPath(m_pszHelpFilePath);    path += _T("Store.csv");

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(MediaDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(MediaView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Media")); setTitle(_T("Media List"));

  view()->setFont(_T("Arial"), 12.0);

  channels.load();

  doc()->loadData(path);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


int Media::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void Media::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void Media::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

