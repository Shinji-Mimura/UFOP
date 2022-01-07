CREATE TABLE Genero (
  descricao VARCHAR(255), 
  codGenero INT NOT NULL,
  CONSTRAINT pk_genero PRIMARY KEY (codGenero)
);

CREATE TABLE Editora (
  nome VARCHAR(255), 
  cnpj VARCHAR(255) NOT NULL, 
  rua VARCHAR(255), 
  bairro VARCHAR(255), 
  cidade VARCHAR(255), 
  estado CHAR(2),
  cep CHAR(9),
  CONSTRAINT pk_editora PRIMARY KEY (cnpj)
);

CREATE TABLE Livro (
  titulo VARCHAR(255), 
  isbn VARCHAR(17) NOT NULL, 
  dataPublicacao DATE, 
  edicao VARCHAR(255), 
  codGenero INT, 
  codAutor INT, 
  cnpjEditora CHAR(18), 
  CONSTRAINT pk_livro PRIMARY KEY (isbn)
);

CREATE TABLE Autor (
  nome VARCHAR(255), 
  dataNascimento DATE, 
  nacionalidade VARCHAR(255), 
  codAutor INT NOT NULL,
  CONSTRAINT pk_autor PRIMARY KEY (codAutor)
);

CREATE TABLE Exemplar (
  codBarras VARCHAR(15) NOT NULL, 
  condicao VARCHAR(255), 
  isbnLivro CHAR(17), 
  codBiblioteca INT, 
  estoque INT, 
  CONSTRAINT pk_exemplar PRIMARY KEY (codBarras)
);

CREATE TABLE Biblioteca (
  nome VARCHAR(255), 
  codBiblioteca INT NOT NULL, 
  rua VARCHAR(255), 
  bairro VARCHAR(255), 
  cidade VARCHAR(255), 
  estado CHAR(2),
  cep CHAR(9),
  CONSTRAINT pk_biblioteca PRIMARY KEY (codBiblioteca)
);

CREATE TABLE Departamento (
  nome VARCHAR(255), 
  codDepartamento INT NOT NULL, 
  codBiblioteca INT, 
  codGerente CHAR(15),
  CONSTRAINT pk_departamento PRIMARY KEY (codDepartamento) 
);

CREATE TABLE Funcionario (
  cargo VARCHAR(255), 
  nss VARCHAR(15), 
  salario NUMERIC(8,2), 
  cpfFuncionario CHAR(15) NOT NULL,
  CONSTRAINT pk_funcionario PRIMARY KEY (cpfFuncionario) 
);

CREATE TABLE Departamento_Funcionario (
  codDepartamento INT, 
  cpfFuncionario VARCHAR(15), 
  dataEntrada DATE, 
  dataSaida DATE,
  CONSTRAINT pk_departamento_funcionario PRIMARY KEY (codDepartamento, cpfFuncionario)
);

CREATE TABLE Cliente (
  numRegistro INT, 
  cpfCliente CHAR(15) NOT NULL,
  CONSTRAINT pk_cliente PRIMARY KEY (cpfCliente)
);

CREATE TABLE Usuario (
  dataNascimento DATE, 
  nome VARCHAR(255), 
  email VARCHAR(255),
  cpfUsuario CHAR(15) NOT NULL,
  CONSTRAINT pk_usuario PRIMARY KEY (cpfUsuario)
);

CREATE TABLE Telefone_Usuario (
  cpfUsuario CHAR(15), 
  telefone VARCHAR(40),
  CONSTRAINT pk_telefone_usuario PRIMARY KEY (cpfUsuario, telefone)
);

CREATE TABLE Telefone_Departamento (
  codDepartamento INT, 
  telefone VARCHAR(40), 
  CONSTRAINT pk_telefone_departamento PRIMARY KEY (codDepartamento, telefone)
);

CREATE TABLE Compra (
  codCompra INT NOT NULL, 
  preco NUMERIC(5,2), 
  dataCompra DATE, 
  numProtocolo INT, 
  CONSTRAINT pk_compra PRIMARY KEY (codCompra)
);

CREATE TABLE Aluguel (
  codAluguel INT NOT NULL, 
  dataDevolucao DATE, 
  dataLocacao DATE, 
  dataLimite DATE, 
  preco NUMERIC(5,2), 
  numProtocolo INT,
  CONSTRAINT pk_aluguel PRIMARY KEY (codAluguel) 
);

CREATE TABLE Relatorio (
  numProtocolo INT NOT NULL,
  CONSTRAINT pk_relatorio PRIMARY KEY (numProtocolo) 
);

CREATE TABLE Exemplar_Usuario_Relatorio (
  codExemplar CHAR(15), 
  cpfUsuario CHAR(15), 
  numProtocolo INT,
  CONSTRAINT pk_exemplar_usuario_relatorio PRIMARY KEY (codExemplar, cpfUsuario, numProtocolo)
);


-- Populando para Gênero
INSERT INTO Genero VALUES ('Horror', 1);
INSERT INTO Genero VALUES ('Ficção', 2);
INSERT INTO Genero VALUES ('Fantasia', 3); 
INSERT INTO Genero VALUES ('Poesia', 4);
INSERT INTO Genero VALUES ('Romance', 5); 
INSERT INTO Genero VALUES ('Suspense', 6); 
INSERT INTO Genero VALUES ('Não Ficção', 7); 
INSERT INTO Genero VALUES ('Infantil', 8);

-- Populando para Editoras
INSERT INTO Editora VALUES('Rocco', '42.444.703/0004-00', 'Alameda Santos, 1165', 'Cerqueira Cesar', 'São Paulo', 'SP', '01419-002');
INSERT INTO Editora VALUES('INTriseca', '05.660.045/0001-06', 'Rua Marques de Sao Vicente, 99', 'Gavea', 'Rio de Janeiro', 'RJ', '22451-041');
INSERT INTO Editora VALUES('Sextante', '02.310.771/0001-00', 'Rua Voluntarios da Patria, 45', 'Botafogo', 'Rio de Janeiro', 'RJ', '22270-000');
INSERT INTO Editora VALUES('Ediouro', '04.160.920/0001-28', 'Rua Candelaria, 00060', 'Centro', 'Rio de Janeiro', 'RJ', '20091-020');
INSERT INTO Editora VALUES('Schwarcz', '55.789.390/0008-99', 'Avenida Orlanda Bergamo, 780', 'Cumbica', 'Guarulhos', 'SP', '07232-151');
INSERT INTO Editora VALUES('Original', '04.946.820/0001-21', 'Rua Henrique Schaumann, 286', 'Cerqueira Cesar', 'São Paulo', 'SP', '05413-010');

-- Populando Autor
INSERT INTO Autor VALUES('Olívio Jekupe', '10/10/1965', 'Brasileiro', 1);
INSERT INTO Autor VALUES('Lisa Williamson', NULL, 'Inglês', 2);
INSERT INTO Autor VALUES('Rafia Zakaria', NULL, 'Estadunidense', 3);
INSERT INTO Autor VALUES('Rhonda Byrne', '12/03/1951', 'Australiana', 4);
INSERT INTO Autor VALUES('Aleksandr Pushkin', '06/06/1799', 'Russo', 5);
INSERT INTO Autor VALUES('Augusto Luís Browne de Campos', '14/02/1931', 'Brasileiro', 6);

-- Populando Livros
INSERT INTO Livro VALUES('O Saci Verdadeiro', '978-655-697-147-6', NULL, '2021', 8, 1, '04.946.820/0001-21'); 
INSERT INTO Livro VALUES('A Arte de Ser Normal', '978-857-980-250-8', NULL, '2021', 2, 2, '42.444.703/0004-00');
INSERT INTO Livro VALUES('Contra o Feminismo Branco', '978-655-560-323-1', '26/10/2021', '2021', 7, 3, '05.660.045/0001-06');
INSERT INTO Livro VALUES('Héroi', '978-854-310-824-7', '09/09/2019', '2019', 3, 4, '02.310.771/0001-00');
INSERT INTO Livro VALUES('A filha do capitão', '978-850-011-485-4', '01/01/2000', '2020', 5, 5, '04.160.920/0001-28');  
INSERT INTO Livro VALUES('Poesia antipoesia antropofagia & cia', '978-853-592-646-0', '27/10/2015', '2015', 4, 6, '55.789.390/0008-99');

-- Populando Exemplar
INSERT INTO Exemplar VALUES('123456789101112', 'Bom', '978-655-697-147-6', 010, 25);
INSERT INTO Exemplar VALUES('124567891011123', 'Ótimo', '978-655-560-323-1', 020, 15);
INSERT INTO Exemplar VALUES('123336789101112', 'Ruim', '978-857-980-250-8', 030, 27);
INSERT INTO Exemplar VALUES('123657889101112', 'Bom', '978-850-011-485-4', 020, 9);
INSERT INTO Exemplar VALUES('213465789101112', 'Ruim', '978-853-592-646-0', 030, 45);
INSERT INTO Exemplar VALUES('968526789101112', 'Bom', '978-850-011-485-4', 010, 12);
INSERT INTO Exemplar VALUES('928356789101112', 'Ótimo', '978-854-310-824-7', 010, 31);

-- Populando Biblioteca
INSERT INTO Biblioteca VALUES('Saraiva Bauxita', 010, 'Rua Alfa 1809', 'Bauxita', 'Ouro Preto', 'MG', '35400-000');
INSERT INTO Biblioteca VALUES('Saraiva Barra', 020, 'Rua Pandiá Calógeras 197', 'Barra', 'Ouro Preto', 'MG', '35400-000');
INSERT INTO Biblioteca VALUES('Saraiva Veloso', 030, 'Rua Padre Rolim 2054', 'Veloso', 'Ouro Preto', 'MG', '35400-000');


-- Populando Usuario
INSERT INTO Usuario VALUES('20/11/1977', 'Allana Carolina de Paula', 'allanacdepaula@gmail.com', '999.999.999-99');
INSERT INTO Usuario VALUES('07/05/1965', 'Rafaela Marina Cristiane Melo', 'rrafaelamarinac@uol.com.br', '888.888.888-88');
INSERT INTO Usuario VALUES('07/10/1976', 'Cecília Emanuelly Louise Batista', 'cecilialouise@outlook.com', '777.777.777-77');
INSERT INTO Usuario VALUES('22/01/1994', 'Sofia Natália da Luz', 'sofianathluz@gmail.com', '666.666.666-66');
INSERT INTO Usuario VALUES('20/01/1997', 'Betina Clara Vera Martins', 'etinaveramartins@gmail.com', '555.555.555-55');
INSERT INTO Usuario VALUES('19/08/1995', 'Armando de Jesus', 'ajj95@gmail.com', '444.444.444-44');
INSERT INTO Usuario VALUES('03/07/1999', 'Pedro Xavier', 'pedro-xavier@gmail.com', '333.333.333-33');
INSERT INTO Usuario VALUES('15/05/2001', 'Marília de Souza', 'mlia.souza@outlook.com', '222.222.222-22');
INSERT INTO Usuario VALUES('01/09/2000', 'João Silva', 'jsilva@yahho.com', '111.111.111-11');


-- Populando Funcionario
INSERT INTO Funcionario VALUES('Recepcionista', '123.456.789-1', 1500.00, '999.999.999-99');
INSERT INTO Funcionario VALUES('Bibliotecário', '132.465.798-1', 3500.00, '888.888.888-88');
INSERT INTO Funcionario VALUES('Recepcionista', '321.654.987-1', 2500.00, '777.777.777-77');
INSERT INTO Funcionario VALUES('Psicóloga', '221.445.668-2', 4500.00, '666.666.666-66');
INSERT INTO Funcionario VALUES('Recepcionista', '122.335.448-6', 2000.00, '555.555.555-55');
INSERT INTO Funcionario VALUES('Psicólogo', '122.488.998-7', 3800.00, '444.444.444-44');

-- Populando Departamento_Funcionario
INSERT INTO Departamento_Funcionario VALUES(101, '999.999.999-99', '26/10/2010', NULL);
INSERT INTO Departamento_Funcionario VALUES(110, '888.888.888-88', '06/11/2016', NULL);
INSERT INTO Departamento_Funcionario VALUES(102, '777.777.777-77', '13/04/1999', '16/06/2010');
INSERT INTO Departamento_Funcionario VALUES(111, '666.666.666-66', '08/12/2003', '27/08/2016');
INSERT INTO Departamento_Funcionario VALUES(103, '555.555.555-55', '26/06/2014', NULL);
INSERT INTO Departamento_Funcionario VALUES(112, '444.444.444-44', '26/10/2020', NULL);

-- Populando Cliente
INSERT INTO Cliente VALUES(1, '111.111.111-11');
INSERT INTO Cliente VALUES(2, '222.222.222-22');
INSERT INTO Cliente VALUES(3, '333.333.333-33');


-- Populando Departamento
INSERT INTO Departamento VALUES('Departamento de Finanças', 101, 010, '999.999.999-99');
INSERT INTO Departamento VALUES('Departamento de Recursos Humanos', 110, 010, '888.888.888-88');
INSERT INTO Departamento VALUES('Departamento de Finanças', 102, 020, '777.777.777-77');
INSERT INTO Departamento VALUES('Departamento de Recursos Humanos', 111, 020, '666.666.666-66');
INSERT INTO Departamento VALUES('Departamento de Finanças', 103, 030, '555.555.555-55');
INSERT INTO Departamento VALUES('Departamento de Recursos Humanos', 112, 030, '444.444.444-44');


-- Populando Telefone_Usuario
INSERT INTO Telefone_Usuario VALUES('999.999.999-99', '(31) 99857-9256');
INSERT INTO Telefone_Usuario VALUES('888.888.888-88', '(32) 99772-1334');
INSERT INTO Telefone_Usuario VALUES('777.777.777-77', '(22) 98753-8567');
INSERT INTO Telefone_Usuario VALUES('666.666.666-66', '(19) 98275-0153');
INSERT INTO Telefone_Usuario VALUES('555.555.555-55', '(33) 99743-5431');
INSERT INTO Telefone_Usuario VALUES('444.444.444-44', '(25) 98432-6743');
INSERT INTO Telefone_Usuario VALUES('333.333.333-33', '(27) 99101-7234');
INSERT INTO Telefone_Usuario VALUES('222.222.222-22', '(18) 99754-7285');
INSERT INTO Telefone_Usuario VALUES('111.111.111-11', '(26) 99229-1234');

-- Populando Telefone_Departamento
INSERT INTO Telefone_Departamento VALUES(101, '(31) 94185-4715');
INSERT INTO Telefone_Departamento VALUES(110, '(32) 97845-4367');
INSERT INTO Telefone_Departamento VALUES(102, '(19) 94785-9587');
INSERT INTO Telefone_Departamento VALUES(111, '(33) 97984-1534');
INSERT INTO Telefone_Departamento VALUES(103, '(27) 97458-8843');
INSERT INTO Telefone_Departamento VALUES(112, '(18) 91563-1564');

-- Populando Compra
INSERT INTO Compra VALUES(10, 50.30, '10/08/2015', 1000);
INSERT INTO Compra VALUES(11, 80.10, '11/06/2016', 1001);

-- Populando Aluguel
INSERT INTO Aluguel VALUES(13, '05/10/2020', '03/09/2020', '08/10/2020', 34.70, 1002);

-- Populando Relatorio
INSERT INTO Relatorio VALUES(1000);
INSERT INTO Relatorio VALUES(1001);
INSERT INTO Relatorio VALUES(1002);

-- Populando Exemplar_Usuario_Relatorio
INSERT INTO Exemplar_Usuario_Relatorio VALUES('123456789101112', '999.999.999-99', 1000);
INSERT INTO Exemplar_Usuario_Relatorio VALUES('124567891011123', '888.888.888-88', 1001);
INSERT INTO Exemplar_Usuario_Relatorio VALUES('123336789101112', '777.777.777-77', 1002);

-- restrições de INTegridade referencial


ALTER TABLE Livro
ADD CONSTRAINT fk_livro_genero FOREIGN KEY (codGenero) REFERENCES Genero (codGenero) ON UPDATE CASCADE;

ALTER TABLE Livro
ADD CONSTRAINT fk_livro_autor FOREIGN KEY (codAutor) REFERENCES Autor (codAutor) ON UPDATE CASCADE;

ALTER TABLE Livro
ADD CONSTRAINT fk_livro_editora FOREIGN KEY (cnpjEditora) REFERENCES Editora (cnpj) ON UPDATE CASCADE;

ALTER TABLE Exemplar
ADD CONSTRAINT fk_exemplar_livro FOREIGN KEY (isbnLivro) REFERENCES Livro (isbn) ON UPDATE CASCADE;

ALTER TABLE Exemplar
ADD CONSTRAINT fk_exemplar_biblioteca FOREIGN KEY (codBiblioteca) REFERENCES Biblioteca (codBiblioteca) ON UPDATE CASCADE;

ALTER TABLE Departamento
ADD CONSTRAINT fk_departamento_biblioteca FOREIGN KEY (codBiblioteca) REFERENCES Biblioteca (codBiblioteca) ON UPDATE CASCADE;

ALTER TABLE Departamento
ADD CONSTRAINT fk_departamento_funcionario FOREIGN KEY (codGerente) REFERENCES Funcionario (cpfFuncionario) ON UPDATE CASCADE;

ALTER TABLE Funcionario
ADD CONSTRAINT fk_funcionario_usuario FOREIGN KEY (cpfFuncionario) REFERENCES Usuario (cpfUsuario) ON DELETE CASCADE;

ALTER TABLE Departamento_Funcionario
ADD CONSTRAINT fk_departamento_funcionario_departamento FOREIGN KEY (codDepartamento) REFERENCES Departamento (codDepartamento) ON UPDATE CASCADE;

ALTER TABLE Departamento_Funcionario
ADD CONSTRAINT fk_departamentento_funcionario_funcionario FOREIGN KEY (cpfFuncionario) REFERENCES Funcionario (cpfFuncionario) ON UPDATE CASCADE; 

ALTER TABLE Cliente
ADD CONSTRAINT fk_cliente_usuario FOREIGN KEY (cpfCliente) REFERENCES Usuario (cpfUsuario) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE Telefone_Usuario
ADD CONSTRAINT fk_telefone_usuario_usuario FOREIGN KEY (cpfUsuario) REFERENCES Usuario (cpfUsuario) ON DELETE CASCADE;

ALTER TABLE Telefone_Departamento
ADD CONSTRAINT fk_telefone_departamento_departamento FOREIGN KEY (codDepartamento) REFERENCES Departamento (codDepartamento) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE Compra
ADD CONSTRAINT fk_compra_relatorio FOREIGN KEY (numProtocolo) REFERENCES Relatorio (numProtocolo) ON UPDATE CASCADE;

ALTER TABLE Aluguel
ADD CONSTRAINT fk_aluguel_relatorio FOREIGN KEY (numProtocolo) REFERENCES Relatorio (numProtocolo) ON UPDATE CASCADE;

ALTER TABLE Exemplar_Usuario_Relatorio
ADD CONSTRAINT fk_exemplar_usuario_relatorio_exemplar FOREIGN KEY (codExemplar) REFERENCES Exemplar (codBarras) ON UPDATE CASCADE;

ALTER TABLE Exemplar_Usuario_Relatorio
ADD CONSTRAINT fk_exemplar_usuario_relatorio_usuario FOREIGN KEY (cpfUsuario) REFERENCES Usuario (cpfUsuario) ON UPDATE CASCADE;

ALTER TABLE Exemplar_Usuario_Relatorio
ADD CONSTRAINT fk_exemplar_usuario_relatorio_relatorio FOREIGN KEY (numProtocolo) REFERENCES Relatorio (numProtocolo) ON UPDATE CASCADE;
