import os
import pandas as pd
import matplotlib.pyplot as plt

# Caminho dos arquivos e nomes dos algoritmos
folders = ['n10', 'n100', 'n1000', 'n10000', 'n100000', 'n1000000']
algorithms = ["Insertion_Sort","Merge_Sort",'Radix_Sort']

results = {algorithm: {} for algorithm in algorithms}

for folder in folders:
    # Calcula a potência de 10 correspondente
    power_of_10 = f'$10^{len(folder[1:]) - 1}$'
    
    for algorithm in algorithms:
        # Lê o arquivo e extrai o tempo médio
        with open(f"../../output/{folder}/{algorithm}.out") as f:
            avg_time = float(f.readlines()[-1].split()[-1])
            results[algorithm][power_of_10] = avg_time

# Cria um DataFrame
df = pd.DataFrame(results)

# Usa um estilo predefinido
plt.style.use('ggplot')

# Plota o gráfico
ax = df.plot(kind='line', grid=True, linewidth=2.0, marker='o')
plt.ylabel('Tempo Médio', fontsize=12)
plt.xlabel('Tamanho da entrada', fontsize=12)
plt.title('Insertion Sort vs Merge Sort vs Radix Sort', fontsize=10)

# Personaliza a legenda
plt.legend(fontsize=10, title_fontsize='10')

plt.savefig(f"../../graphs/AllAlgs.png", dpi=200)
