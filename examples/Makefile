CXX=g++
CXXFLAGS=-std=c++14 -I../include

PROGRAMS=$(patsubst %.cpp, %, $(wildcard *.cpp))
DEPS=$(patsubst %.cpp, %.d, $(wildcard *.cpp))

all: $(PROGRAMS)

%: %.cpp Makefile
	$(CXX) $< -MMD -o $@ $(CXXFLAGS)

-include $(DEPS)

clean:
	rm -f $(PROGRAMS) *.d
