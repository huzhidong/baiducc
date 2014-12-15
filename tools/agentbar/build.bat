
if exist output rd /q /s output
if not exist output mkdir output

set LIBINIT="%VS100COMNTOOLS%/../Tools/vsvars32.bat"
set CMD_VS2010="%VS100COMNTOOLS%/../IDE/Devenv"

rem "build image plugin"
%CMD_VS2010% "ccl_imgex\ccl_imgex.vcxproj" /rebuild Release /project ccl_imgex

rem "build main activex"
%CMD_VS2010% "agentbarsrc\CCAgentBar.vcxproj" /rebuild Release /project CCAgentBar

rem "build test project"
%CMD_VS2010% "agentbartest\CCAgentBarTest.vcxproj" /rebuild Release /project CCAgentBarTest

call %LIBINIT%
rem "create cab package"
copy .\bin\cabarc.exe .\
copy .\bin\signcode.exe .\
cabarc.exe -s 6144 n .\bin\CCAgentBar.cab .\bin\CCAgentBar.inf .\bin\CCAgentBar.ocx .\bin\ccl_imgex.dll
signcode.exe -spc .\bin\CCAgentBar.spc -v .\bin\CCAgentBar.pvk .\bin\CCAgentBar.cab

copy .\bin\CCAgentBar.ocx output\
copy .\bin\ccl_imgex.dll output\
copy .\bin\CCAgentBar.cab output\
copy .\bin\CCAgentBar.pdb output\
copy .\doc\develop_manual.doc output\
