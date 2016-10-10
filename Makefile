build:
	g++ icndb.cpp -o icndb -std=c++11 `pkg-config --libs --cflags libcurl`
