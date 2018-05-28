@echo off

set file=fareway

submit.exe
if not exist %file%.out goto no
spjudge.exe %file%.in %file%.out %file%.std
del %file%.out
pause
