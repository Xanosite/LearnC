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
void welcome_message();
char check_win(char * grid);
char turn_changer(char * lastTurn);
void computer_turn(char * grid);
void player_turn(char * grid);
void game_end(char winState, char * playerName);

int main()
{
  char * playerName = malloc(60);
  char * grid = malloc(15);
  strcpy(grid, "---------");
  char turn = 2;
  char lastTurn = 2;
  char winState = 0;
  welcome_message();
  get_name(playerName);
  /*Generates seed for rand() based on time*/
  srand(time(0));
  /* main engine */
  while(1)
  {
    winState = check_win(grid);
    if (winState != 0)
    {
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      printf("|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|\n\n");
      print_grid(grid);
      printf("\n\n|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|\n\n");
      game_end(winState, playerName);
      free(playerName);
      free(grid);
      break;
    }
    turn = turn_changer(&lastTurn);
    if (turn == 1)
    {
      computer_turn(grid);
      printf("\n\n\n<> I've made my move, human.\n\n");
    }
    else
    {
      print_grid(grid);
      player_turn(grid);
    }
  }
  return 0;
}

void welcome_message()
{
  printf("|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|\n\n");
  printf(" Welcome to a simple game of Tic-Tac-Toe!\n\n");
  printf("|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|\n\n");
}

void print_grid(char * tGrid)
/*prints the play grid to console*/
{
  printf("     1  ||  2  ||  3  \n");
  printf("     %c  ||  %c  ||  %c  \n", tGrid[0], tGrid[1], tGrid[2]);
  printf("        ||     ||     \n   =====||=====||=====\n     4  ||  5  ||  6  \n");
  printf("     %c  ||  %c  ||  %c  \n", tGrid[3], tGrid[4], tGrid[5]);
  printf("        ||     ||     \n   =====||=====||=====\n     7  ||  8  ||  9  \n");
  printf("     %c  ||  %c  ||  %c  \n", tGrid[6], tGrid[7], tGrid[8]);
  printf("        ||     ||     \n");
}

void get_name(char * namePoint)
/*takes inout for player name*/
{
  printf(" You'll be X's and I'll be O.\n\n");
  printf("|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|\n\n");
  printf("<> What's your name, human?: ");
  fgets(namePoint, 50, stdin);
  /*removes newline or carriage return if there is one*/
  namePoint[strcspn(namePoint, "\r\n")] = 0;
  printf("<> Welcome %s, let's see how you fare.\n", namePoint);
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
    if (rand() % 2 == 0)
    {
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
      break;
    }
  }
}

void player_turn(char * grid)
/* get input from player as to where they want to place the marl */
/* berate them for fucking it up */
{
  int i;
  while(1)
  {
    printf("<> Pick your X, human: ");
    scanf("%d", &i);
    i--;
    if (grid[i] != '-')
    {
      printf("<> You're not the brightest bulb, are you?\n");
      printf("<> The numbers are the spaces...obviously.\n");
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
    printf("<> You have no more moves %s!\n", playerName);
  }
  else if (winState == 'X')
  {
    printf("<> You win this time, %s\n", playerName);
  }
  else
  {
    printf("<> I won this game %s\n", playerName);
  }
  printf("<> Will I beat you next time?");
}
