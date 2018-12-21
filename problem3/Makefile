CXX      = g++-8
CXXFLAGS = -std=c++17 -Wall
LDFLAGS  = -pthread

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all : task1 task2

task1 : task1.o
	$(CXX) $(LDFLAGS) $^ -o $@

task2 : task2.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean :
	rm -rf task1 task2 *.o
