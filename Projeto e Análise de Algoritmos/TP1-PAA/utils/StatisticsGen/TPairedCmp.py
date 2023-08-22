# ALPHA = 0.05
# CONFIDANCE = 0.95
# FREEDOM_DEGREE = SAMPLES - 1

import sys
import statistics
import math
from pathlib import Path

CRITICAL_T = 2.093 # Valor crítico para o cálculo do intervalo de confiança
SAMPLES = 20 # Número de amostras

print(f"{sys.argv[2]} X {sys.argv[3]} | Tamanho da Instância: {sys.argv[1]}")

size = int(sys.argv[1])
algorithm1 = sys.argv[2] 
algorithm2 = sys.argv[3] 

# Define os caminhos para os arquivos de saída
output_file1 = f"../../output/n{size}/{algorithm1}.out"
output_file2 = f"../../output/n{size}/{algorithm2}.out"

with open(output_file1, 'r') as f1, open(output_file2, 'r') as f2:
    output1 = f1.readlines()
    output2 = f2.readlines()

# Calcula a diferença no tempo de execução entre cada par de linhas correspondentes
diff = [float(line1.split(": ")[1].strip()) - float(line2.split(": ")[1].strip()) 
        for line1, line2 in zip(output1[2:22], output2[2:22])]

mean_value = statistics.mean(diff) # Calcula a média das diferenças de tempo de execução
std_value = statistics.stdev(diff) # Calcula o desvio padrão das diferenças de tempo de execução

# Calcula os limites do intervalo de confiança
fst_bound = mean_value + CRITICAL_T * std_value / math.sqrt(SAMPLES)
snd_bound = mean_value - CRITICAL_T * std_value / math.sqrt(SAMPLES)

# Organiza os limites em ordem crescente
lower_bound = min(fst_bound, snd_bound)
upper_bound = max(fst_bound, snd_bound)

print(f"Intervalo de Confiança: ({lower_bound:.4f}; {upper_bound:.4f})")

