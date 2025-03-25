#include <stdio.h>

void sort(int* arr, int n) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int tmp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = tmp;
		}
	}
}

int main(void) {
	int arr[10] = {4, 62, -5, 90, 65, 32, 9, 59, 8, 1};
	sort(arr, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
	return 0;
}
