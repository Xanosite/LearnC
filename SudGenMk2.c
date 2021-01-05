#include <stdio.h>
#include <stdlib.h>

struct GridUnit
{
  char location, current, qty_legal;
  char arr_legal[10];
};
typedef struct GridUnit GridUnit;

static void testf(GridUnit * SudukoGrid);

int main()
{
  GridUnit l00;
  GridUnit *pl00 = & l00;
  pl00->location = 0;
  pl00->current = 5;
  pl00->qty_legal = 8;
  pl00->arr_legal[0] = 1;
  printf("Location: %2d  Value: %d  Options: %d  Opt1: %d\n", pl00->location, pl00->current, pl00->qty_legal, pl00->arr_legal[0]);
  GridUnit * SudukoGrid = calloc(81, sizeof(struct GridUnit));
  SudukoGrid[0].location = 15;
  printf("Location %d\n", SudukoGrid[0].location);
  testf(SudukoGrid);
  printf("Location %d\n", SudukoGrid[0].location);
  return 0;
}

static void testf(GridUnit * SudukoGrid)
{
  SudukoGrid[0].location = 7;
}
