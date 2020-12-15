
static void get_console_input(char * input, int maxLength);
/*
Gets user input from console
Removes new line characters
clears input of any unread data
*/
static void get_console_input(char * input, int maxLength)
/* Accepts user input from console */
{
  int c;
  fgets(input, maxLength, stdin);
  c = strlen(input);
  input[strcspn(input, "\r\n")] = 0;
  if (c == strlen(input))
  {
    while ((c = getchar()) != '\n' && c != EOF);
  }
}

/* clears the console */
system("cls");
