#!/bin/bash
#
./cppdust js/dust-full.js dust/sample.dust
cd java && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. java buzz.fizz.jdust.JDust ../js/dust-full.js ../dust/sample.dust
