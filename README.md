# SO_1819
Text Editor in C (Unix)

# Meta 1
 - [x] Definição de estruturas e costantes necessários ao editor de texto e utilizador;
 - [x] Função para verificar username num determinado ficheiro;
 - [x] Edição e navegação de uma linha;
 - [X] Leitura e validação dos comandos/argumentos opcionais do servidor;
 - [x] Leitura e validação das variáveis de ambiente do servidor e cliente.

# Meta 2
 - [] Comunicação através de named piped entre servidor e cliente;
 - [] Gestão dos clientes (detectar que existem, avisar que o servidor encerrou, etc) a funcionar;
 - [] Login dos utilizadores a funcionar;
 - [] Lançamento e comunicação com o dicionário preparada, incluindo verificações.


# Bugs / A melhorar
 - Má implementação quando se escreve no editor e se tenta apagar (repetição do caracter que se está a apagar);
 - Organização do código.
 - Se tentarmos apagar um espaço em branco, o BACKSPACE buga e não consegue apagar nenhum caracter.
  
