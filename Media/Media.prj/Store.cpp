// Sample Data Store


#include "stdafx.h"
#include "Store.h"
#include "NotePad.h"


const int TabVal = 5;


Store      store;                                        // Global since all classes need access
static int ttlLng;



Datum* StoreSearch::operator() (TCchar* target) {
Datum* dtm;

  if (!target || !*target || srchFld == StrSrchNil) return 0;

  reg.setPattern(target);

  dtm = iter(StrIter::Rev);   return compare(dtm) ? dtm : (*this)++;
  }


Datum* StoreSearch::operator++ (int) {
Datum* dtm;

  for (dtm = iter--; dtm; dtm = iter--) if (compare(dtm)) return dtm;

  return 0;
  }


bool StoreSearch::compare(Datum* dtm) {

  switch (srchFld) {
    case StrSrchCom   : return reg.match(dtm->comment);
    case StrSrchTitle : return reg.match(dtm->title);
    case StrSrchChn   : return reg.match(dtm->channel);
    }
  return false;
  }


bool StoreSearch::del(Datum* dtm) {

  if (iter.current() != dtm) return false;

  iter.remove(StrIter::Rev);   return true;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void Store::load(Archive& ar) {
CSVLex lex(ar);
Datum  dtm;

  data.clear();

  while (dtm.load(lex) == true) {dtm.setKey(sortKey);   data = dtm;}
  }


bool Datum::load(CSVLex& lex) {
String s;

  if (!getLexTok(lex, title)) return false;

  if (!getLexTok(lex, channel)) return false;
  if (!getLexTok(lex, s))       return false;   date << s;
  if (!getLexTok(lex, comment)) return false;
  if (!getLexTok(lex, s))       return false;   bobPresent     = s == _T("1");
  if (!getLexTok(lex, s))       return false;   maureenPresent = s == _T("1");

  return true;
  }


void Datum::clear() {
  key.clear();   title.clear();   channel.clear();  date.clear();   comment.clear();
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


void Store::setSort(SortKey k) {
StrIter iter(*this);
Datum*  dtm;

  sortKey = k;

  for (dtm = iter(); dtm; dtm = iter++) dtm->setKey(sortKey);
  }


void Datum::setKey(SortKey sortKey) {
  key.clear();

  if (sortKey == NameSort) key = title;   key += date.format(_T("%Y%m%d%H%M%S"));

  key.trim();
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


void Store::display(DisplayDir dir) {
StrIter iter(*this);
Datum*  dtm;

  for (dtm = iter(), ttlLng = 0; dtm; dtm = iter++)
                                 {int lng = dtm->title.length();   if (lng > ttlLng) ttlLng = lng;}
  ttlLng = ttlLng*13/16;

  notePad.clear();

  notePad << _T("Films Recorded: ") << nData() << nCrlf << nCrlf;

  if (dir == LowToHigh) for (dtm = iter();             dtm; dtm = iter++) dtm->display();
  else                  for (dtm = iter(StrIter::Rev); dtm; dtm = iter--) dtm->display();
  }


void Datum::display() {

  notePad << nClrTabs << nSetTab(1) << nSetTab(ttlLng + 1) << nSetRTab(ttlLng+24);
  notePad << nSetTab(ttlLng+27) << nSetTab(ttlLng+33);

  notePad << nTab << title;
  notePad << nTab << channel;
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
  key            = d.key;
  title          = d.title;
  channel        = d.channel;
  date           = d.date;
  comment        = d.comment;
  bobPresent     = d.bobPresent;
  maureenPresent = d.maureenPresent;
  recentEdit     = d.recentEdit;
  }




