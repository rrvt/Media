// Channels


#include "stdafx.h"
#include "Channels.h"
#include "IniFile.h"

Channels channels;


void Channels::add(TCchar* name) {
  if (!find(name)) {
  Channel chn;
  chn.name = name;
  data = chn;
  }
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

    iniFile.read(Section, key, chn.name);   data = chn;
    }
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


