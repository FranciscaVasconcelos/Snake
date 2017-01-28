# Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS = test.o

# Executable name
EXENAME = test

# Macros
CC = g++
CCOPTS = -c -g -O0 -Wall -Wno-deprecated
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# Testing for OS X v Linux
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -framework GLUT -framework OpenGL -framework Cocoa
else
	LIBS = -lGL -lGLU -lglut
endif

# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS)

# Object files
flightsim.o : test.cpp
	$(CC) $(CCOPTS) test.cp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null