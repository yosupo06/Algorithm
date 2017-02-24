CXXFLAGS=-std=c++11 -Wall -lpthread
INCLUDE = -I./ -I./tests/
SOURCES := $(wildcard tests/*.cpp)
GTEST_ALL = tests/gtest/gtest-all.cc
$(info $(SOURCES))
test: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SOURCES) $(GTEST_ALL) -o test
clean:
	$(RM) test
