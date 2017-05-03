CXX?=g++
CXXFLAGS=-std=c++14 -I../include -Wall -pedantic -Weffc++
LDFLAGS=-pthread

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ./,$(notdir $(CPP_FILES:.cpp=.o)))

tests: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

rebuild: clean tests

all: tests

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

-include $(DEPS)

clean:
	rm -f tests *.d $(OBJ_FILES)
