CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = testbst
OBJS = intbst.o testbst.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

intbst.o: intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c intbst.cpp

testbst.o: testbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c testbst.cpp

clean:
	rm -f $(OBJS) $(TARGET)
