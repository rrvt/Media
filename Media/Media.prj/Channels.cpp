// Channels


#include "stdafx.h"
#include "Channels.h"
#include "IniFileEx.h"

Channels channels;


void Channels::add(String& name) {

  if (!isUnique(name)) return;

  Channel chn;   chn.name = name;   data = chn;
  }


Channel* Channels::find(TCchar* name) {
ChnIter  iter(*this);
Channel* chn;

  for (chn = iter(); chn; chn = iter++) if (chn->name == name) return chn;

  return 0;
  }



static TCchar* Section       = _T("Channels");
static TCchar* KeyPrefix     = _T("Channel");
static TCchar* NoChannelsKey = _T("NoChannels");


void Channels::load() {
Channel chn;
int     i;
int     n;
String  key;

  iniFile.read(Section, NoChannelsKey, n);

  for (i = 0; i < n; i++) {
    key.format(_T("%s%03i"), KeyPrefix, i);

    iniFile.read(Section, key, chn.name);

    if (isUnique(chn.name)) data = chn;
    }
  }


bool Channels::isUnique(String& name) {
int      lng    = name.length();
int      prfLng = lng > 3 ? 3 : lng;
String   prfx   = name.substr(0, prfLng);
ChnIter  iter(*this);
Channel* chn;

  for (chn = iter(); chn; chn = iter++)
                       if (prfx == chn->name.substr(0, prfLng)) {name = chn->name;   return false;}
  return true;
  }


void Channels::store() {
ChnIter  iter(*this);
Channel* chn;
int      i;
String   key;

  iniFile.write(Section, NoChannelsKey, nData());

  for (chn = iter(), i = 0; chn; chn = iter++, i++)
                {key.format(_T("%s%03i"), KeyPrefix, i);   iniFile.write(Section, key, chn->name);}
  }


