# Compilation flags.
#CPPFLAGS = -std=c++11 -O0 -ggdb -DDEBUG -fno-inline
CPPFLAGS = -std=c++11 -O3
LDFLAGS = -pthread

# Setting path.
VPATH = ../src
CPPFLAGS += -I../src

all : BB_test Match_test

BB_test : BB_test.cpp BoundedBuffer.hpp BoundedBuffer.cpp Echo.hpp Echo.cpp \
		iowrappers.hpp iowrappers.cpp SourceSink.hpp

Match_test : Match_test.cpp Match.hpp Match.cpp \
		iowrappers.hpp iowrappers.cpp SourceSink.hpp
