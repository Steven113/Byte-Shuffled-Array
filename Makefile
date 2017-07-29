Driver.exe : Driver.cpp ShuffledArray.h
	g++ -g -o Driver.exe Driver.cpp

clean:
	del /F Driver.exe

run:
	Driver.exe

gadd:
	git add *.cpp
	git add *.h
	git add Makefile