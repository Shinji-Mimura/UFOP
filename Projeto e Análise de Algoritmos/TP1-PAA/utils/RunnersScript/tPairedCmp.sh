#!/bin/bash

echo "[+] Gerando Comparações de Testes T Entre Algoritmos"

cd ../StatisticsGen

for i in 10 100 1000 10000 100000 1000000; do
    mkdir -p ../../output/TPairedTests/n$i
    python3.10 TPairedCmp.py $i Merge_Sort Radix_Sort > ../../output/TPairedTests/n$i/Merge_Sort-X-Radix_Sort.out
    python3.10 TPairedCmp.py $i Merge_Sort Insertion_Sort > ../../output/TPairedTests/n$i/Merge_Sort-X-Insertion_Sort.out
done

echo "[+] Comparações Finalizadas!"