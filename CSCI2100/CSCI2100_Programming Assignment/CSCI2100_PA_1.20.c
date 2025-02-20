#include <stdio.h>
#define STR_SIZE 31

int main()
{
  // initialize t and counter for loop
  int t, i, j, k;
  // scan line no.
  scanf("%d", &t);
  getchar(); // remove '\n'
  char temp[t][STR_SIZE];

  // read from input
  for (i = 0; i < t; i++)
  {
    scanf("%s", temp[i]);
  }

  // print output lines
  for (j = 0; j < t; j++)
  {
    for (k = 0; k < STR_SIZE; k++)
    {
      // remove no.
      if (temp[j][k] >= '0' && temp[j][k] <= '9')
        continue;
      // check end
      if (temp[j][k] == 0)
        break;
      printf("%c", temp[j][k]);
    }
    printf("\n");
  }
  return 0;
}