/*
Plays a single game of Tic-Tac-Toe
Computer does not have any reasoning, just random
only plays once, repeat issue found with fgets

TO DO:
- Add replayability
- Clean up UI
- Add heuristic algo to computer emoves*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_grid(char * tGrid);
void get_name(char * namePoint);
char check_win(char * grid);
char turn_changer(char * lastTurn);
void computer_turn(char * grid);
void player_turn(char * grid, char * playerName);
void game_end(char winState, char * playerName);
void print_title();

int main()
{
  print_title();
  char * playerName = malloc(60);
  char * grid = malloc(15);
  strcpy(grid, "---------");
  char turn = 2;
  char lastTurn = 2;
  char winState = 0;
  get_name(playerName);
  /*Generates seed for rand() based on time*/
  srand(time(0));
  /* main engine */
  while(1)
  {
    winState = check_win(grid);
    if (winState != 0)
    {
      print_grid(grid);
      game_end(winState, playerName);
      free(playerName);
      free(grid);
      break;
    }
    turn = turn_changer(&lastTurn);
    if (turn == 1)
    {
      computer_turn(grid);
    }
    else
    {
      print_grid(grid);
      player_turn(grid, playerName);
    }
  }
  return 0;
}

void print_grid(char * tGrid)
/*prints the play grid to console*/
{
  printf("\n#########################################\n\n");
  printf("         1    ##    2    ##    3    \n");
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
  printf("         7    ##    8    ##    9    \n");
  printf("              ##         ##         \n");
  printf("         %c    ##    %c    ##    %c    \n", tGrid[6], tGrid[7], tGrid[8]);
  printf("              ##         ##         \n");
  printf("              ##         ##         \n\n");
  printf("#########################################\n");
}

void get_name(char * namePoint)
/*takes inout for player name*/
{

  printf("\n <Player Name>: ");
  fgets(namePoint, 50, stdin);
  /*removes newline or carriage return if there is one*/
  namePoint[strcspn(namePoint, "\r\n")] = 0;
  printf(" <Computer> \"%s is it? I'll keep that in mind when you lose.\"\n", namePoint);
}

char check_win(char * grid)
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

char turn_changer(char * lastTurn)
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

void computer_turn(char * grid)
/*picks a random spot to mark...for now*/
{
  int i;
  while(1)
  {
    i = rand() % 9;
    if (grid[i] == '-')
    {
      grid[i] = 'O';
      printf("\n <Computer> \"I picked %d, your turn.\"\n", i+1);
      break;
    }
  }
}

void player_turn(char * grid, char * playerName)
/* get input from player as to where they want to place the marl */
/* berate them for fucking it up */
{
  int i;
  while(1)
  {
    printf(" <Computer> \"Pick your space, %s\": ", playerName);
    scanf("%d", &i);
    i--;
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

void game_end(char winState, char *  playerName)
{
  if (winState == 1)
  {
    printf(" <Computer> \"You have no more moves %s!\"\n", playerName);
  }
  else if (winState == 'X')
  {
    printf(" <Computer> \"You win this time, %s\"\n", playerName);
  }
  else
  {
    printf(" <Computer> \"I won this game %s\"\n", playerName);
  }
  printf(" <Computer> \"Will I beat you next time?\"");
}

void print_title()
{
  printf("######################################################################\n");
  printf("#  _______  _             _______                 _______            #\n");
  printf("# |__   __|(_)           |__   __|               |__   __|           #\n");
  printf("#    | |    _   ___  ______ | |  __ _   ___  ______ | |  ___    ___  #\n");
  printf("#    | |   | | / __||______|| | / _` | / __||______|| | / _ \\  / _ \\ #\n");
  printf("#    | |   | || (__         | || (_| || (__         | || (_) ||  __/ #\n");
  printf("#    |_|   |_| \\___|        |_| \\__,_| \\___|        |_| \\___/  \\___/ #\n");
  printf("######################################################################\n");
  printf("#              Welcome to a simple game of Tic-Tac-Toe!              #\n");
  printf("#        Can you beat the computer? It sure doesn't think so!        #\n");
  printf("#====================================================================#\n");
  printf("#                         Made by:  Xanosite                         #\n");
  printf("######################################################################\n");
}
