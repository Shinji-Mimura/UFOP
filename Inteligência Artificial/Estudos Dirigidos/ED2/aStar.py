import random
import heapq


def heuristic(a, b):
    (x1, y1) = a
    (x2, y2) = b
    return abs(x1 - x2) + abs(y1 - y2)


def aStar(labirinto):
    inicio = (labirinto.rows, labirinto.cols)
    objetivo = labirinto._goal
    fronteira = []
    heapq.heappush(fronteira, (0, inicio))

    caminhoAStar = {}
    custo = {}
    caminhoAStar[inicio] = None
    custo[inicio] = 0

    while fronteira:
        (prioridade, vertice_atual) = heapq.heappop(fronteira)

        if vertice_atual == objetivo:
            print("Objetivo Encontrado!")
            break

        movimentos = ["E", "S", "N", "W"]
        random.shuffle(movimentos)

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

                novo_custo = custo[vertice_atual] + \
                    heuristic(vertice_atual, vizinho)

                if vizinho not in custo or novo_custo < custo[vizinho]:
                    custo[vizinho] = novo_custo
                    prioridade = novo_custo + heuristic(objetivo, vizinho)
                    heapq.heappush(fronteira, (prioridade, vizinho))
                    caminhoAStar[vizinho] = vertice_atual

    fwdPath = {}
    cell = objetivo
    while cell != inicio:
        fwdPath[caminhoAStar[cell]] = cell
        cell = caminhoAStar[cell]
    return fwdPath
