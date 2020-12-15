#include <stdio.h>
#include <stdlib.h>

static void print(char * px, char x, char y, char z);

int main(void)
{
  int i;
  char j;
  char *px = malloc(3 * sizeof(char));
  px = "hi";
  char x = px[0];
  char y = px[1];
  char z = px[2];
  print(px, x, y, z);
  for (i = 0; i < 10000; i++)
  {
    px--;
  }
  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < 16; j++)
    {
      px++;
      x = px[0];
      printf("%4d ", x);
    }
    printf("\n");
  }
}

static void print(char * px, char x, char y, char z)
{
  printf("Memory Address  : %p\n", px);
  printf("Chars (x, y, z) : \"%c\", \"%c\", \"%c\"\n", x, y, z);
  printf("Values (x, y, z): \"%d\", \"%d\", \"%d\"\n", x, y, z);
}
