# Compilation flags.
#CPPFLAGS = -std=c++11 -O0 -ggdb -DDEBUG -fno-inline
CPPFLAGS = -std=c++11 -O3
LDFLAGS = -pthread

# Setting path.
VPATH = ../src
CPPFLAGS += -I../src

all : BB_test Match_test Replace_test

BB_test : BB_test.cpp BoundedBuffer.cpp Echo.cpp iowrappers.cpp

Match_test : Match_test.cpp Match.cpp iowrappers.cpp

Replace_test : Replace_test.cpp Replace.cpp iowrappers.cpp
