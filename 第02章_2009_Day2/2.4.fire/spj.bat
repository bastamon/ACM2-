@echo off

set file=fire

if not exist %file%.in echo internal error

submit.exe
if not exist %file%.out goto no
set line=0
for /f %%i in ('fc %file%.out %file%.std') do set /a line+=1
if /i %line% neq 2 goto no
echo yes
goto end
:no
echo no
:end
del %file%.out
pause
