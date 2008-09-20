#!/bin/bash

for i in $( ls -F | grep /); do
  cp -v Graphics.png ActMap.txt $i/
done
