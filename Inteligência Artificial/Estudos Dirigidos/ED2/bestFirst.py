import random
import heapq

def heuristic(a, b):
    (x1, y1) = a
    (x2, y2) = b
    return abs(x1 - x2) + abs(y1 - y2)

def bfirst(labirinto):
    inicio = (labirinto.rows, labirinto.cols)
    objetivo = labirinto._goal
    fronteira = []
    heapq.heappush(fronteira, (0, inicio))

    caminhoBestFirst = {}
    caminhoBestFirst[inicio] = None

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

                if vizinho not in caminhoBestFirst:
                    prioridade = heuristic(objetivo, vizinho)
                    heapq.heappush(fronteira, (prioridade, vizinho))
                    caminhoBestFirst[vizinho] = vertice_atual

    fwdPath = {}
    cell = objetivo
    while cell != inicio:
        fwdPath[caminhoBestFirst[cell]] = cell
        cell = caminhoBestFirst[cell]
    return fwdPath
