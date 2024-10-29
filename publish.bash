#!/bin/bash

# Convert all .txt files in the current directory
for file in *.*; do
    dos2unix "$file"
done
