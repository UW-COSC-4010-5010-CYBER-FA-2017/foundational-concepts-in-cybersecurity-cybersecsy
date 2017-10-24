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
PFUNCS=ProcessFunctions.h ProcessFunctions.cpp
EX2PATH=Example2/Exemplar/
CXX=g++
CXXFLAGS=-ggdb -Wall -std=c++11

.PHONY: clean

example2: Commander ProcessManager Reporter
nonexample2: /Example2/NonExample/thread.cpp
	${CXX} ${CXXFLAGS} Example2/NonExample/thread.cpp -o nonexample2

example3: Example3/driver.cpp 
	${CXX} ${CXXFLAGS} Example3/driver.cpp -o example3
nonexample3: Example3/driverBad.cpp

	${CXX} ${CXXFLAGS} Example3/driverBad.cpp -o nonexample3 
example4: Example4/driver.cpp Example4/DisjointSet.hpp
	${CXX} ${CXXFLAGS} Example4/driver.cpp -o example4
nonexample4: Example4/driverBad.cpp
	${CXX} ${CXXFLAGS} Example4/driverBad.cpp -o nonexample4

Commander: ${EX2PATH}Commander.cpp
	${CC} ${CFLAGS} ${EX2PATH}Commander.cpp -o commander
ProcessManager: ${EX2PATH}ProcessManager.cpp ${PFUNCS}
	${CC} ${CFLAGS} ${EX2PATH}ProcessManager.cpp ${PFUNCS} -o processManager
Reporter: ${EX2PATH}Reporter.cpp
	${CC} ${CFLAGS} ${EX2PATH}Reporter.cpp -o reporter 

clean: 
	/bin/rm -f *.o core.* example4 nonexample4 

