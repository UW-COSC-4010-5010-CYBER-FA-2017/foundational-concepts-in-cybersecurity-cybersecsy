##############################
# Makefile
# Author: Wyatt Emery, Shaya Wolf
# Date: OCT 24, 2017
#
# COSC 4010/5010
# 
# this will compile and generate an executable for the various examples 
# 
##############################
PFUNCS=${EX1PATH}ProcessFunctions.h ${EX1PATH}ProcessFunctions.cpp
EX1PATH=Example1/Exemplar/
CXX=g++
CXXFLAGS=-ggdb -Wall -std=c++11

.PHONY: clean

all: example1 nonexample1 example2 nonexample2 example3 nonexample3

example1: Commander ProcessManager Reporter TestFile
nonexample1: Example1/NonExample/thread.cpp
	${CXX} ${CXXFLAGS} -pthread Example1/NonExample/thread.cpp -o nonexample1

example2: Example2/driver.cpp 
	${CXX} ${CXXFLAGS} Example2/driver.cpp -o example2
nonexample2: Example2/driverBad.cpp
	${CXX} ${CXXFLAGS} Example2/driverBad.cpp -o nonexample2
 
example3: Example3/driver.cpp Example3/DisjointSet.hpp
	${CXX} ${CXXFLAGS} Example3/driver.cpp -o example3
nonexample3: Example3/driverBad.cpp
	${CXX} ${CXXFLAGS} Example3/driverBad.cpp -o nonexample3

Commander: ${EX1PATH}Commander.cpp
	${CXX} ${CFLAGS} ${EX1PATH}Commander.cpp -o ex1_commander
ProcessManager: ${EX1PATH}ProcessManager.cpp ${PFUNCS}
	${CXX} ${CFLAGS} ${EX1PATH}ProcessManager.cpp ${PFUNCS} -o ex1_processManager
Reporter: ${EX1PATH}Reporter.cpp
	${CXX} ${CFLAGS} ${EX1PATH}Reporter.cpp -o ex1_reporter 
TestFile:
	/bin/cp ${EX1PATH}ex1_input.txt ./

clean: 
	/bin/rm -f *.o core.* ex1_commander ex1_reporter ex1_input.txt \
	 ex1_processManager example1 nonexample1 example2 nonexample2 \
	example3 nonexample3  

