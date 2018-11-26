#include "comandos.h"
#include "main.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>

bool verify_file_existence(char *file) {
  FILE *f = fopen(file, "r");

  if (f == NULL) {
    return 1;
  } else {
    return 0;
  }
}

// INICIALIZA A MATRIZ DO EDITOR COM ESPAÇOS EM BRANCO
void initialize_editor_content() {
  for (int i = 0; i < editor.lines; i++) {
    for (int j = 0; j < editor.columns; j++)
      editor.content[i][j] = ' ';
  }
}

void shutdown() {
  char pipe[20];
  int fd;
  Editor send;
  send.action = SERVER_SHUTDOWN;
  sprintf(pipe, "../pipe-%d", editor.pid);
  fd = open(pipe, O_WRONLY, 0600);

  write(fd, &send, sizeof(send));
  close(fd);
  unlink(PIPE);
  printf("Programa terminado\n");
  exit(0);
}

void save_settings(char *filename) {
  FILE *f = fopen(filename, "w");
  int i, j;

  if (f == NULL) {
    printf("Erro com o ficheiro %s\n", filename);
    fclose(f);
    return;
  } else {
    for (i = 0; i < editor.lines; i++) {
      for (j = 0; j < editor.columns; j++) {
        fprintf(f, "%c", editor.content[i][j]);
      }
      fprintf(f, "\n");
    }
  }
  fclose(f);
}

void users() {
  char pipe[20];
  sprintf(pipe, "pipe-%d", editor.pid);

  system("clear");
  printf("Utilizador: %s\n", editor.username);
  printf("Nome do Pipe: %s\n", pipe);
}

void settings() {
  system("clear");
  printf("Numero de Linhas: %d\nNumero de colunas: %d\nNumero Max. de "
         "Utilizadores: %d\nNome do Pipe Principal: %s\n",
         editor.lines, editor.columns, editor.max_users, PIPE);
}

void load_file(char *filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("Erro ao carregar ficheiro : %s\n", filename);
    return;
  }

  for (int x = 0; x < editor.lines; x++) {
    for (int y = 0; y < editor.columns; y++) {
      fscanf(file, "%c", &editor.content[x][y]);
    }
  }
  fclose(file);
}

void text() {
  system("clear");

  for (int i = 0; i < editor.lines; i++) {
    printf("%d ", i + 1); // FALTAR IMPRIMIR O NOME DO USER
    for (int j = 0; j < editor.columns; j++) {
      printf("%c", editor.content[i][j]);
    }
    printf("\n");
  }
}

void free_row(char content[][MAX_COLUMNS], int line) {
  for (int i = 0; i < MAX_COLUMNS; i++)
    content[line][i] = ' ';
}

void count_chars(char *aux) {
  int count = 0;
  while (*aux) {
    if (!isspace(*aux++))
      count++;
  }
  printf("Numero de letras:%d\n", count);
}

void statistics(char array[][MAX_COLUMNS]) {
  char *p = strtok(array[0], " ");
  int n_words = 0;

  while (p) {
    printf("Palavra: %s\n", p);
    count_chars(p);
    ++n_words;
    p = strtok(NULL, " ");
  }
  printf("\nTotal de Palavras:%d\n", n_words);
}

void cmd(char *com) {
  char **arg = NULL;
  char *p = strtok(com, " ");
  int n_spaces = 0;

  /* dividir a string e anexar tokens em 'arg' */
  while (p) {
    arg = realloc(arg, sizeof(char *) * ++n_spaces);
    if (arg == NULL)
      exit(-1); /* falha na alocação de meḿória */
    arg[n_spaces - 1] = p;
    p = strtok(NULL, " ");
  }

  int fd;
  char pipe[20];
  sprintf(pipe, "../pipe-%d", editor.pid);
  fd = open(pipe, O_WRONLY);
  /* Realocar um elemento extra para o último NULL */
  arg = realloc(arg, sizeof(char *) * (n_spaces + 1));
  arg[n_spaces] = 0;

  if (strcmp(arg[0], "load") == 0) {
    if (arg[1]) {
      if (verify_file_existence(arg[1]) == 0)
        load_file(arg[1]);
      else {
        printf("Ficheiro nao encontrado!\n");
        return;
      }
    } else {
      printf("Faltam argumentos!\n");
      return;
    }
  } else if (strcmp(arg[0], "save") == 0) {
    if (arg[1])
      save_settings(arg[1]); // ../out/exemplo.txt (exemplo)
    else {
      printf("Faltam argumentos!\n");
      return;
    }
  } else if (strcmp(arg[0], "shutdown") == 0)
    shutdown();
  else if (strcmp(arg[0], "settings") == 0)
    settings();
  else if (strcmp(arg[0], "sair") == 0)
    shutdown();
  else if (strcmp(arg[0], "users") == 0)
    users();
  else if (strcmp(arg[0], "text") == 0)
    text();
  else if (strcmp(arg[0], "free") == 0) {
    if (arg[1]) {
      free_row(editor.content, atoi(arg[1]));
      editor.action = FREE;
      write(fd, &editor, sizeof(editor));
    } else {
      printf("Faltam argumentos!\n");
      return;
    }
  } else if (strcmp(arg[0], "statistics") == 0)
    statistics(editor.content);
  else {
    printf("Comando inválido!\n");
    return;
  }
  free(arg);
}