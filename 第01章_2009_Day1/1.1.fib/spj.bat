@echo off

set file=fib

submit.exe
if not exist %file%.out echo "output not found"
spjudge.exe %file%.in %file%.out
del %file%.out
pause
