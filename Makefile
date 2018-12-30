# define the C compiler to use
CC = gcc
CXX = g++
# define any compile-time flags
CFLAGS = -Wall -g
CXXFLAGS = -std=c++11
RM = rm -f

# define the C++ source files
# SRCS = main.cpp server_module.cpp process_module.cpp rbtree_module.cpp
# SRCS = main.cpp server_module.cpp process_module.cpp setup.cpp time_module.cpp
SRCS = main.cpp server_module.cpp process_module.cpp connection_module.cpp setup.cpp time_module.cpp

# define the C++ object files
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(SRCS:.cpp=.h)
# define the executable file
TARGET = main

all:    $(TARGET)
	@echo  Simple compiler named main has been compiled

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o : main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp $(HEADERS)

server_module.o : server_module.cpp server_module.h
	$(CXX) $(CXXFLAGS) -c server_module.cpp server_module.h

process_module.o : process_module.cpp process_module.h
	$(CXX) $(CXXFLAGS) -c process_module.cpp process_module.h

connection_module.o : connection_module.cpp connection_module.h
	$(CXX) $(CXXFLAGS) -c connection_module.cpp connection_module.h

setup.o : setup.cpp setup.h
	$(CXX) $(CXXFLAGS) -c setup.cpp setup.h

time_module.o : time_module.cpp time_module.h
	$(CXX) $(CXXFLAGS) -c time_module.cpp time_module.h

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
clean:
	$(RM) *.o *~ $(TARGET)