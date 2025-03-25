#include <stdio.h>

void sort(int* arr, int n) {
	if (n < 2)
		return;

	for (int p = 1; p < n; p++) {
		int tmp = arr[p];
		int j;
		for (j = p; j > 0 && arr[j-1] > tmp; --j)
			arr[j] = arr[j-1];
		arr[j] = tmp;
	}
}

int main(void) {
	int arr[10] = {9, 3, 10, 589, 39, 20, 5, 8, -49, 39};
	sort(arr, 10);

	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
	return 0;
}
