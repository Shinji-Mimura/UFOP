# ALPHA = 0.05
# CONFIDANCE = 0.95
# FREEDOM_DEGREE = SAMPLES - 1

import sys
import statistics
import math
from pathlib import Path

CRITICAL_T = 2.093 # Valor crítico para o cálculo do intervalo de confiança
SAMPLES = 20 # Número de amostras

print(f"{sys.argv[2]} | Tamanho da Instância: {sys.argv[1]}")

size = int(sys.argv[1]) 
algorithm = sys.argv[2]

output_file = f"../../output/n{size}/{algorithm}.out"
with open(output_file, 'r') as f: 
    output = f.readlines() #

# Extrai o tempo de execução de cada linha (ignorando as duas primeiras linhas) e converte para float
time_execution = [float(line.split(": ")[1].strip()) for line in output[2:22]]

mean_value = statistics.mean(time_execution) # Calcula a média dos tempos de execução
std_value = statistics.stdev(time_execution) # Calcula o desvio padrão dos tempos de execução

# Calcula os limites do intervalo de confiança
fst_bound = mean_value + CRITICAL_T * std_value / math.sqrt(SAMPLES)
snd_bound = mean_value - CRITICAL_T * std_value / math.sqrt(SAMPLES)

# Organiza os limites em ordem crescente
lower_bound = min(fst_bound, snd_bound)
upper_bound = max(fst_bound, snd_bound)

print(f"Intervalo de Confiança: ({lower_bound:.4f}; {upper_bound:.4f})")
