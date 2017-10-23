##############################
# Makefile
# Author: Wyatt Emery
# Date: FEB 6, 2017
#
#
# 
# this will compile and generate executables from Commander.cpp ProcessManager.cpp 
# and Reporter.cpp
##############################

CC=g++
CFLAGS=-ggdb -Wall
PFUNCS=ProcessFunctions.h ProcessFunctions.cpp

.PHONY: clean

all: Commander ProcessManager Reporter

Commander: Commander.cpp
	${CC} ${CFLAGS} Commander.cpp -o commander

ProcessManager: ProcessManager.cpp ${PFUNCS}
	${CC} ${CFLAGS} ProcessManager.cpp ${PFUNCS} -o processManager

Reporter: Reporter.cpp
	${CC} ${CFLAGS} Reporter.cpp -o reporter 

clean: 
	/bin/rm -f *.o commander processManager reporter
