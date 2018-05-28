@echo off

set file=project

submit.exe
if not exist %file%.out goto no
spjudge.exe %file%.in %file%.out
del %file%.out
pause
