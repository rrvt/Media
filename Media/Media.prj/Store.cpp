// Sample Data Store


#include "stdafx.h"
#include "Store.h"
#include "NotePad.h"


const int TabVal = 5;


Store      store;                                        // Global since all classes need access
static int ttlLng;



Datum* StoreSearch::operator() (TCchar* target) {
  if (!target || !*target || srchFld == StrSrchNil) return 0;

  reg.setPattern(target);   index = -1;   return (*this)++;
  }


Datum* StoreSearch::operator++ (int) {
TCchar* s;

  for (index++; index < store.nData(); index++) {
    Datum* dtm = store.data[index].p;

    switch (srchFld) {
      case StrSrchCom   : s = dtm->comment; break;
      case StrSrchTitle : s = dtm->title; break;
      case StrSrchChn   : s = dtm->channel; break;
      default           : return 0;
      }
    if (dtm && reg.match(s)) return dtm;
    }
  return 0;
  }


bool StoreSearch::del(Datum* dtm) {

  if (store.data[index].p != dtm) return false;

  store.data.del(index);   index--;   return true;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void Store::load(Archive& ar) {
CSVLex lex(ar);
Datum  dtm;

  data.clear();

  while (dtm.load(lex) == true) {
    data = dtm;
    }
  }


bool Datum::load(CSVLex& lex) {
String s;

  if (!getLexTok(lex, title)) return false;
  if (!getLexTok(lex, channel)) return false;
  if (!getLexTok(lex, s)) return false;        date << s;
  if (!getLexTok(lex, comment)) return false;
  if (!getLexTok(lex, s)) return false;        bobPresent     = s == _T("1");
  if (!getLexTok(lex, s)) return false;        maureenPresent = s == _T("1");

  return true;
  }


void Datum::clear() {
  title.clear(); channel.clear(); comment.clear();
  bobPresent = false; maureenPresent = false;   recentEdit = false;
  }


//enum CSVtokCode {NoToken, WhiteToken, StringToken, CommaToken, EolToken, EOFToken, IllegalToken};

bool Datum::getLexTok(CSVLex& lex, String& s) {
CSVtokCode code  = lex.get_token();    if (code == EOFToken) return false;
CSVtokCode code1 = lex.token1.code;

  if (code == StringToken && (code1 == CommaToken || code1 == EolToken)) {
    s = lex.token.name;  lex.accept_two_tokens(); return true;
    }

  if (code == CommaToken || code == EolToken) {s.clear();  lex.accept_token(); return true;}

  return false;
  }



void Store::store(Archive& ar) {
CSVOut  csv(ar);
StrIter iter(*this);
Datum*  dtm;

  for (dtm = iter(); dtm; dtm = iter++) dtm->store(csv);
  }


void Datum::store(CSVOut& csv) {
  csv << title.trim()   << _T(',');
  csv << channel.trim() << _T(',');
  csv << date           << _T(',');
  csv << comment.trim() << _T(',');
  csv << bobPresent     << _T(',');
  csv << maureenPresent;
  csv << vCrlf;
  }


void Store::display() {
StrIter iter(*this);
Datum*  dtm;
int     i;

  for (dtm = iter(), ttlLng = 0; dtm; dtm = iter++)
                                        {int lng = dtm->title.length();   if (lng > ttlLng) ttlLng = lng;}
  notePad.clear();

  for (dtm = iter(), i = 0; dtm; dtm = iter++, i++) {if (i) notePad << nCrlf;   dtm->display();}
  }


void Datum::display() {

  notePad << nClrTabs << nSetTab(ttlLng) << nSetTab(ttlLng+12) << nSetTab(ttlLng+24);
  notePad << nSetTab(ttlLng+30);
  notePad << title << nTab << channel;
  notePad << nTab << date;
  notePad << nTab << (bobPresent ? _T("Bob") : _T("  "));
  notePad << nTab << (maureenPresent ? _T("Maureen") : _T(""));
  notePad << nCrlf;

  if (!comment.isEmpty()) {
    notePad << nClrTabs << nSetTab(5);
    notePad << nTab << comment;
    notePad << nCrlf;
    }
  }



void Datum::copy(Datum& d) {
  title          = d.title;
  channel        = d.channel;
  date           = d.date;
  comment        = d.comment;
  bobPresent     = d.bobPresent;
  maureenPresent = d.maureenPresent;
  recentEdit     = d.recentEdit;
  }




#if 1
#else
WrapIter  iter(wrp);
WrapData* wd;
int       i;

  notePad << nClrTabs << nSetTab(TabVal) << nTab;       // The tab is set to the same value as in wrap

  for (wd = iter(), i = 0; wd; wd = iter++, i++) {
    if (i) notePad << nTab;

    notePad << wd->line << nCrlf;
    }

  return i;
#endif


#if 0
Datum* Store::find(TCchar* target) {regExpr.setPattern(target);   findX = -1;   return findNext();}


Datum* Store::findNext() {
  for (findX++; findX < nData(); findX++) {
    Datum* dtm = data[findX].p;

    if (dtm && regExpr.match(dtm->title)) return dtm;
    }

  return 0;
  }


bool Store::delDatum(Datum* dtm) {

  if (data[findX].p != dtm) return false;

  data.del(findX);   findX--;   return true;
  }
#endif

