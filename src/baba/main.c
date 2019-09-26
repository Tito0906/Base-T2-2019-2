#include <stdio.h>
#include "search/bfs.h"
#include <unistd.h>
#include "watcher/watcher.h"

void show_solution(Board* current)
{
  if(current -> parent)
  {
    show_solution(current -> parent);
  }
  watcher_draw_board(current);
  usleep(500000);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Modo de uso: ./baba <rule_file.txt> <board_file.txt>\n");
    return 0;
  }

  // Leo las reglas
  initialize_rules(argv[1]);

  // Leo el tablero
  Board* board = board_init(argv[2]);

  watcher_open(board -> height, board -> width);

  // Creo una tabla de hash
  Table* table = table_init(board -> height, board -> width);

  // Hago BFS
  Board* sol = BFS(board, table);

  // Si no tengo una solucion imprimo que no hay
  if (!sol)
  {
    printf("No hay solucion\n");
  }
  else
  {
    // Mostramos la solución
    show_solution(sol);

    // Libero el tablero solucion
    board_destroy(sol);
  }

  // Libero los tableros y la tabla
  table_destroy(table);


  // Libero las reglas
  destroy_rules();

  watcher_close();

  // Todo termino bien
  return 0;
}
