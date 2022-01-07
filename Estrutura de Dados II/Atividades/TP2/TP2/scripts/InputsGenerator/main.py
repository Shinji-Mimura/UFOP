import random

if __name__ == "__main__":

    metodos = [1, 2, 3]
    quantidades = [100, 1000, 10000, 100000, 471705]
    situacoes = [1, 2, 3]

    intercalacao_Ffitas = open(
        "../../input/IntercalacaoFfitas/testes.txt",
        "w",
    )
    intercalacao_2Ffitas = open(
        "../../input/Intercalacao2Ffitas/testes.txt",
        "w",
    )
    QuickExterno = open(
        "../../input/QuicksortExterno/testes.txt",
        "w",
    )

    for metodo in metodos:
        for situacao in situacoes:
            for quantidade in quantidades:

                if metodo == 1:
                    intercalacao_2Ffitas.write(
                        f"./ordena {metodo} {quantidade} {situacao}\n"
                    )

                elif metodo == 2:
                    intercalacao_Ffitas.write(
                        f"./ordena {metodo} {quantidade} {situacao}\n"
                    )
                elif metodo == 3:
                    QuickExterno.write(f"./ordena {metodo} {quantidade} {situacao}\n")

    intercalacao_Ffitas.close()
    intercalacao_2Ffitas.close()
    QuickExterno.close()
