# Compilation flags.
#CPPFLAGS = -std=c++11 -O0 -ggdb -DDEBUG -fno-inline
CPPFLAGS = -std=c++11 -O3
LDFLAGS = -pthread

# Setting path.
VPATH = ../src
CPPFLAGS += -I../src

all : BB_test Match_test

BB_test : BB_test.cpp BoundedBuffer.hpp BoundedBuffer.cpp tasks.hpp Task.cpp \
	Echo.cpp iowrappers.hpp iowrappers.cpp SourceSink.hpp

Match_test : Match_test.cpp tasks.hpp Task.cpp Match.cpp iowrappers.hpp \
	iowrappers.cpp SourceSink.hpp
