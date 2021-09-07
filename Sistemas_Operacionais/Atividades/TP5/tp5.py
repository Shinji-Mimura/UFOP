# Trabalho Prático 5 - Sistemas Operacionais
# Professor Doutor: Carlos Frederico Marcelo da Cunha Cavalcanti
# Aluno: Lucas de Aráujo
# Matrícula: 18.2.4049

import requests  # Biblioteca nativa do python para realizar requests

# Função que realiza request para API e formata os dados para o JSON
resposta = requests.get(
    "https://api.covid19api.com/live/country/brazil/status/confirmed"
).json()

# Listas utilizadas para coletar os dados da API
minas_gerais_confirmados = []
minas_gerais_mortes = []
minas_gerais_ativos = []
minas_gerais_data = []

# Loop que busca apenas por dados do estado de Minas Gerais
for i in range(len(resposta)):
    if resposta[i]["Province"] == "Minas Gerais":
        minas_gerais_confirmados.append(resposta[i]["Confirmed"])
        minas_gerais_mortes.append(resposta[i]["Deaths"])
        minas_gerais_ativos.append(resposta[i]["Active"])
        minas_gerais_data.append(resposta[i]["Date"])

# Impressão dos dados mais recentes do estado de Minas Gerais
print("\n")
print("+-------------------------------------+")
print("|  Casos de Covid-19 em Minas Gerais  |")k
print("+-------------------------------------+")
print(f"Número de Confirmados: {minas_gerais_confirmados[-1]}")
print(f"Número de Mortes: {minas_gerais_mortes[-1]}")
print(f"Número de Ativos: {minas_gerais_ativos[-1]}")
print(f"Data: {minas_gerais_data[-1][:10]}")
print("\n")
