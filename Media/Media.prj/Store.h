// Sample Data Store


#pragma once
#include "Archive.h"
#include "CSVLex.h"
#include "CSVOut.h"
#include "Date.h"
#include "DevBase.h"
#include "ExpandableP.h"
#include "IterT.h"
#include "RegExpr.h"
#include "Wrap.h"



// This is the Datum record.  It can be a complex as necessary.
// Set will accept any reasonable group of entities and then will divide up the input into fields in
// the data.
// Get will return any grouping of data desired from the record, or there might be multiple get methods
// that will retrieve invidual or groups of fields.
// Note, the copy constructor and operator often call a private function that will do all the copying.

class Datum {
public:
String title;
String channel;
Date   date;
String comment;
bool   bobPresent;
bool   maureenPresent;

bool   recentEdit;

  Datum() : bobPresent(false), maureenPresent(false), recentEdit(false) { }
  Datum(Datum& d) {copy(d);}
 ~Datum()        { }

  void     clear();

  bool     load( CSVLex& lex);
  void     store(CSVOut& csv);

  void     display();

  Datum&   operator= (Datum& d) {copy(d); return *this;}

  bool     operator== (Datum& d) {return title == d.title;}
  bool     operator!= (Datum& d) {return title != d.title;}
  bool     operator>  (Datum& d) {return title >  d.title;}
  bool     operator<  (Datum& d) {return title <  d.title;}
  bool     operator>= (Datum& d) {return title >= d.title;}
  bool     operator<= (Datum& d) {return title <= d.title;}

private:

  bool getLexTok(CSVLex& lex, String& s);

  void copy(Datum& d);
  };


// Define an object to hold a pointer to each datum.  When sorting, the pointer is moved, not the
// datum (which could be large)

typedef DatumPtrT<Datum> DatumP;

// Define the iterator used to look at the data in the datastore.  It is here so that it can be friended

class Store;
typedef IterT<Store, Datum> StrIter;                        // Iterator for the Store


// This is the main store.  I think of it as a permanent home for the data while the program is running.
// The Expandable array deals with the uncertainty of the amount of data as it expands by doubling in
// length each time it has to expand.
// In this example, we provide a way to load it from a file, the details of which are up to the Datum
// class.  The data can be stored in a file, again the details of each record are enclosed in the Datum
// class.  We can add something to the store from the user or some other source (TBD).  In this example
// a sort option is provided to change the order of the data in the array.
// Finally, the destructor returns the allocated Datum records back to the heap (see cpp file).

class Store {

ExpandableP<Datum, DatumP, 2> data;

public:

         Store() { }
        ~Store() { }

  void   load( Archive& ar);
  void   store(Archive& ar);

  bool   isEmpty() {return data.end() == 0;}

  void   add(Datum& d) {data = d;}
  void   add(Datum* d) {data = d;}

#if 0
  RegExpression                 regExpr;
  int                           findX;
  Datum* find(TCchar* target);
  Datum* findNext();
  bool   delDatum(Datum* dtm);
#endif

  void   display();

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  Datum* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  // returns number of data items in array
  int   nData()      {return data.end();}

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StrIter;
  friend class    StoreSearch;
  };



enum StrSrchFld {StrSrchNil, StrSrchTitle, StrSrchChn, StrSrchDate, StrSrchCom};

class StoreSearch {

Store&        store;
int           index;
StrSrchFld    srchFld;
RegExpression reg;

public:

  StoreSearch(Store& str) : store(str), index(-1), srchFld(StrSrchNil) { }
 ~StoreSearch() { }

  void   setFld(StrSrchFld fld) {srchFld = fld;}

  Datum* operator() (TCchar* target);
  Datum* operator++ (int);
  bool   del(Datum* dtm);

private:

  StoreSearch() : store(*(Store*)0) { }
  };


extern Store store;                                   // Sometimes there only needs to one object

