// MediaDoc.h : interface of the MediaDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "Store.h"

class FindDlg;


enum DataSource {NotePadSrc, StoreSrc, FontSrc};


class MediaDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

String      dataPath;

protected: // create from serialization only

  MediaDoc() noexcept;
  DECLARE_DYNCREATE(MediaDoc)

public:

  DataSource dataSrc() {return dataSource;}

  void       display(DataSource ds);

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

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFind();
  afx_msg void onAddMedia();
  afx_msg void onEditMedia();
  afx_msg void onDelMedia();
  afx_msg void onRefresh();
  afx_msg void onFileSave();
  };

