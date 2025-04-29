#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  int m, n;
  int no;
  double ans;
  for (int i = 0; i < cases; i++) {
    scanf("%d %d", &m, &n);
    no = m + n;
    int arr[no];
    for (int j = 0; j < no; j++){
      scanf("%d", &arr[j]);
    }
    qsort(arr, no, sizeof(int), compare);
    if (no % 2 == 0){
      ans = (double) (arr[no/2 - 1] + arr[no/2]) / 2.0;
    }
    else {
      ans = arr[no/2];
    }
    printf("%.1f\n", ans);
  }
}