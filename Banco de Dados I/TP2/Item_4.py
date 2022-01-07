import psycopg2
from tabulate import tabulate

# Função que realiza conexão local com o banco de dados
def conecta_database(password, nome_db):
    try:
        con = psycopg2.connect(host='localhost', database=nome_db, user='postgres', password=password)
    except:
        print("[!] Connection error with database Biblioteca")
        exit(1)

    return con

# Função que retorna todos os departamentos e seus atributos
def lista_departamentos(con):
    cur = con.cursor()
    sql_query = "SELECT * FROM departamento"
    cur.execute(sql_query)
    result_query = cur.fetchall()

    print(tabulate(result_query, headers=['Nome', 'Código Departamento', 'Código Biblioteca', 'Código Gerente'], tablefmt='psql'))

# Função que retorna todos os livros alugados/comprados de determinado usuário através de seu cpf
def livros_do_cliente(con, cpf_cliente):
    cur = con.cursor()

    sql_query = f"SELECT cpfusuario, condicao, isbn, datapublicacao, ed.nome, edicao, titulo, au.nome \
        FROM exemplar_usuario_relatorio \
        AS eur \
        INNER JOIN \
        exemplar AS e \
        ON eur.codexemplar=e.codbarras \
        INNER JOIN \
        livro AS l \
        ON e.isbnlivro=l.isbn \
        INNER JOIN \
        autor as au \
        ON l.codautor=au.codautor \
        INNER JOIN \
        editora as ed \
        ON l.cnpjeditora=ed.cnpj \
        WHERE cpfusuario='{cpf_cliente}'; \
    "
    
    cur.execute(sql_query)
    result_query = cur.fetchall()
    print(tabulate(result_query, headers=['CPF', 'Condição', 'ISBN', 'Publicação', 'Editora', 'Edição', 'Título', 'Autor'], tablefmt='psql'))

# Função que retorna se determinado autor possui exemplares disponíveis e quais os status dos mesmos
def verifica_autor(con, nome_autor):
    cur = con.cursor()

    sql_query = f"select nome, titulo, condicao from livro \
        INNER JOIN autor ON autor.codautor=livro.codautor INNER JOIN \
        exemplar ON livro.isbn=exemplar.isbnlivro where nome like '%{nome_autor}%'"

    cur.execute(sql_query)
    result_query = cur.fetchall()
    print(tabulate(result_query, headers=['Nome', 'Titulo', 'Condição do Exemplar'], tablefmt='psql'))

# Função que retorna, para cada departamento, qual é o seu código, nome, nome de seu gerente, a quantidade de
# funcionários e a média salarial deles
def informacoes_departamento(con):
    cur = con.cursor()
    sql_query = f"SELECT d.codDepartamento, d.nome, u.nome, COUNT(*), AVG(f.Salario) \
        FROM Departamento as d\
        INNER JOIN \
        Funcionario as f \
        ON d.codGerente = f.cpfFuncionario \
        INNER JOIN \
        Usuario as u \
        ON f.cpfFuncionario = u.cpfUsuario \
        GROUP BY u.nome, d.codDepartamento; \
    "

    cur.execute(sql_query)
    result_query = cur.fetchall()
    print(tabulate(result_query, headers=['Código do Departamento', 'Nome do Departamento', 'Nome do Gerente', 'Quantidade de Funcionários', 'Média Salarial'], tablefmt='psql'))

# Função que troca o código de certo departamento para um novo código
def update_cod_departamento(con, cod_departamento_antigo, cod_departamento_novo):
    cur = con.cursor()
    sql_query = f"UPDATE Departamento SET codDepartamento={cod_departamento_novo} WHERE coddepartamento = {cod_departamento_antigo}"
    cur.execute(sql_query)
  
if __name__ == "__main__":
    password = input("Password of Database: ")
    connection = conecta_database(password, "Biblioteca") # Nome do BD

    # Menu
    option = -1

    while option != 5:
        print("\n")
        print("1. Consultar livros do cliente")
        print("2. Consultar livros de um autor")
        print("3. Consultar informações dos departamentos")
        print("4. Atualizar um Código de Departamento")
        print("5. Sair do Programa\n")

        option = int(input("Escolha uma opção: "))

        if (option == 1):
            cpf = input('Digite o CPF do cliente: ')
            livros_do_cliente(connection, cpf)

        elif (option == 2):
            nome = input('Digite o nome do autor: ')
            verifica_autor(connection, nome)

        elif (option == 3):  
            informacoes_departamento(connection)
        
        elif (option == 4): 
            antigo = int(input('Digite o código do departamento que deseja atualizar: '))
            novo = int(input('Digite o novo código do departamento em questão: '))
            update_cod_departamento(connection, antigo, novo)

    connection.commit() # Efetiva as alterações no banco