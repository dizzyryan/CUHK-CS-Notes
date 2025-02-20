#include <stdio.h>
#include <stdbool.h>

bool isPowerOfFive(long n);

int main()
{
  // initialize t and counter for loop
  long m, i;
  // scan line no.
  scanf("%ld", &m);
  getchar(); // remove '\n'
  long list[m];

  // read from input
  for (i = 0; i < m; i++)
  {
    scanf("%ld", &list[i]);
  }

  // check isPowerOfFive
  for (i = 0; i < m; i++)
  {
    if (isPowerOfFive(list[i]))
    {
      printf("True\n");
    }
    else
    {
      printf("False\n");
    }
  }
  return 0;
}

// check is power of five
bool isPowerOfFive(long n)
{
  long pow = 5l;
  if (n == 1l)
  {
    return true;
  }
  while (pow < n)
  {
    pow *= 5l;
  }
  if (pow == n)
  {
    return true;
  }
  else
  {
    return false;
  }
}