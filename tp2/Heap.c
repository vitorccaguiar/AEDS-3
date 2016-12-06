#include <stdio.h>
#include "Heap.h"

void printArray(int *array, int size, int* d) {
	int i = 1;
	while (i <= size) {
		printf("%d ", d[array[i]]);
		i++;
	}
	printf("\n");
}

void minHeapify(int *array, int i, int sizeHeap, int *d) {
	int left = 2*i;
	int right = (2*i)+1;
	int min;
	if (left <= sizeHeap && d[array[left]] < d[array[i]]) {
		min = left;
	}else {
		min = i;
	}
	if (right <= sizeHeap && d[array[right]] < d[array[min]]) {
		min = right;
	}
	if (min != i) {
		int aux = array[i];
		array[i] = array[min];
		array[min] = aux;
		minHeapify(array, min, sizeHeap, d);
	}
}

void buildMinHeap(int *array, int sizeArray, int *d) {
	int sizeHeap = sizeArray;
	int i = (sizeArray/2) - 1;
	for (; i >= 1; i--) {
		minHeapify(array, i, sizeHeap, d);
	}
}
