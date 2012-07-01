@echo off

set path=%PATH%;d:\devel\MinGW\bin

gcc -c -o MurmurHash64A.o MurmurHash64A.c
gcc -O2 -s -o MurmurHash64A.exe MurmurHash64A.o
del /q /f *.o

pause