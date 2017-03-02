all: web

web : main.cpp HttpState.cpp Util.cpp HttpRequestParser.cpp HttpRequestParser.hpp HttpState.hpp
	g++ -Wall -g -O0 -ggdb -std=c++11 $^ -o $@

clean:
	rm -rf web
