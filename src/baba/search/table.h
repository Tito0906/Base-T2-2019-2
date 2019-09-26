#pragma once
#include <stdint.h>
#include "../board/board.h"

/** Elemento guardado en la tabla que incluye board y valor del hash */
typedef struct data
{
  /** Valor del hash del board almacenado */
  uint64_t hash;
  /** Tablero mismo */
  Board* board;
} Data;

/** Tabla de hash */
typedef struct table
{
  /** Arreglo de datas */
  Data** array;
  /** Tamanio del arreglo */
  int size;
  /** Numero de elementos en el arreglo */
  int count;
} Table;

/** Inicializa la tabla vacia */
Table* table_init(uint8_t height, uint8_t width);

/** Inserta board si no existe y retorna true. Sino, retorna False */
bool table_insert(Table* table, Board* board);

/** Libera la tabla de hash y todos los tablero en ella */
void table_destroy(Table* table);
