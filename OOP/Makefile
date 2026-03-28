# Simple Makefile for OOP project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -pthread
TARGET = main.exe
SRCS = main.cpp BankAccount.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
