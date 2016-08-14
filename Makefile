utf-8 := -D FILE_UTF_8

libfullname.so: fullname.cpp fullname.h
	g++ -Wall -O $(utf-8) -std=c++11 -o libfullname.so -fPIC -shared fullname.cpp

clean: libfullname.so
	rm -rf libfullname.so
