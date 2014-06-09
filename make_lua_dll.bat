@echo off

set path=%PATH%;d:\devel\MinGW\bin

gcc -c -o murmur.o murmur.c
gcc -O2 -s -shared -o murmur.dll murmur.o -L. -llua52
rem strip --strip-unneeded murmur.dll
del /q /f *.o

pause
