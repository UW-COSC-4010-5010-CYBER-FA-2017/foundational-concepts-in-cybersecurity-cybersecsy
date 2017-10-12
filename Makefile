##############################
# Makefile
# Author: Wyatt Emery
# Date: SEP 27, 2017
#
# COSC 4785, Homework 2
# 
# this will compile and generate an executable from program2.cpp program2.lpp
# Lexeme.cpp and the Bison file
##############################

CXX=g++
CXXFLAGS=-ggdb -Wall -std=c++11

.PHONY: clean

example4: Example4/driver.cpp Example4/DisjointSet.hpp
	${CXX} ${CXXFLAGS} Example4/driver.cpp -o example4

clean: 
	/bin/rm -f *.o core.* example4

