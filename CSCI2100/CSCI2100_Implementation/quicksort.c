#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int* arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int temp = arr[i];
		int j;
		for (j = i; j > left && arr[j-1] > temp; j--) {
			arr[j] = arr[j-1];
		}
		arr[j] = temp;
	}
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void print(int* arr, int left, int right) {
	for (int i = left; i <= right; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

int median3(int* arr, int left, int right) {
	int mid = (left + right) / 2;
	if (arr[left] > arr[mid])
		swap(&arr[left], &arr[mid]);
	if (arr[left] > arr[right])
		swap(&arr[left], &arr[right]);
	if (arr[mid] > arr[right])
		swap(&arr[mid], &arr[right]);
	
	swap(&arr[mid], &arr[right-1]);
	return arr[right-1];
}

void helper(int* arr, int left, int right) {
	if (left + 10 >= right) {
		insertionSort(arr, left, right);
	} else {
		int pivot = median3(arr, left, right);
		int i = left;
		int j = right - 1;
		while (1) {
			while (arr[++i] < pivot) {}
			while (arr[--j] > pivot) {}
			if (i < j) {
				swap(&arr[i], &arr[j]);
				//printf("Swap: ");
				//print(arr, left, right);
			} else
				break;
		}
		swap(&arr[right-1], &arr[i]);
		//printf("One pass: ");
		//print(arr, left, right);
		helper(arr, left, i - 1);
		helper(arr, i + 1, right);
	}
}

void quickSort(int* arr, int n) {
	helper(arr, 0, n - 1);
}

int main(void) {
  	clock_t tick, tock;

	int arr[50] = {8, 6, 4, 24, 63, 74, 77, 21, 78, -23, 5, 9, 2,  0, 52, 
				67, 89, -3, 52, 785, 84, 65, 43, 244, 633, 744, 757, 261, 
				778, -203, 38, 68, 40, 8724, 6893, 7844, -77, 2361, 478, 
				-233, 48, 56, 64, 2457, 6383, 7004, 7577, 271, 7874, -253};
  	
	tick = clock();
	quickSort(arr, 50);
  	tock = clock();
	print(arr, 0, 49);

  	printf("Quick Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	int arr1[100000];

	srand((unsigned) time(NULL));	
	for (int i = 0; i < 100000; i++) {
		int num = rand();
		arr1[i] =num;
	}

	tick = clock();
	quickSort(arr1, 100000);
	tock = clock();
	
	printf("Quick Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);
	return 0;
}
