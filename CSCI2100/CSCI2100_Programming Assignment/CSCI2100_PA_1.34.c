#include <stdio.h>

int main()
{
  // initialize m, n and counter for loop
  int m, n, i, j;
  int maxEvenNo, temp;

  // scan line no.
  scanf("%d", &m);
  getchar(); // remove '\n'

  for (i = 0; i < m; i++)
  {
    maxEvenNo = 0; // initialize & restore value of maxEvenNo
    scanf("%d", &n); // scan no. of elements
    getchar(); // remove '\n'

    // scan elements, find max no.
    for (j = 0; j < n; j++)
    {
      scanf("%d", &temp);
      
      // proceed if even no.
      if (temp % 2 == 0)
      {
        // update max even no if find larger one
        if (temp > maxEvenNo)
          maxEvenNo = temp;
      }

      // skip odd no.
      else
        continue;
    }
    getchar();

    // output: max no of the line
    printf("%d\n", maxEvenNo);
  }
  
  return 0;
}