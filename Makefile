DriverGCC.exe : Driver.cpp ShuffledArray.h ByteShuffledArray.h
	g++ -g -o DriverGCC.exe Driver.cpp -std=c++11

DriverWin.exe : Driver.cpp ShuffledArray.h ByteShuffledArray.h
	cl /EHsc Driver.cpp /link /out:DriverWin.exe

clean:
	del /F *.exe

run:
	DriverGCC.exe

gadd:
	git add *.cpp
	git add *.h
	git add Makefile