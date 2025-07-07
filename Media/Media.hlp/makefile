

Media.chm : *.htm Media.hhp Media.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" Media


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist Media.chm del /F Media.chm


Release/Media.chm : Media.chm
  copy $(MAKEDIR)\Media.chm  $(MAKEDIR)\..\Release\Media.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist Media.chm del /F Media.chm
  cd $(MAKEDIR)


Debug/Media.chm : Media.chm
  copy $(MAKEDIR)\Media.chm  $(MAKEDIR)\..\Debug\Media.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist Media.chm del /F Media.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/Media.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/Media.chm


