#ifndef Heap_h
#define Heap_h

/**
 * @brief		Imprime o heap.
 *
 * @param[in]	array				Vetor do heap.
 * @param[in]	size				Tamanho do vetor.
 */
void printArray(int *array, int size, int*d);

/**
 * @brief		Faz com que o heap fique minimo.
 *
 * @param[in]	array				Vetor do heap.
 * @param[in]	i					Indice.
 * @param[in]	sizeHeap			Tamanho do vetor.
 * @param[in]	d					Vetor que armazena o peso dos caminhos mais curtos,
 									usado como chave dentro do heap.
 */
void minHeapify(int *array, int i, int sizeHeap, int *d);

/**
 * @brief		Constroi heap minimo, sendo que o menor elemento fica na
 				primeira posicao.
 *
 * @param[in]	array				Vetor do heap.
 * @param[in]	sizeArray			Tamanho do vetor.
 * @param[in]	d					Vetor que armazena o peso dos caminhos mais curtos,
 									usado como chave dentro do heap.
 */
void buildMinHeap(int *array, int sizeArray, int *d);

#endif
