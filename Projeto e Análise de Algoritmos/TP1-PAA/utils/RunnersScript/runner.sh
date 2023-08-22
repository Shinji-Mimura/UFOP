#!/bin/bash

cd ../../src
make all


for j in 10 100 1000 10000 100000 1000000; do
        make run ALG=2 TAM="$j" 
done