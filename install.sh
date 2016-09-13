#!/bin/bash
echo "Compiling program from source"
g++ -std=c++11 -o bin/setport src/setport.cpp
echo "Installing progam to path"
cp bin/setport /usr/local/bin/setport
