import matplotlib.pyplot as plt
import seaborn as sbn


def nome_grafico():
    print("Digite o nome do método que você deseja criar um gráfico (Ex: Acesso Sequencial Indexado)")
    op = input("Nome: ")
    return op


def ordem_grafico():
    print("Digite qual a ordem do arquivo utilizada no método (Ex: Ordem Decrescente)")
    op2 = input("Ordem: ")
    return op2


def assunto_grafico():
    print("Digite o sobre o que se trata o gráfico (Ex: Tempo médio, Número de comparações etc)")
    op3 = input("Assunto: ")
    return op3


def salva_valores():
    valores_totais = []
    for i in range(5):
        valor = float(input(f"Digite o {i+1}° valor: "))
        valores_totais.append(valor)

    return valores_totais


if __name__ == "__main__":

    plt_colors = sbn.color_palette("pastel")

    qtd_registros = ['200', '2000', '20000', '200000', '2000000']
    plt.xlabel("Quantidade de Registros no Arquivo")

    plt.ylabel(assunto_grafico())

    plt.title(ordem_grafico())
    plt.suptitle(nome_grafico(), fontsize=16)

    valores_totais = salva_valores()
    plt.bar(qtd_registros, valores_totais, color=plt_colors[:5])

    plt.axis('tight')

    plt.show()
