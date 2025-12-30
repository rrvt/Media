// MediaDoc.h : interface of the MediaDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "PathDlgDsc.h"
#include "Store.h"

class FindDlg;


enum DataSource {NotePadSrc, StoreSrc, FontSrc};

extern TCchar* GlobalSect;
extern TCchar* DBPathKey;



class MediaDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;
DisplayDir  lastDir{LowToHigh};

String      dataPath;
String      firstName;
String      secondName;
bool        firstNamePrsnt{false};
bool        secondNamePrsnt{false};


protected: // create from serialization only

  MediaDoc() noexcept;
  DECLARE_DYNCREATE(MediaDoc)

public:

  DataSource dataSrc() {return dataSource;}

  void       display(DataSource ds = NotePadSrc);

  TCchar*    getPathDlg(TCchar* helpPath);
  void       loadData(TCchar* path);
  void       saveData(DataSource src);

  void       serialize(Archive& ar);

// Implementation
public:

  virtual ~MediaDoc();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void       testLine(int n);
  void       wholePage();
  StrSrchFld getSrchTgt(String& target);
  void       refresh(DisplayDir dir = LowToHigh);

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFind();
  afx_msg void onAddMedia();
  afx_msg void onEditMedia();
  afx_msg void onDelMedia();
  afx_msg void onRefresh();
  afx_msg void onSortName();
  afx_msg void onSortDate();
  afx_msg void onSetWatcherNames();
  afx_msg void onFileSave();
  afx_msg void onSpecifyPath();
  };

