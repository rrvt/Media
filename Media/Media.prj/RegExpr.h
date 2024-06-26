// Regular Expression Match
// rrvt 11/16/96



// Regular expressions are made up of the following meta characters and ordinary
// characters:
//
//    ^  - At beginning of pattern indicates matches the beginning of line,
//         otherwise just an ordinary character.
//    $  - At end of pattern indicates matches the end of the line, otherwise
//         just an ordinary character.
//    .  - Matches any character.
//    [] - The set of characters contained within the brackets matches the
//         character at the corresponding position in the line
//    *  - Kleene Closure of the preceding pattern (Tchar, metachar or set).
//    \  - Escape character, next character is used literally (even metachar).
//         \t indicates the tab character.
// Sets
//    ^  - When the first Tchar in the set [^...] indicates that the match is for
//         any character NOT in the set.
//    -  - When dash (-) is not the first or last character in the set,
//         indicates that a range of characters is to be placed in the set.  For
//         example [0-9] indicates all the digits.
//    \  - When not the last character indicates that the next character is to
//         be placed in the set literally (not a meta character).  For example
//         [0-9\-] indicates the digits and dash is in the set.


#pragma once
#include "Expandable.h"
#include "IterT.h"


typedef void processLine(String& line);


// Translate a file name with wildcard characters into a regular expression

class RegExpression {

enum {SetSize   =   8};                                    //, NoPattern = 512
enum PatKey {nilKey, Ch, Bol, Eol, CharClass, KleeneClosure, Any, EndOfPat};


typedef struct {
PatKey key;
Tchar  ch;
ulong  set[SetSize];
} Pattern;

typedef IterT<RegExpression, Pattern> ReIter;

typedef Expandable<Pattern, 32> PatVector;
PatVector                       pattern;

public:

         RegExpression()            {pattern[0].key = nilKey; }
         RegExpression(TCchar* pat) {pattern[0].key = nilKey; setPattern(pat);}
        ~RegExpression() {}

  bool   setWildCardPattern(TCchar* name);
  bool   setPattern(TCchar* pat);

  bool   match(TCchar* stg);          // Match string against previously set pattern

private:

  Tchar* unanchoredMatch(TCchar* line, int index);
  Tchar* anchoredMatch(  TCchar* line, int index);
  short  omatch(    TCchar* s,  Pattern* pat);
  bool   collectSet(TCchar** s, Pattern* p);
  bool   installKleene(short i);
  void   clrSet(ulong set[]);
  void   setBit(Tchar ch, ulong set[]);
  bool   inSet( Tchar ch, ulong set[]);
  void   invertSet(ulong set[]);

  // returns either a pointer to datum at index i in array or zero

  Pattern* datum(int i) {return 0 <= i && i < nData() ? &pattern[i] : 0;}

  int   nData()      {return pattern.end();}                   // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) pattern.del(i);}

  friend typename ReIter;
  };


