import matplotlib.pyplot as plt
import os, sys
import numpy as np

tamanhos = [10, 100, 1000, 10000, 100000, 1000000]
tempos_execucao = {tam: [] for tam in tamanhos}
algs = ["Merge_Sort"]

for alg in algs:
    for tamanho in tamanhos:
        arquivo = f"../../output/n{tamanho}/{alg}.out"
        
        with open(arquivo, 'r') as f:
            lines = f.readlines()

            # Ignorando o nome do algoritmo e o tempo médio
            lines = lines[1:-1]
            # Assumindo que cada linha contém um tempo de execução
            tempos_execucao[tamanho] = [float(line.split(': ')[1]) for line in lines if ': ' in line]

    # Criar o gráfico
    plt.figure(figsize=(10,5))
    plt.boxplot([tempos_execucao[tam] for tam in tamanhos], labels=[str(tam) for tam in tamanhos])

    plt.xlabel('Tamanho da Instância')
    plt.ylabel('Tempo de Execução')
    plt.title(f'Gráfico: {alg}')
    plt.grid(True)

    plt.savefig(f"../../graphs/{alg}.png", dpi=200)
