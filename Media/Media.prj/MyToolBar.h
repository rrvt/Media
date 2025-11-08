// My ToolBar


#pragma once
#include "TBMenu.h"

//#define ButtonDefs
#define DocViewTB


#ifdef ButtonDefs
#include "TBButton.h"
#include "TBEditBox.h"

#ifdef DocViewTB
#else
#include "TBCbxMenu.h"
#endif
#include "TBCboBx.h"
#endif
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

#ifdef ButtonDefs

TBButton  button;
TBEditBox editBox;

#ifdef DocViewTB

TBMenu    menu1;

#else

TBCbxMenu cbxMenu1;

#endif

TBCboBx   cboBx;

#ifdef DocViewTB

TBMenu    saveMenu;

#else


#endif
#endif

TBMenu    menu;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool    addButton( uint id, TCchar* caption);
  bool    addEditBox(uint id, int     noChars);
  CString getText(uint id);

  bool    addMenu(   uint id, int     idr, TCchar* caption);

#ifdef DocViewTB

  bool    addMenu(   uint id, int     idr, int     index);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);

#else

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
  void    dispatch(uint id);

#endif

  bool    addCBx(    uint id);
  bool    addCBx(    uint id, int     idr, TCchar* caption);
  bool    addCbxItem(uint id, TCchar* txt, int data);
  bool    addCBx(    uint id, CbxItem cbxItem[], int n, TCchar* caption);
  bool    addCbxItemSorted(uint id, TCchar* txt, int data);
  void    setCaption(uint id, TCchar* caption);
  void    setWidth(uint id);
  bool    getCurSel( uint id, String& s, int& data);
  };

