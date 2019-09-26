#include <stdio.h>
#include "search/bfs.h"
#include <unistd.h>
#include <string.h>
#include "watcher/watcher.h"

void show_solution(Board* current, bool watch)
{
  if(current -> parent)
  {
    show_solution(current -> parent, watch);
  }
  if (watch)
  {
    watcher_draw_board(current);
    usleep(500000);
  }
  else
  {
    board_print(current);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3 && argc != 4)
  {
    printf("Modo de uso: ./baba <rule_file.txt> <board_file.txt> [-w]\n");
    printf("El paramatro opcional sirve para usar la interfaz grafica [-w]\n");
    return 0;
  }
  bool watch = false;
  if (argc == 4 && strcmp(argv[3], "-w") == 0)
  {
    watch = true;
  }

  // Leo las reglas
  initialize_rules(argv[1]);

  // Leo el tablero
  Board* board = board_init(argv[2]);

  // Si hay interfaz
  if (watch)
  {
    watcher_open(board -> height, board -> width);
	watcher_draw_board(board);
  }

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
    show_solution(sol, watch);

    // Libero el tablero solucion
    board_destroy(sol);
  }

  // Libero los tableros y la tabla
  table_destroy(table);


  // Libero las reglas
  destroy_rules();

  if (watch)
  {
    watcher_close();
  }

  // Todo termino bien
  return 0;
}
