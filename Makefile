CXXFLAGS=-std=c++14 -O2 -Wall -lpthread
INCLUDE = -I./ -I./tests/
SOURCE = tests/main_test.cpp
HEADERS := $(wildcard tests/*.h)
GTEST_ALL = tests/gtest/gtest-all.cc

test: $(SOURCE) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SOURCE) $(GTEST_ALL) -o test
	
clean:
	$(RM) test
