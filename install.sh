#!/bin/bash
echo "Compiling program from source"
g++-5 -std=c++14 -o bin/setport src/setport.cpp
echo "Compiling test program :: run- './bin/testing-setport' for a test report"
g++-5 -std=c++14 -o bin/testing-setport src/testing-setport.cpp
echo "Installing progam to path"


cp bin/setport /usr/local/bin/setport

# Set up folders for configurations
mkdir /usr/local/etc/setport
cp txt/* /usr/local/etc/setport/
