# ---------------------------- #
# Lucas de Araújo - 18.2.4049  #
# Estudo Dirigido II           #
# ---------------------------- #

from pyamaze import maze, agent
from random import randint
from bfs import *
from dfs import *
from aStar import *
from custoMin import *
from bestFirst import *


def execucaoMaze(tamanho=30, possibilidadeCaminhos=100, algoritmo="bfs"):

    goalX, goalY = randint(1, tamanho), 1

    m = maze(tamanho, tamanho)
    m.CreateMaze(goalX, goalY, loopPercent=possibilidadeCaminhos)

    # Inclusão do agente no ambiente
    a = agent(m, footprints=True, shape="arrow")
    b = agent(m, footprints=True, color='red', filled=True)

    if algoritmo == "bfs":
        print("[+] Busca em Largura")
        path = bfs(m)

    elif algoritmo == "dfs":
        print("[+] Busca em Profundidade")
        path = dfs(m)

    elif algoritmo == "aStar":
        print("[+] Busca A*")
        path = aStar(m)

    elif algoritmo == "cm":
        print("[+] Busca de Custo Minimo")
        path = cm(m)

    elif algoritmo == "bfirst":
        print("[+] Busca Best First")
        path = bfirst(m)

    m.tracePath({a: path})
    m.run()


if __name__ == '__main__':

    print("Escolha algum dos seguintes algoritmos")
    print("""

    1) BFS
    2) DFS
    3) A*
    4) Custo Minimo
    5) Best First

    """)

    op = int(input("OP (número): "))

    # Variáveis de ambiente do labirinto
    tamanho = 20
    possibilidadeCaminhos = 100

    match op:
        case 1:
            execucaoMaze(tamanho, possibilidadeCaminhos,"bfs")
        case 2:
            execucaoMaze(tamanho, possibilidadeCaminhos, "dfs")
        case 3:
            execucaoMaze(tamanho, possibilidadeCaminhos, "aStar")
        case 4:
            execucaoMaze(tamanho, possibilidadeCaminhos, "cm")
        case 5:
            execucaoMaze(tamanho, possibilidadeCaminhos, "bfirst")
        case _:
            print("Esta opção é inválida! Tente novamente.")
