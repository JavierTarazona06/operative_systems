#!/bin/bash

echo "running tests, output will be in "test-output.text""


#Usage is: <virtual_size> <page_size> <physical_size> <replacement_algo> <numberThreads> <time_seconds> <report_file_name>


#clock virtual
./PartASim 8 8 8 1 1 10 "test-output.text"
./PartASim 8 8 8 1 1 10 "test-output.text"
./PartASim 16384 8 8 1 1 10 "test-output.text"
./PartASim 1000000000 8 1000000 1 1 10 "test-output.text"

#second chance virtual
#./PartASim 1024 256 2048 1 12 10 "test-output.text"
#./PartASim 2048 256 2048 1 12 10 "test-output.text"
#./PartASim 4096 256 2048 1 12 10 "test-output.text"