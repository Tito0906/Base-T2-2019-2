#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "../random/random.h"

/** Calcula una mala funcion de hash del tablero */
static uint64_t bad_hash(Board* board)
{
  /*
  Esta funcion numera las posiciones del tablero desde la 1 hasta la
  weight x height y multiplica el valor de los elementos que hay en la posicion
  por el indice de la posicion y suma todo.
  Es una mala funcion de hash porque los valores van a tender a caer en un
  rango pequenio
  */

  // Parto con el hash en 0
  uint64_t hash = 0;

  // Indice de la posicion
  int i = 1;
  for (int row = 0; row < board -> height; row++)
  {
    for (int col = 0; col < board -> width; col++)
    {
      // Lista de la celda
      List* list = board -> matrix[row][col];

      // Itero por los objetos de la posicion multiplicando i por el valor
      for (Cell* current = list -> first; current; current = current -> next)
      {
        // Multiplico el valor del objeto con el indice y lo sumo al hash
        hash += current -> type * i;
      }

      // Aumento el indice
      i++;
    }
  }

  // Retorno el hash
  return hash;
}

/** Hace rehash de la tabla completa */
static void rehash(Table* table)
{
  // Debes completar esto
}

/** Inicializa la tabla vacia */
Table* table_init(uint8_t height, uint8_t width)
{
  // Inicializo la tabla
  Table* table = malloc(sizeof(Table));

  // Inicializo el arreglo
  table -> size = 100000;
  table -> count = 0;
  table -> array = calloc(table -> size, sizeof(Data*));

  // Retorno la tabla
  return table;
}

/** Inserta board si no existe y retorna true. Sino, retorna False */
bool table_insert(Table* table, Board* board)
{
  // Calculo el hash del tablero
  uint64_t hash = bad_hash(board);

  // Busco el tablero en la tabla
  for (int i = 0; i < table -> count; i++)
  {
    // Veo el tablero y hash que hay en la posicion
    uint64_t h2 = table -> array[i] -> hash;
    Board* b2 = table -> array[i] -> board;

    // Si son el mismo tablero
    if (board_compare(board, hash, b2, h2))
    {
      // Retorno false porque ya existia
      return false;
    }
  }

  // Si llego hasta aca es porque no existia el tablero por lo que lo inserto
  if (table -> size == table -> count)
  {
    printf("Error: la tabla esta llena\n");
    exit(1);
  }
  table -> array[table -> count] = malloc(sizeof(Data));
  table -> array[table -> count] -> board = board;
  table -> array[table -> count] -> hash = hash;

  table -> count++;

  return true;
}

/** Libera la tabla de hash y todos los tablero en ella */
void table_destroy(Table* table)
{
  // Libero todos los tableros del arreglo, los Data, el arreglo y la tabla
  printf("Estados explorados %d\n", table -> count);
  for (int i = 0; i < table -> count; i++)
  {
    board_destroy(table -> array[i] -> board);
    free(table -> array[i]);
  }
  free(table -> array);
  free(table);
}
