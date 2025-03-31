#include <stdio.h>
#include <stdlib.h>

enum Type { EMPTY, ACTIVE, DELETED };

typedef struct _entry {
	enum Type type;
	int key;
} Entry;

typedef struct _hashtable {
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
	Entry* entry = (Entry*)malloc(sizeof(Entry) * size);
	for (int i = 0; i < size; i++)
		entry[i].type = EMPTY;
	return entry;
}

HashTable* createHashTable(int size) {
	if (!isPrime(size)){
		size = nextPrime(size);
	}
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	ht->arr = createEntryList(size);
	ht->currSize = 0;
	ht->maxSize = size;
	return ht;
}

void freeHashTable(HashTable* ht) {
	free(ht->arr);
	free(ht);
}

// Linear hash
// int hash(HashTable *ht, int inKey, int probes){
// 	return ((inKey % ht->maxSize) + probes) % ht->maxSize;
// }

// string hash function
// int hash(HashTable* ht, const char* key){
// 	int hash = 0;
// 	while(*key != '\0' )
// 		hash += *key++;
// 	return hash % ht->maxSize;
// }

// int hash(HashTable* ht, const char* key){
// 	return ( Key[ 0 ] + 27 * Key[ 1 ] + 729 * Key[ 2 ] ) % TableSize;
// }

// Quadratic hash function
int hash(HashTable* ht, int inKey, int probes) {
	return ((inKey % ht->maxSize) + probes * probes) % ht->maxSize;
}

HashTable* insert(HashTable* ht, int key) {
	int probes = 0;
	int hashVal = hash(ht, key, probes);
	while (ht->arr[hashVal].type == ACTIVE) {
		// if (ht->arr[hashVal].key == key){
		// 	printf("Duplicated entry!\n");
		// 	return;
		// }
		probes++;
		hashVal = hash(ht, key, probes);
		// if (hashVal == ht->maxSize) {
		// 	printf("FULL TABLE!\n");
		// 	return;
		// }
	}
	ht->arr[hashVal].key = key;
	ht->arr[hashVal].type = ACTIVE;
	ht->currSize++;

	if (ht->currSize * 2 >= ht->maxSize) {
		HashTable* temp = ht;
		ht = createHashTable(nextPrime(temp->maxSize * 2));
		for (int i = 0; i < temp->maxSize; i++){
			if (temp->arr[i].type == ACTIVE) {
				insert(ht, temp->arr[i].key);
			}
		}
		freeHashTable(temp);
	}
	return ht;
}

void delete(HashTable* ht, int key) {
	int probes = 0;
	int hashVal = hash(ht, key, probes);
	while (ht->arr[hashVal].type == DELETED || (ht->arr[hashVal].type == ACTIVE && ht->arr[hashVal].key != key)) {
		probes++;
		hashVal = hash(ht, key, probes);
	}
	if (ht->arr[hashVal].type == ACTIVE) {
		ht->arr[hashVal].type = DELETED;
	}
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

int main(void) {
	HashTable* ht = createHashTable(7);
	ht = insert(ht, 190);
	ht = insert(ht, 1311);
	ht = insert(ht, 689);
	ht = insert(ht, 92);
	ht = insert(ht, 87);
	ht = insert(ht, 69);
	ht = insert(ht, 420);
	if (find(ht, 92)) puts("YES 1");
	if (!find(ht, 88)) puts("YES 2");
	if (find(ht, 689)) puts("YES 3");
	delete(ht, 689);
	delete(ht, 190);
	delete(ht, 1311);
	if (!find(ht, 689)) puts("YES 4");
	if (find(ht, 92)) puts("YES 5");
	if (!find(ht, 1311)) puts("YES 6");
	delete(ht, 92);
	if (!find(ht, 92)) puts("YES 7");
	freeHashTable(ht);
	return 0;
}