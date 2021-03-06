DriverWin.exe : Driver.cpp ShuffledArray.h ByteShuffledArray.h TestingMacros.h
	cl /EHsc Driver.cpp /link /out:DriverWin.exe

DriverGCC.exe : Driver.cpp ShuffledArray.h ByteShuffledArray.h Random.h TestingMacros.h
	g++ -g -Wall -o DriverGCC.exe Driver.cpp -std=c++11

clean:
	del /F *.exe

run:
	DriverWin.exe

gadd:
	git add *.cpp
	git add *.h
	git add Makefile

PushToRepo:
	git push -u origin master

PullMasterFromRepo:
	git pull https://github.com/Steven113/Byte-Shuffled-Array.git master