#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * #include <stdlib.h>
 * NOTSTABLE: void qsort (void *base, size_t nmemb, size_t size, int (*compar ) (const void *, const void * ))
 * NOTSTABLE: int heapsort (void *base, size_t nmemb, size_t size, int (*compar ) (const void *, const void * ))
 * STABLE: 		int mergesort (void *base, size_t nmemb, size_t size, int (*compar ) (const void *, const void * ))
*/

/**
 * qsort(arr, n, size, comp);
 * arr: Pointer to the first element of the array.
 * n: Number of elements in the array.
 * size: Size of each element.
 * comp: Function pointer to a comparison function/comparator.
 * 				> 0 => a > b
 * 				< 0 => a < b
 * 				= 0 => a = b
*/

// qsort ascending order
int intAsc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// qsort descending order
int intDes(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

// Comparison function to sort strings in ascending order
int strAsc(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

// Comparison function to sort strings in descending order
int strDes(const void *a, const void *b) {
  return strcmp(*(const char **)b, *(const char **)a);
}

int main() {
	int a[50] = {
		8, 6, 4, 24, 63, 74, 77, 21, 78, -23, 5, 9, 2, 0, 52,
		67, 89, -3, 52, 785, 84, 65, 43, 244, 633, 744, 757, 261,
		778, -203, 38, 68, 40, 8724, 6893, 7844, -77, 2361, 478,
		-233, 48, 56, 64, 2457, 6383, 7004, 7577, 271, 7874, -253};

	const char *aw[] = {
		"tiger", "house", "banana", "queen", "rabbit", "apple", "monkey", "dog",
		"violin", "penguin", "elephant", "frog", "grape", "zebra", "sun", "ice",
		"orange", "lemon", "whale", "jungle", "night", "umbrella", "cat", "kite",
		"x-ray", "yummy"};
	
	int arr1[100000];
	int arr2[100000];
	int arr3[100000];

	srand((unsigned) time(NULL));	
	for (int i = 0; i < 100000; i++) {
		int num = rand();
		arr1[i] = arr2[i] = arr3[i] = num;
	}

	int size = sizeof(aw) / sizeof(aw[0]);
	
    clock_t tick, tock;

	tick = clock();
    qsort(a, 50, sizeof(a[0]), intAsc);
	tock = clock();
	printf("Quick Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	tick = clock();
    qsort(aw, 26, sizeof(aw[0]), strAsc);
	tock = clock();
	printf("Quick Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	for (int i = 0; i < 50; i++)
        printf("%d ", a[i]);
	putchar('\n');
	for (int i = 0; i < size; i++)
        printf("%s ", aw[i]);
	putchar('\n');

	tick = clock();
    heapsort(a, 50, sizeof(a[0]), intDes);
	tock = clock();
	printf("Heap Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	tick = clock();
    heapsort(aw, 26, sizeof(aw[0]), strDes);
	tock = clock();
	printf("Heap Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	for (int i = 0; i < 50; i++)
        printf("%d ", a[i]);
	putchar('\n');
	for (int i = 0; i < size; i++)
        printf("%s ", aw[i]);
	putchar('\n');

	tick = clock();
    mergesort(a, 50, sizeof(a[0]), intAsc);
	tock = clock();
	printf("Merge Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	tick = clock();
    mergesort(aw, 26, sizeof(aw[0]), strAsc);
	tock = clock();
	printf("Merge Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	for (int i = 0; i < 50; i++)
		printf("%d ", a[i]);
	putchar('\n');
	for (int i = 0; i < size; i++)
		printf("%s ", aw[i]);
	putchar('\n');
	
	tick = clock();
    qsort(arr1, 100000, sizeof(arr1[0]), intAsc);
	tock = clock();
	printf("Quick Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	tick = clock();
    heapsort(arr2, 100000, sizeof(arr2[0]), intAsc);
	tock = clock();
	printf("Heap Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	tick = clock();
    mergesort(arr3, 100000, sizeof(arr3[0]), intAsc);
	tock = clock();
	printf("Merge Sort (Time spent: %.8f):\n", (double) (tock - tick) / CLOCKS_PER_SEC);

	return 0;
}