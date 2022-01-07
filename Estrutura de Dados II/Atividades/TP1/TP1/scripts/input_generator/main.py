from os import fdopen
import random

if __name__ == "__main__":

    metodos = [1, 2, 3, 4]
    quantidades = [200, 2000, 20000, 200000, 2000000]
    situacoes = [1, 2, 3]

    asi_file = open("../../input/ASI/testes.txt", "w")
    binary_tree_file = open("../../input/ArvBinaria/testes.txt", "w")
    b_tree_file = open("../../input/ArvB/testes.txt", "w")
    bStar_tree_file = open("../../input/ArvB_Star/testes.txt", "w")

    for metodo in metodos:
        for situacao in situacoes:
            for quantidade in quantidades:
                for i in range(20):
                    chave = random.randint(0, quantidade)

                    if metodo == 1:
                        asi_file.write(
                            f"./pesquisa {metodo} {quantidade} {situacao} {chave}\n"
                        )
                    elif metodo == 2:
                        binary_tree_file.write(
                            f"./pesquisa {metodo} {quantidade} {situacao} {chave}\n"
                        )
                    elif metodo == 3:
                        b_tree_file.write(
                            f"./pesquisa {metodo} {quantidade} {situacao} {chave}\n"
                        )
                    elif metodo == 4:
                        bStar_tree_file.write(
                            f"./pesquisa {metodo} {quantidade} {situacao} {chave}\n"
                        )

    asi_file.close()
    binary_tree_file.close()
    b_tree_file.close()
    bStar_tree_file.close()
