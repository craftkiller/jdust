#!/bin/bash
#
echo "C++"
time ./cppperf js/dust-full.js dust/sample.dust
echo "Java"
cd java && time LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. java buzz.fizz.jdust.JPerformanceTest ../js/dust-full.js ../dust/sample.dust
