#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int* temp, int left, int mid, int right) {
	int size = right - left + 1;
	int leftPointer = left;
	int rightPointer = mid + 1;
	int mergePointer = left;
	while (leftPointer <= mid && rightPointer <= right) {
		if (arr[leftPointer] <= arr[rightPointer]) {
			temp[mergePointer++] = arr[leftPointer++];
		} else {
			temp[mergePointer++] = arr[rightPointer++];
		}
	}
	while (leftPointer <= mid) {
		temp[mergePointer++] = arr[leftPointer++];
	}
	while (rightPointer <= right) {
		temp[mergePointer++] = arr[rightPointer++];
	}
	for (int i = 0; i < size; i++, right--) {
		arr[right] = temp[right];
	}
}

void msort(int* arr, int* temp, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		msort(arr, temp, left, mid);
		msort(arr, temp, mid + 1, right);
		merge(arr, temp, left, mid, right);
	}
}

void sort(int* arr, int n) {
	int* temp = (int*)malloc(sizeof(int) * n);
	msort(arr, temp, 0, n - 1);
	free(temp);
}

int main(void) {
	int arr[10] = {1, -4, 50, 9, 39, 95, 13, 49, 43, 0};
	sort(arr, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
	return 0;
}