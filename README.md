# SO_1819
Text Editor in C (Unix)

# Meta 1
 - [x] Definição de estruturas e costantes necessários ao editor de texto e utilizador;
 - [x] Função para verificar username num determinado ficheiro;
 - [x] Edição e navegação de uma linha;
 - [X] Leitura e validação dos comandos/argumentos opcionais do servidor;
 - [x] Leitura e validação das variáveis de ambiente do servidor e cliente.

# Meta 2
 - [x] Comunicação através de named piped entre servidor e cliente;
 - [x] Gestão dos clientes (detectar que existem, avisar que o servidor encerrou, etc) a funcionar;
 - [x] Login dos utilizadores a funcionar;
 - [x] Lançamento e comunicação com o dicionário preparada, incluindo verificações (somente no lado do servidor).


# Bugs / A melhorar
 - Organização do código.
 - Passar a variável content da estrutura Editor para um array 2D dinâmico.
 - Contador do nº de caracteres do utilizador está bugado.
 - Alternação entre o Modo de Edição/Navegação (graficamente) bugado.
 - [X] Saber graficamente, quem está a editar o quê em tempo real.
 - Implementar a idade da sessão de cada utilizador em tempo real;
 - Implementar mutexes / semáforos.
 - [X] Na função statistcs() implementar código para saber quais as linhas que estão a ser editadas no momento pelos clientes (em tempo real).
 - No servidor, quando chamamos o comando free da linha, nao atualiza de imediato no cliente, e preciso fazer um getchar.

# Funcionalidades implementadas para final do trabalho
 - [X] Implementar no servidor um array de estruturas dos clientes para a comunicação entre o servidor e os clientes;
