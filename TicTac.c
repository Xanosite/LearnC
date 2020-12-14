/*
Plays a game of Tic-Tac-Toe

BUGS:

TO DO:
- add comments explaining robo brain and subs
- Make better UI
- Clean
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static void print_grid(char * tGrid);
static void get_name(char * playerName);
static char check_win(char * grid);
static char turn_changer(char * lastTurn);
static void player_turn(char * grid, char * playerName);
static void game_end(char winState, char * playerName);
static void print_title();
static void get_console_input(char * input, int maxLength);
static void game_engine(char * playerName);
static int replay();
static char check_two_h(char * grid, char player);
static char check_two_v(char * grid, char player);
static char check_two_d(char * grid, char player);
static char robo_brain(char * grid);
static void clear_screen();

int main()
{
  char * playerName = malloc(60);
  print_title();
  get_name(playerName);
  do
  {
    game_engine(playerName);
  } while (replay() == 1);
  free(playerName);
  return 0;
}

static void game_engine(char * playerName)
/* runs the actual ggame */
{
  char * grid = malloc(15);
  strcpy(grid, "---------");
  char turn = 2;
  char lastTurn = 2;
  char winState = 0;
  /*Generates seed for rand() based on time*/
  srand(time(0));
  /* main engine */
  while(1)
  {
    winState = check_win(grid);
    if (winState != 0)
    {
      clear_screen();
      print_grid(grid);
      game_end(winState, playerName);
      free(grid);
      break;
    }
    turn = turn_changer(&lastTurn);
    if (turn == 1)
    {
      clear_screen();
      grid[robo_brain(grid)] = 'O';
    }
    else
    {
      clear_screen();
      print_grid(grid);
      player_turn(grid, playerName);
    }
  }
  free(grid);
}

static void print_grid(char * tGrid)
/*prints the play grid to console*/
{
  printf("\n#########################################\n\n");
  printf("         7    ##    8    ##    9    \n");
  printf("              ##         ##         \n");
  printf("         %c    ##    %c    ##    %c    \n", tGrid[0], tGrid[1], tGrid[2]);
  printf("              ##         ##         \n");
  printf("              ##         ##         \n");
  printf("     ###############################\n");
  printf("         4    ##    5    ##    6    \n");
  printf("              ##         ##         \n");
  printf("         %c    ##    %c    ##    %c    \n", tGrid[3], tGrid[4], tGrid[5]);
  printf("              ##         ##         \n");
  printf("              ##         ##         \n");
  printf("     ###############################\n");
  printf("         1    ##    2    ##    3    \n");
  printf("              ##         ##         \n");
  printf("         %c    ##    %c    ##    %c    \n", tGrid[6], tGrid[7], tGrid[8]);
  printf("              ##         ##         \n");
  printf("              ##         ##         \n\n");
  printf("#########################################\n");
}

static void get_name(char * playerName)
/*takes inout for player name*/
{
  printf("\n <Player Name>: ");
  get_console_input(playerName, 50);
  printf(" <Computer> \"%s is it? I'll keep that in mind when you lose.\"\n", playerName);
}

static char check_win(char * grid)
/*Returns winning character if there is one, else returns 0 for continue, 1 for stalemate*/
{
  /*horizontal or vertical win state check*/
  int i;
  for (i = 0; i < 4; i++ )
  {
    /*checks for horizontal win states*/
    if (grid[i*3] != '-' && grid[i*3] == grid[i*3+1] && grid[i*3+1] == grid[i*3+2])
    {
      return grid[i*3];
    }
    /*checks for vertical win state*/
    if (grid[i] != '-' && grid[i] == grid[i+3] && grid[i+3] == grid[i+6])
    {
      return grid[i];
    }
  }
  /*checks for diagonal win state, ugly*/
  if (grid[4] != '-')
  {
    if (grid[0] == grid[4] && grid[8] == grid[4])
    {
      return grid[4];
    }
    else if (grid[2] == grid[4] && grid[6] == grid[4])
    {
      return grid[4];
    }
  }
  for (i = 0; i < 9; i++)
  {
    if (grid[i] == '-')
    {
      return 0;
    }
  }
  return 1;
}

static char turn_changer(char * lastTurn)
/*if last turn is 2 (no one) randomly decides whos turn it is
  otherwise, determines who's turn it is now
  1 = Computer
  0 = Player*/
{
  if (*lastTurn == 2)
  {
    printf(" <Computer> \"You can be X's, I'll be O's.\"\n");
    if (rand() % 2 == 0)
    {
      printf(" <Computer> \"Ha! I get to go first this time!\"\n");
      *lastTurn = 0;
    }
  }
  if (*lastTurn == 0)
  {
    *lastTurn = 1;
    return 1;
  }
  else
  {
    *lastTurn = 0;
    return 0;
  }
}

static void player_turn(char * grid, char * playerName)
/* get input from player as to where they want to place the marl */
/* berate them for fucking it up */
{
  int i;
  while(1)
  {
    printf(" <Computer> \"Pick your space, %s\": ", playerName);
    char * tempS = malloc(20);
    get_console_input(tempS, 10);
    i = tempS[0] - '0';
    free(tempS);
    i--;
    /* swap positions around to match keypad */
    switch (i)
    {
      case 6: i = 0; break;
      case 7: i = 1; break;
      case 8: i = 2; break;
      case 0: i = 6; break;
      case 1: i = 7; break;
      case 2: i = 8; break;
    }
    if (grid[i] != '-')
    {
      printf(" <Computer> \"You're not the brightest bulb, are you?\"\n");
      printf(" <Computer> \"The numbers are the spaces...obviously.\"\n");
      continue;
    }
    else
    {
      grid[i] = 'X';
      break;
    }
  }
}

static void game_end(char winState, char *  playerName)
{
  if (winState == 1)
  {
    printf(" <Computer> \"It's a draw, well played %s!\"\n", playerName);
  }
  else if (winState == 'X')
  {
    printf(" <Computer> \"You win this time, %s!\"\n", playerName);
  }
  else
  {
    printf(" <Computer> \"I won this game %s!\"\n", playerName);
  }
  printf(" <Computer> \"Will I beat you next time?\"\n");
}

static void print_title()
{
  printf("######################################################################\n");
  printf("#  _______  _             _______                 _______            #\n");
  printf("# |__   __|(_)           |__   __|               |__   __|           #\n");
  printf("#    | |    _   ___  ______ | |  __ _   ___  ______ | |  ___    ___  #\n");
  printf("#    | |   | | / __||______|| | / _` | / __||______|| | / _ \\  / _ \\ #\n");
  printf("#    | |   | || (__         | || (_| || (__         | || (_) | |  __/ #\n");
  printf("#    |_|   |_| \\___|        |_| \\__,_| \\___|        |_| \\___/  \\___/ #\n");
  printf("######################################################################\n");
  printf("#              Welcome to a simple game of Tic-Tac-Toe!              #\n");
  printf("#        Can you beat the computer? It sure doesn't think so!        #\n");
  printf("#====================================================================#\n");
  printf("#                         Made by:  Xanosite                         #\n");
  printf("######################################################################\n");
}

static void get_console_input(char * input, int maxLength)
/* Gets input from console */
{
  int c;
  fgets(input, maxLength, stdin);
  c = strlen(input);
  /* finds and replaces newline with null */
  input[strcspn(input, "\r\n")] = 0;
  /* if input exceeds max length, erase remaining input
     console input requires ENTER, so if not found, input was too long */
  if (c == strlen(input)) { while ((c = getchar()) != '\n' && c != EOF); }
}

static int replay()
/* return 1 to replay, 0 to exit */
{
  char * tempS = malloc(10);
  printf(" <Computer> \"Play again?\" YES / NO: ");
  get_console_input(tempS, 5);
  if (tempS[0] == 'Y' || tempS[0] == 'y')
  {
    free(tempS);
    printf("\n\n\n\n\n\n");
    print_title();
    return 1;
  }
  free(tempS);
  return 0;
}

static char check_two_h(char * grid, char player)
/* returns location to play if player has 2 in a row horizontally, else 77 */
{
  char line[3];
  char i, j, k;
  for (i = 0; i < 3; i++)
  {
    line[0] = grid[i * 3];
    line[1] = grid[i * 3 + 1];
    line[2] = grid[i * 3 + 2];
    j = 0;
    for (k = 0; k < 3; k++) { if (line[k] == player) { j++; } }
    if (j > 1)
    {
      for (k = 0; k < 3; k++)
      {
        if (line[k] == '-')
        {
          return (i * 3 + k);
        }
      }
    }
  }
  return 77;
}

static char check_two_v(char * grid, char player)
/* returns location to play if player has two in a row vertically, else 77 */
{
  char line[3];
  char i, j, k;
  for (i = 0; i < 3; i++)
  {
    line[0] = grid[i];
    line[1] = grid[i + 3];
    line[2] = grid[i + 6];
    j = 0;
    for (k = 0; k < 3; k++) { if (line[k] == player) { j++; } }
    if (j > 1)
    {
      for (k = 0; k < 3; k++)
      {
        if (line[k] == '-')
        {
          return (i + (3 * k));
        }
      }
    }
  }
  return 77;
}

static char check_two_d(char * grid, char player)
/* returns location to play if player has two in a row diagonally, else 77 */
{
  if (grid[4] == player)
  {
    if (grid[0] == player)
    {
      return 8;
    }
    else if (grid[2] == player)
    {
      return 6;
    }
    else if (grid[6] == player)
    {
      return 2;
    }
    else if (grid[8] == player)
    {
      return 0;
    }
  }
  return 77;
}

static char robo_brain(char * grid)
/* decides where computer will place it's mark */
{
  /* check if computer can win this move */
  char move;
  int i;
  move = check_two_d(grid, 'O'); if (move != 77 && grid[move] == '-') { return move; }
  move = check_two_h(grid, 'O'); if (move != 77 && grid[move] == '-') { return move; }
  move = check_two_v(grid, 'O'); if (move != 77 && grid[move] == '-') { return move; }
  /* check if player has two in a row */
  move = check_two_d(grid, 'X'); if (move != 77 && grid[move] == '-') { return move; }
  move = check_two_h(grid, 'X'); if (move != 77 && grid[move] == '-') { return move; }
  move = check_two_v(grid, 'X'); if (move != 77 && grid[move] == '-') { return move; }
  /* checks if diags are avaliable */
  if (grid[0] == '-' || grid[2] == '-' || grid[6] == '-' || grid[8] == '-')
  {
    while(1)
    {
      i = rand() % 4;
      switch (i)
      {
        case 0: move = 0; break;
        case 1: move = 2; break;
        case 2: move = 6; break;
        case 3: move = 8; break;
      }
      if (grid[move] == '-') { return move; }
    }
  }
  /* picks middle if open */
  if (grid[4] == '-') { return 4; }
  /* picks a mid as last choice */
  if (move == 77)
  {
    while(1)
    {
      i = rand() % 4;
      switch (i)
      {
        case 0: move = 1; break;
        case 1: move = 3; break;
        case 2: move = 5; break;
        case 3: move = 7; break;
      }
      if (grid[move] == '-') { return move; }
    }
  }
}

static void clear_screen()
{
  system("cls");
  print_title();
}
