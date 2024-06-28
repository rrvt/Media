// Channels


#pragma once

#include "Expandable.h"
#include "IterT.h"


struct Channel {
String name;

  Channel() { }
  Channel(Channel& chn) {name = chn.name;}
 ~Channel() { }

  Channel& operator= (Channel& chn) {name = chn.name; return *this;}

  // Required for Insertion Sort, i.e. data = dtm;
  bool operator >= (Channel& r) {return name >= r.name;}
  bool operator == (Channel& r) {return name == r.name;}

  // Required for Binary Search
  bool operator== (TCchar* name) {return this->name == name;}
  bool operator<  (TCchar* name) {return this->name <  name;}
  bool operator>  (TCchar* name) {return this->name >  name;}
  };


class Channels;
typedef IterT<Channels, Channel> ChnIter;


class Channels {

Expandable<Channel, 2> data;

public:

           Channels() { }
          ~Channels() { }

  void     add( String& name);
  Channel* find(TCchar* name);

  void     load();
  void     store();

private:

  bool     isUnique(String& name);

  // returns either a pointer to datum at index i in array or zero

  Channel* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int   nData()      {return data.end();}                  // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename ChnIter;
  };


extern Channels channels;
