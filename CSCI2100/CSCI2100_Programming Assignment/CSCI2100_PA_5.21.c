#include <stdio.h>
#include <stdlib.h>

enum Type { EMPTY, ACTIVE, DELETED };

typedef struct _entry {
    enum Type type;
    int key;
} Entry;

typedef struct _hashTable {
    int currSize;
    int maxSize;
    Entry* arr;
} HashTable;

int isPrime(int num) {
	int i;
	for (i = 2; i * i <= num; i++) {
		if (num % i == 0)
			return 0;
	}
	return 1;
}

int nextPrime(int num) {
	while (!isPrime(num)) {
		num++;
	}
	return num;
}

Entry* createEntryList(int size) {
    Entry* entry = malloc(sizeof(Entry) * size);
    int i;
    for (i = 0; i < size; i++) {
        entry[i].type = EMPTY;
    }
    return entry;
}

HashTable* createHashTable(int size) {
    if (!isPrime(size)) {
        size = nextPrime(size);
    }
    HashTable* ht = malloc(sizeof(HashTable));
    ht->arr = createEntryList(size);
    ht->currSize = 0;
    ht->maxSize = size;
    return ht;
}

void freeHashTable(HashTable* ht) {
    free(ht->arr);
	free(ht);
}

int hash(HashTable *ht, int key, int probes) {
    return ((key % ht->maxSize) + probes * probes) % ht->maxSize;
}

HashTable* insert(HashTable *ht, int key) {
    int probe = 0;
    int hashVal = hash(ht, key, probe);
    while (ht->arr[hashVal].type == ACTIVE) {
        probe++;
        hashVal = hash(ht, key, probe);
    }

    ht->arr[hashVal].key = key;
    ht->arr[hashVal].type = ACTIVE;
    ht->currSize++;
    
    if (ht->currSize * 2 >= ht->maxSize) {
		HashTable* temp = ht;
		ht = createHashTable(nextPrime(temp->maxSize * 2));
        int i;
		for (i = 0; i < temp->maxSize; i++){
			if (temp->arr[i].type == ACTIVE) {
				insert(ht, temp->arr[i].key);
			}
		}
		freeHashTable(temp);
	}

	return ht;
}

int find(HashTable* ht, int key) {
    int probes = 0;
    int hashVal = hash(ht, key, probes);
    while (ht->arr[hashVal].type == DELETED || (ht->arr[hashVal].type == ACTIVE && ht->arr[hashVal].key != key)) {
        probes++;
        hashVal = hash(ht, key, probes);
    }
    if (ht->arr[hashVal].type == EMPTY) {
		return 0;
	}
	return 1;
}

int indexVal(HashTable* ht, int key) {
    int probes = 0;
    int hashVal = hash(ht, key, probes);
    while (ht->arr[hashVal].type == DELETED || (ht->arr[hashVal].type == ACTIVE && ht->arr[hashVal].key != key)) {
        probes++;
        hashVal = hash(ht, key, probes);
        if (probes >= ht->maxSize) {
            return -1;
        }
    }
    return hashVal;
}


void findTri(int* arr, HashTable *ht, int no, int tar) {
    int i, j;
    int count = 0;
    int twoAns, remainder;
    int zero = 0;
    for (i = 0; i < no; i++) {
        for (j = i+1; j < no; j++){
            twoAns = arr[i] * arr[j];
            if (tar == 0){
                for (int i = 0; i < no; i++) {
                    if (arr[i] == 0) {
                        zero = 1;
                        break;
                    }
                }
                if (zero == 1){
                    count = (no - 1) * (no - 2) / 2;
                }
                printf("%d\n", count);
                return;
            }
            if (twoAns != 0 && tar%twoAns == 0){
                remainder = tar / twoAns;
                if (remainder != arr[i] && remainder != arr[j]){
                    if (!find(ht, remainder)){
                        continue;
                    }
                    if (indexVal(ht, remainder) < indexVal(ht, arr[i]) || indexVal(ht, remainder) < indexVal(ht, arr[j])){
                        continue;
                    }
                    count++;
                }
            }
        }
    }
    printf("%d\n", count);
}

int main() {
    int cases, n, m, size, temp;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d %d", &n, &m);
        size = nextPrime(n); // Ensure the table size is prime
        HashTable* ht = createHashTable(size);
        int arr[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            ht = insert(ht, arr[i]);
        }
        findTri(arr, ht, n, m);
        freeHashTable(ht);
    }
    return 0;
}
