/*Banco sorveteria*/

/*          Justificativas da tabela cliente:
id SERIAL para não precisar inserir o ID manualmente e PRIMARY KEY porque ela é o identificador de cada linha da tabela.
nome VARCHAR pois o nome é uma string que pode conter caracteres não numéricos
telefone VARCHAR pois apesar de ser um número, não serão feitas operações com ele, além disso, em alguns casos sinais como - ou () também são inseridos nesse campo.
email VARCHAR pelo mesmo motivo do campo nome, é uma string.*/
CREATE TABLE cliente (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    telefone VARCHAR(15),
    email VARCHAR(100) UNIQUE
);
/*          Justificativas da tabela produto:
id SERIAL para não precisar inserir o ID manualmente e PRIMARY KEY porque ela é o identificador de cada linha da tabela.

nome VARCHAR pois o nome é uma string com caracteres não numéricos

categoria VARCHAR pois a categoria é uma string que pode conter caracteres não numéricos

preco DECIMAL com 10 casas antes da virgula e 2 depois da virgula; esse campo foi construido dessa forma pois ele irá guardar o valor
dos produtos dessa sorveteria e para preços é necessário que exista também as casas decimais.

estoque é INT de número inteiro, esse campo foi escolhido como int pois o estoque de algo é um número inteiro, sendo assim, INT é a escolha
adequada para esse campo.

 */
CREATE TABLE produto (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    categoria VARCHAR(50) NOT NULL,
    preco DECIMAL(10,2) NOT NULL,
    estoque INT NOT NULL
);
/*]
id SERIAL para não precisar inserir o ID manualmente e PRIMARY KEY porque ela é o identificador de cada linha da tabela.

id_cliente é uma chave estrangeira e é o campo utilizado para referenciar uma das linhas de outra tabela, nesse caso a tabela cliente, o tipo é INT pois apesar do
fato de que na tabela cliente o id seja SERIAL, o tipo INT é compatível.

id_produto é uma chave estrangeira e é o campo utilizado para referenciar uma das linhas de outra tabela, nesse caso a tabela produto, o tipo é INT pois apesar do
fato de que na tabela produto o id seja SERIAL, o tipo INT é compatível.

quantidade é o campo que registra quantas unidades do produto foram compradas. Como se trata de um número inteiro, INT é o mais indicado.

data_pedido é do tipo DATE que é justamente o tipo de campo que guarda datas e irá guardar a data que o pedido foi realizado.

valor_total é o campo que irá guardar a soma da quantidade de produtos multiplicado pelo preço de cada produto por isso é DECIMAL, pois irá guardar um valor.

*/
CREATE TABLE pedido (
id SERIAL PRIMARY KEY,
id_cliente INT NOT NULL,
id_produto INT NOT NULL,
quantidade INT NOT NULL,
data_pedido DATE NOT NULL,
  valor_total DECIMAL(10,2) NOT NULL,
    CONSTRAINT fk_pedido_cliente
        FOREIGN KEY (id_cliente)
        REFERENCES cliente(id),
    CONSTRAINT fk_pedido_produto
        FOREIGN KEY (id_produto)
        REFERENCES produto(id)
);

INSERT INTO cliente (nome, telefone, email) VALUES
('Rayssa', '86999990001', 'rayssa@gmail.com'),
('Pedro', '86999990002', 'pedro@gmail.com'),
('Lucas', '86999990003', 'lucas@gmail.com'),
('Matheus', '86999990004', 'matheus@gmail.com'),
('Igor', '86999990005', 'igor@gmail.com'),
('João Pedro', '86999990006', 'joaopedro@gmail.com'),
('Kauê', '86999990007', 'kaue@gmail.com'),
('Messias', '86999990008', 'messias@gmail.com'),
('Diolindo', '86999990009', 'diolindo@gmail.com'),
('Tainara', '86999990010', 'tainara@gmail.com'),
('Kaua', '86999990011', 'kaua@gmail.com'),
('Eduardo', '86999990012', 'eduardo@gmail.com');

INSERT INTO produto (nome, categoria, preco, estoque) VALUES
('Sorvete de Chocolate', 'Sorvete', 8.50, 40),
('Sorvete de Morango', 'Sorvete', 8.00, 35),
('Sorvete de Baunilha', 'Sorvete', 7.50, 30),
('Picolé de Limão', 'Picolé', 4.00, 50),
('Picolé de Uva', 'Picolé', 4.50, 45),
('Milk-shake de Ovomaltine', 'Milk-shake', 12.00, 20),
('Milk-shake de Morango', 'Milk-shake', 11.50, 18),
('Açaí 300ml', 'Açaí', 10.00, 25),
('Açaí 500ml', 'Açaí', 15.00, 20),
('Casquinha Simples', 'Casquinha', 5.00, 60),
('Banana Split', 'Sobremesa', 16.00, 12),
('Petit Gateau com Sorvete', 'Sobremesa', 18.00, 10);


INSERT INTO pedido (id_cliente, id_produto, quantidade, data_pedido, valor_total) VALUES
(1, 1, 2, '2026-06-01', 17.00),
(2, 4, 3, '2026-06-01', 12.00),
(3, 6, 1, '2026-06-02', 12.00),
(4, 8, 2, '2026-06-02', 20.00),
(5, 10, 4, '2026-06-03', 20.00),
(6, 11, 1, '2026-06-03', 16.00),
(7, 2, 2, '2026-06-04', 16.00),
(8, 9, 1, '2026-06-04', 15.00),
(9, 3, 3, '2026-06-05', 22.50),
(10, 5, 2, '2026-06-05', 9.00),
(11, 7, 1, '2026-06-06', 11.50),
(12, 12, 1, '2026-06-06', 18.00);

SELECT
nome AS nome_do_produto,
estoque AS quantidade_em_estoque
FROM produto;

SELECT
SUM(valor_total) AS soma_das_vendas,
MAX(valor_total) AS maior_venda,
MIN(valor_total) AS menor_venda,
AVG(valor_total) AS media_das_vendas
FROM pedido;

SELECT
cliente.nome AS nome_do_cliente,
produto.preco AS preco_do_produto,
pedido.quantidade AS quantidade_vendida,
pedido.valor_total AS valor_total_da_venda
FROM pedido
INNER JOIN cliente
ON pedido.id_cliente = cliente.id
INNER JOIN produto
ON pedido.id_produto = produto.id
GROUP BY(cliente.nome, produto.preco, pedido.quantidade, pedido.valor_total)
HAVING valor_total>=13.00
ORDER BY(valor_total)DESC;

SELECT
cliente.nome AS nome_do_cliente,
produto.preco AS preco_do_produto,
pedido.quantidade AS quantidade_vendida,
pedido.valor_total AS valor_total_da_venda
FROM pedido
INNER JOIN cliente
ON pedido.id_cliente = cliente.id
INNER JOIN produto
ON pedido.id_produto = produto.id
GROUP BY(cliente.nome, produto.preco, pedido.quantidade, pedido.valor_total)
HAVING cliente.nome LIKE '%Pedro%';



function