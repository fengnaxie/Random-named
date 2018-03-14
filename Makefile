utf-8 := -D FILE_UTF_8

test: basename.cpp basename.h test.cpp
	g++ -Wall -O $(utf-8) -std=c++11 -o exeTest basename.cpp test.cpp 

test_debug: basename.cpp basename.h test.cpp
	g++ -Wall -g -O $(utf-8) -std=c++11 -o exeTest basename.cpp test.cpp 
