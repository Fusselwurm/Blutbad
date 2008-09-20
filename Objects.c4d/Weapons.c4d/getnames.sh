#!/bin/bash

for i in $( ls -F | grep /); do
  cat $i/Names.txt | grep DE
  cat $i/Names.txt | grep US
  echo $i
done
