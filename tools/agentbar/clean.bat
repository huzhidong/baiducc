
if exist output rd /q /s output
if not exist output mkdir output

set CMD_VS2010="%VS100COMNTOOLS%/../IDE/Devenv"

rem "build image plugin "
%CMD_VS2010% "ccl_imgex\ccl_imgex.vcxproj" /clean Release /project ccl_imgex

rem "build main activex "
%CMD_VS2010% "agentbarsrc\CCAgentBar.vcxproj" /clean Release /project CCAgentBar

rem "build test project"
%CMD_VS2010% "agentbartest\CCAgentBarTest.vcxproj" /clean Release /project CCAgentBarTest
