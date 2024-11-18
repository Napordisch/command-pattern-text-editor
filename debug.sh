#!/bin/bash
clang++ -std=c++17 src/*.cpp -o build/command-text-editor -g && lldb ./build/command-text-editor
