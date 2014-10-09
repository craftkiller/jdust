#!/bin/bash
#
echo "C++"
./cppperf js/dust-full.js dust/sample.dust
echo "Java"
cd java && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. java buzz.fizz.jdust.JPerformanceTest ../js/dust-full.js ../dust/sample.dust
