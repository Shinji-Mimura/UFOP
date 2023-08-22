#!/bin/bash

echo "[+] Gerando Testes T Pareados"

cd ../StatisticsGen

for i in 10 100 1000 10000 100000 1000000; do
    mkdir -p ../../output/TPairedTests/n$i
    python3.10 TPairedAlg.py $i Merge_Sort > ../../output/TPairedTests/n$i/Merge_Sort.out 
done

echo "[+] Testes Finalizados!"