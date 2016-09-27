#!/bin/bash
echo "Compiling program from source"
g++-5 -std=c++14 -o bin/setport src/setport.cpp
echo "Compiling test program :: run- './bin/testing-setport' for a test report"
g++-5 -std=c++14 -o bin/testing-setport src/testing-setport.cpp
echo "Installing progam to path"


cp bin/setport /usr/local/bin/setport

# Set up folders for configurations
mkdir /usr/local/etc/setport
# Symlink in files from the source directory
ln -s ~/workspace/setport/txt/setport.usage_en.txt /usr/local/etc/setport/setport.usage_en.txt
ln -s ~/workspace/setport/txt/setport.about_en.txt /usr/local/etc/setport/setport.about_en.txt
ln -s ~/workspace/setport/txt/setport.warnings_en.txt /usr/local/etc/setport/setport.warnings_en.txt
# Spanish
ln -s ~/workspace/setport/txt/setport.usage_es.txt /usr/local/etc/setport/setport.usage_es.txt
ln -s ~/workspace/setport/txt/setport.about_es.txt /usr/local/etc/setport/setport.about_es.txt
ln -s ~/workspace/setport/txt/setport.warnings_es.txt /usr/local/etc/setport/setport.warnings_es.txt

