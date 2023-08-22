import random
import heapq


def cm(labirinto):
    inicio = (labirinto.rows, labirinto.cols)
    objetivo = labirinto._goal
    fronteira = []
    heapq.heappush(fronteira, (0, inicio))

    camDjk = {}
    custo = {}
    camDjk[inicio] = None
    custo[inicio] = 0

    while fronteira:
        (custo_atual, vertice_atual) = heapq.heappop(fronteira)

        if vertice_atual == objetivo:
            print("Objetivo Encontrado!")
            break

        movimentos = ["E", "S", "N", "W"]

        for d in movimentos:
            if labirinto.maze_map[vertice_atual][d] == True:
                if d == 'E':
                    vizinho = (vertice_atual[0], vertice_atual[1]+1)
                if d == 'W':
                    vizinho = (vertice_atual[0], vertice_atual[1]-1)
                if d == 'N':
                    vizinho = (vertice_atual[0]-1, vertice_atual[1])
                if d == 'S':
                    vizinho = (vertice_atual[0]+1, vertice_atual[1])

                # Custo aleatório entre 1 e 30
                novo_custo = custo[vertice_atual] + random.randint(1, 30) 

                if vizinho not in custo or novo_custo < custo[vizinho]:
                    custo[vizinho] = novo_custo
                    heapq.heappush(fronteira, (novo_custo, vizinho))
                    camDjk[vizinho] = vertice_atual

    fwdPath = {}
    cell = objetivo
    while cell != inicio:
        fwdPath[camDjk[cell]] = cell
        cell = camDjk[cell]
    return fwdPath
