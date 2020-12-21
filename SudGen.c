#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Notepad:

*/

static char get_legal_numbers(char * sudukoGrid, char location, char * validNumbers);
static char number_legal_check( char * sudukoGrid, char location, char number);
static void valid_numbers_arr_handler(char * validNumbers, char newNumber);
static char get_block_start(char location);
static char pick_from_legal(char * validNumbers);

static char test_handler(char printVar);
static char test_number_legal_check(char printVar);
static char test_get_block_start(char printVar);
static char test_get_legal_numbers(char printVar);
static char test_pick_from_legal(char printVar);

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

    columnModifier = location % 9
    rowModifier = location - (location % 9)
    blockColumnModifier = column - (column % 3)
    blockRowModifier = ((rowModifier / 9) - ((rowModifier / 9) % 3)) * 9
    blockIndex = blockRowModifier                                                                    + blockColumnModifier
    blockIndex = (((rowModifier / 9) - ((rowModifier / 9) % 3)) * 9)                                 + (column - (column % 3))
    blockIndex = ((((location - (location % 9)) / 9) - (((location - (location % 9)) / 9) % 3)) * 9) + ((location % 9) - ((location % 9) % 3))


*/

int main(void)
{
  char * sudukoGrid = calloc(81, sizeof(char));
  srand(time(0));
  if (test_handler(1) == 0)
  {
    return 1;
  }
  return 0;
}

/* begin test function area */

static char test_handler(char printVar)
{
  char allPassed = 1;
  if (test_get_block_start(printVar) == 0) { allPassed = 0; }
  if (test_number_legal_check(printVar) == 0) { allPassed = 0; }
  if (test_get_legal_numbers(printVar) == 0) { allPassed = 0; }
  if (test_pick_from_legal(printVar) == 0) { allPassed = 0; }
  if (allPassed = 0) { printf("Unit test failure.\n"); }
  return allPassed;
}

static char test_number_legal_check(char printVar)
{
  char pass = 1;
  char * testSudukoGrid = calloc(81, sizeof(char));
  char i;
  if (printVar == 1)
  {
    printf("Begin unit test of function \"number_legal_check\": \n");
  }
  /* test 1 */
  for (i = 0; i < 9; i++)
  {
    testSudukoGrid[(i*9) + 4] = i + 1;
    testSudukoGrid[36 + i] = i + 1;
  }
  for (i = 0; i < 3; i++)
  {
    testSudukoGrid[30 + (i * 9)] = (i * 3) + 1;
    testSudukoGrid[31 + (i * 9)] = (i * 3) + 2;
    testSudukoGrid[32 + (i * 9)] = (i * 3) + 3;
  }
  /* frees location 40 and number 5 for testing */
  testSudukoGrid[40] = 0;
  /* test if known legal will result in legal */
  if (number_legal_check(testSudukoGrid, 40, 5) == 0)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Location: 40  Number: 5  Legal: Y  ResultLegal: N  Status: Fail\n");
    }
  }
  else
  {
    if (printVar == 1)
    {
      printf("Location: 40  Number: 5  Legal: Y  ResultLegal: Y  Status: Pass\n");
    }
  }
  /* test if known illegal will result in legal */
  if (number_legal_check(testSudukoGrid, 40, 3) == 1)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Location: 40  Number: 3  Legal: N  ResultLegal: Y  Status: Fail\n");
    }
  }
  else
  {
    if (printVar == 1)
    {
      printf("Location: 40  Number: 3  Legal: N  ResultLegal: N  Status: Pass\n");
    }
  }
  /* test if known illegal in block will result in illegal */
  testSudukoGrid[30] = 5;
  if (number_legal_check(testSudukoGrid, 40, 5) == 1)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Location: 40  Number: 5  Legal: N  ResultLegal: Y  Status: Fail\n");
    }
  }
  else
  {
    if (printVar == 1)
    {
      printf("Location: 40  Number: 5  Legal: N  ResultLegal: N  Status: Pass\n");
    }
  }
  if (printVar == 1)
  {
    printf("End unit test of \"number_legal_check\".\n\n");
  }
  free(testSudukoGrid);
  return pass;
}

static char test_get_block_start(char printVar)
{
  /* tests all possible locations to see if the function returns the correct start point */
  char corrResult = 0;
  char i;
  char pass = 1;
  char funcResult = 0;
  if (printVar == 1)
  {
    printf("Begin unit test of function \"get_block_start\":\n");
  }
  /* goes through all options and sets test values the stupid way */
  for (i = 0; i < 81; i++)
  {
    if (i == 0 || i == 1 || i == 2 || i == 9 || i == 10 || i == 11 || i == 18 || i == 19 || i == 20) { corrResult = 0; }
    else if (i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14 || i == 21 || i == 22 || i == 23) { corrResult = 3; }
    else if (i == 6 || i == 7 || i == 8 || i == 15 || i == 16 || i == 17 || i == 24 || i == 25 || i == 26) { corrResult = 6; }
    else if (i == 27 || i == 28 || i == 29 || i == 36 || i == 37 || i == 38 || i == 45 || i == 46 || i == 47) { corrResult = 27; }
    else if (i == 30 || i == 31 || i == 32 || i == 39 || i == 40 || i == 41 || i == 48 || i == 49 || i == 50) { corrResult = 30; }
    else if (i == 33 || i == 34 || i == 35 || i == 42 || i == 53 || i == 44 || i == 51 || i == 52 || i == 53) { corrResult = 33; }
    else if (i == 54 || i == 55 || i == 56 || i == 63 || i == 64 || i == 65 || i == 72 || i == 73 || i == 74) { corrResult = 54; }
    else if (i == 57 || i == 58 || i == 59 || i == 66 || i == 67 || i == 68 || i == 75 || i == 76 || i == 77) { corrResult = 57; }
    else if (i == 60 || i == 61 || i == 63 || i == 69 || i == 70 || i == 71 || i == 78 || i == 79 || i == 80) { corrResult = 60; }
    funcResult = get_block_start(i);
    if (funcResult != corrResult)
    {
      pass = 0;
      if (printVar == 1)
      {
        printf("Location: %2d  Result: %2d  Correct Result: %2d  Status: Fail\n", i, funcResult, corrResult);
      }
    }
    else
    {
      if (printVar == 1)
      {
        printf("Location: %2d  Result: %2d  Correct Result: %2d  Status: Pass\n", i, funcResult, corrResult);
      }
    }
  }
  if (printVar == 1)
  {
    printf("End unit test of function \"get_block_start\".\n\n");
  }
  return pass;
}

static char test_get_legal_numbers(char printVar)
{
  char * testSudukoGrid = calloc(81, sizeof(char));
  char * testArr = calloc(11, sizeof(char));
  char i, pass;
  pass = 1;
  if (printVar == 1) {
    printf("Begin unit test of function \"get_legal_numbers\":\n");
  }
  /* isolate and test vertical */
  for (i = 0; i < 9; i++)
  {
    testSudukoGrid[1 + (i * 9)] = i + 1;
  }
  testSudukoGrid[28] = 0;
  testSudukoGrid[19] = 0;
  get_legal_numbers(testSudukoGrid, 19, testArr);
  if (testArr[0] == 0)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Vertical isolation test:   Open Location: 19, 28  Open Number: 3, 4  Output: Null  Result: Fail\n");
    }
  }
  else if (testArr[1] != 3 || testArr[2] != 4)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Vertical isolation test:   Open Location: 19, 28  Open Number: 3, 4  Output: %d, %d  Result: Fail\n", testArr[1], testArr[2]);
    }
  }
  else if (printVar == 1)
  {
    printf("Vertical isolation test:   Open Location: 19, 28  Open Number: 3, 4  Output: %d, %d  Result: Pass\n", testArr[1], testArr[2]);
  }
  /* clear grid */
  for (i = 0; i < 81; i++)
  {
    testSudukoGrid[i] = 0;
  }
  /* clear arr */
  for (i = 0; i < 11; i++)
  {
    testArr[i] = 0;
  }
  /* isolate and test horizontal */
  for (i = 0; i < 9; i++)
  {
    testSudukoGrid[9 + i] = i + 1;
  }
  /* free locations 10,11 and numbers 2, 3 */
  testSudukoGrid[10] = 0;
  testSudukoGrid[11] = 0;
  get_legal_numbers(testSudukoGrid, 11, testArr);
  if (testArr[0] == 0)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Horizontal isolation test: Open Location: 10, 11  Open Number: 2, 3  Output: Null  Result: Fail\n");
    }
  }
  else if (testArr[1] != 2 || testArr[2] != 3)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Horizontal isolation test: Open Location: 10, 11  Open Number: 2, 3  Output: %d, %d  Result: Fail\n", testArr[1], testArr[2]);
    }
  }
  else if (printVar == 1)
  {
    printf("Horizontal isolation test: Open Location: 10, 11  Open Number: 2, 3  Output: %d, %d  Result: Pass\n", testArr[1], testArr[2]);
  }
  /* clear grid */
  for (i = 0; i < 81; i++)
  {
    testSudukoGrid[i] = 0;
  }
  /* clear arr */
  for (i = 0; i < 11; i++)
  {
    testArr[i] = 0;
  }
  /* isolate and test block */
  for (i = 0; i < 3; i++)
  {
    testSudukoGrid[30 + (i * 9)] = (i * 3) + 1;
    testSudukoGrid[31 + (i * 9)] = (i * 3) + 2;
    testSudukoGrid[32 + (i * 9)] = (i * 3) + 3;
  }
  /* free locations 31, 41 and numbers 2,6 */
  testSudukoGrid[31] = 0;
  testSudukoGrid[41] = 0;
  get_legal_numbers(testSudukoGrid, 31, testArr);
  if (testArr[0] == 0)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Block isolation test:      Open Location: 31, 41  Open Number: 2, 6  Output: Null Result: Fail\n");
    }
  }
  else if (testArr[1] != 2 || testArr[2] != 6)
  {
    pass = 0;
    if (printVar == 1)
    {
      printf("Block isolation test:      Open Location: 31, 41  Open Number: 2, 6  Output: %d, %d Result: Fail\n", testArr[1], testArr[2]);
    }
  }
  else if (printVar == 1)
  {
    printf("Block isolation test:      Open Location: 31, 41  Open Number: 2, 6  Output: %d, %d  Result: Pass\n", testArr[1], testArr[2]);
  }
  if (printVar == 1)
  {
    printf("End unit test of function \"get_legal_numbers\".\n\n");
  }
  return pass;
}

static char test_pick_from_legal(char printVar)
{
  char * testArr = calloc(11, sizeof(char));
  char tempResult, i;
  char pass = 1;
  if (printVar)
  {
    printf("Begin unit test of function \"pick_from_legal\':\n");
  }
  testArr[1] = 2;
  testArr[2] = 3;
  testArr[3] = 4;
  testArr[4] = 5;
  for (i = 0; i < 25; i++)
  {
    tempResult = pick_from_legal(testArr);
    if ( ! (tempResult == 2 || tempResult == 3 || tempResult == 4 || tempResult == 5))
    {
      pass = 0;
      if (printVar)
      {
        printf("Valid Numbers: 2, 3, 4, 5  Number Picked: %d  Result: Fail\n", tempResult);
      }
    }
    else if (printVar)
    {
      printf("Valid Numbers: 2, 3, 4, 5  Number Picked: %d  Result: Pass\n", tempResult);
    }
  }
  if (printVar)
  {
    printf("End unit test of function \"pick_from_legal\".\n\n");
  }
  return pass;
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
  char blockStart = get_block_start(location);
  char i;
  /* checks for horizintal and vertical matches */
  for (i = 0; i < 9; i++)
  {
    if (sudukoGrid[(i * 9) + columnModifier] == number || sudukoGrid[rowModifier + i] == number)
    {
      return 0;
    }
  }
  /* checks for matches within block area */
  for (i = 0; i < 3; i++)
  {
    if (sudukoGrid[blockStart + (i * 9)] == number || sudukoGrid[blockStart + (i * 9) + 1] == number || sudukoGrid[blockStart + (i * 9) + 2] == number)
    {
      return 0;
    }
  }
  return 1;
}

static void valid_numbers_arr_handler(char * validNumbers, char newNumber)
{
  char i;
  validNumbers[0] += 1;
  for (i = 1; i < 10; i++)
  {
    if (validNumbers[i] == 0)
    {
      validNumbers[i] = newNumber;
      i = 10;
    }
  }
}

static char get_block_start(char location)
{
  /*
  columnModifier = location % 9
  rowModifier = location - (location % 9)
  blockColumnModifier = column - (column % 3)
  blockRowModifier = ((rowModifier / 9) - ((rowModifier / 9) % 3)) * 9
  blockIndex = blockRowModifier                                                                    + blockColumnModifier
  blockIndex = (((rowModifier / 9) - ((rowModifier / 9) % 3)) * 9)                                 + (column - (column % 3))
  blockIndex = ((((location - (location % 9)) / 9) - (((location - (location % 9)) / 9) % 3)) * 9) + ((location % 9) - ((location % 9) % 3))
  ^ seriously....
  */
  return (((((location - (location % 9)) / 9) - (((location - (location % 9)) / 9) % 3)) * 9) + ((location % 9) - ((location % 9) % 3)));
}

static char pick_from_legal(char * validNumbers)
/* picks a random number from the legal ones */
{
  char i, j;
  /* iterates through legal numbers and counts how many there are to choose from by increasing j */
  for (i = 1, j = 0; i < 10; i++)
  {
    if (validNumbers[i] != 0) { j++; }
  }
  return validNumbers[(rand() % j) + 1];
}
