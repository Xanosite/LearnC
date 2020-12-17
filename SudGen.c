#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Notepad:
- Add readout to test_number_legal_check()
    I don't trust what I can't see after previous issues with this test function not populating the test grid
    format it as:
        Begin unit test of function "number_legal_check"
        Pass with Number # in location ##
        Fail with number # in location ##:
            H ## ## ## ## ## ## ## ## ## : # # # # # # # # #
            V ## ## ## ## ## ## ## ## ## : # # # # # # # # #
        End unit test of "number_legal_check": Pass/Fail
*/

static char get_legal_numbers(char * sudukoGrid, char location, char * validNumbers);
static char number_legal_check( char * sudukoGrid, char location, char number);
static void valid_numbers_arr_handler(char * validNumbers, char newNumber);

static void test_handler(char * sudukoGrid);
static char test_number_legal_check();

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
  test_handler(sudukoGrid);
  return 0;
}

/* begin test function area */

static void test_handler(char * sudukoGrid)
{
  printf("Testing number_legal_check: ");
  if (test_number_legal_check() == 1)
  {
    printf("Passed\n");
  }
}

static char test_number_legal_check()
/*
  tests 5 random spots with good assignemnt of numbers
  tests 5 random spots with bad assignemnt of numbers
*/
{
  char * testSudukoGrid = calloc(81, sizeof(char));
  char location;
  char number;
  /* test iterator */
  char t;
  /* number iterator (1-9) */
  char i;
  /* location iterator */
  char j;
  char columnModifier;
  char rowModifier;
  for (t = 0; t < 5; t++)
  {
    /* gets a random location and number to test with */
    location = rand() % 81;
    number = (rand() % 9) + 1;
    columnModifier = location % 9;
    rowModifier = location - (location % 9);
    /* fills in the vertical & horizontal portions of the grid */
    for (i = 1; i < 10; i++)
    {
      if (i == number) { continue; }
      for (j = 0; j < 9; j++)
      {
        /* assign vertical if empty and not the location to be tested */
        if (testSudukoGrid[(j * 9) + columnModifier] == 0 && (j * 9) + columnModifier != location)
        {
          testSudukoGrid[(j * 9) + columnModifier] = i;
          break;
        }
      }
      for (j = 0; j < 9; j++)\
      {
        /* assign horizontal if empty and not the location to be tested  */
        if (testSudukoGrid[rowModifier + j] == 0 && rowModifier + j != location)
        {
          testSudukoGrid[rowModifier + j] = i;
          break;
        }
      }
    }
    if (number_legal_check(testSudukoGrid, location, number) != 1)
    {
      printf("\nError: test_number_legal_check caused fail state with data:\n");
      printf("Number: %d\nLocation: %d", number, location);
      printf("Horizontal data:");
      for (i = 0; i < 9; i++)
      {
        printf("%2d : %d", (rowModifier + i), testSudukoGrid[rowModifier + i]);
      }
      printf("\nVertical Data:");
      for (i = 0; i < 9; i++)
      {
        printf("%2d: %d", ((i * 9) + columnModifier), testSudukoGrid[(i * 9) + columnModifier]);
      }
      return 0;
    }
    number = (number == 9) ? number -1: number + 1;
    if (number_legal_check(testSudukoGrid, location, number) == 1)
    {
      printf("\nError: test_number_legal_check caused false correct state with data:\n");
      printf("Number: %d\nLocation: %d\n", number, location);
      printf("Horizontal data: ");
      for (i = 0; i < 9; i++)
      {
        printf("%2d:%d ", (rowModifier + i), testSudukoGrid[rowModifier + i]);
      }
      printf("\nVertical Data:");
      for (i = 0; i < 9; i++)
      {
        printf("%2d:%d ", ((i * 9) + columnModifier), testSudukoGrid[(i * 9) + columnModifier]);
      }
      return 0;
    }
    /* clear grid and data */
    for (i == 0; i < 81; i++)
    {
      testSudukoGrid[i] = 0;
    }
    location = 0;
    number = 0;
    columnModifier = 0;
    rowModifier = 0;
  }
  free(testSudukoGrid);
  return 1;
}

/* end test function area */

static char get_legal_numbers(char * sudukoGrid, char location, char * validNumbers)
/* assigns any legal numbers to validNumbers 1-9 */
{
  char i;
  validNumbers[0] = 0;
  for (i = 1; i < 10; i++)
  {
    if (number_legal_check(sudukoGrid, location, i))
    {
      valid_numbers_arr_handler(validNumbers, i);
    }
  }
  return validNumbers[0];
}

static char number_legal_check(char * sudukoGrid, char location, char number)
/* returns 1 if there are no matches in the column or row, else, returns 0 */
{
  char columnModifier = location % 9;
  char rowModifier = location - (location % 9);
  char i;
  for (i = 0; i < 9; i++)
  {
    if (sudukoGrid[(i * 9) + columnModifier] == number || sudukoGrid[rowModifier + i] == number)
    {
      return 0;
    }
  }
  return 1;
}


static void valid_numbers_arr_handler(char * validNumbers, char newNumber)
{
  char i;
  validNumbers[0] = 1;
  for (i = 1; i < 10; i++)
  {
    if (validNumbers[i] == 0)
    {
      validNumbers[i] = newNumber;
      i = 10;
    }
  }
}
