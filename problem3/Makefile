CXX      = g++-8
CXXFLAGS = -std=c++17 -Wall
LDFLAGS  = -pthread

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all : task1 

task1 : task1.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean :
	rm -rf task1 *.o
