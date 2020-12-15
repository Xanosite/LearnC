#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static char number_placement_check( char * sudukoGrid, char number, char location);

/*
    Grid Format:
    00 01 02 | 03 04 05 | 06 07 08
    09 10 11 | 12 13 14 | 15 16 17
    18 19 20 | 21 22 23 | 24 25 26
    ------------------------------
    27 28 29 | 30 31 32 | 33 34 35
    36 37 38 | 39 40 41 | 42 43 44
    45 46 47 | 48 49 50 | 51 52 53
    ------------------------------
    54 55 56 | 57 58 59 | 60 61 62
    63 64 65 | 66 67 68 | 69 70 71
    72 73 74 | 75 76 77 | 78 79 80

    location % 9 = column index
    location - (location % 9) / 9 = row index

*/

int main(void)
{
  char * sudukoGrid = calloc(81, sizeof(char));
  srand(time(0));
}

static char number_placement_check(char * sudukoGrid, char number, char location)
/* returns 1 if there are no matches in the column or row, else, returns 0 */
{
  char columnModifier = location % 9;
  char rowModifier = location - (location % 9);
  char i;
  char clear = 2;
  for (i = 0; i < 9; i++)
  {
    if (sudukoGrid[(i * 9) + columnModifier] == number || sudukoGrid[rowModifier + i] == number)
    {
      clear = 0;
      i = 10;
    } else
    {
      clear = 1;
    }
  }
  return clear;
}
