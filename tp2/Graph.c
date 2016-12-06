#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"

void initializeSingleSource(int s, int size, int *d, int *pi) {
	int i;
	for (i = 1; i <= size; i++) {
		d[i] = INT_MAX;
		pi[i] = 0;
	}
	d[s] = 0;
}

void relax(int u, int v, int weight, int *d, int *pi) {
	int value;
	if (d[v] > d[u] + weight) {
		d[v] = d[u] + weight;
		pi[v] = u;
	}
}

void printPath(int s, int v, int *pi) {
	if (v == s) {
		printf("%d ", s);
	}else {
		if (pi[v] == 0) {
			printf("Caminho nao encontrado. ");
		}else {
			printPath(s, pi[v], pi);
			printf("%d ", v);
		}
	}
}

void dijkstra(Edge *adjacencyList, int s, int size, int indexArrayEnd) {
	int d[size+1];
	int pi[size+1];
	initializeSingleSource(s, size, d , pi);
	int *heap = (int*)malloc((size+1)*sizeof(int));
	int sizeHeap = size;
	int i;
	// Preeche indice do heap
	for (i = 1; i <= sizeHeap; i++) {
		heap[i] = i;
	}
	// Constroi heap
	buildMinHeap(heap, sizeHeap, d);
	// Cria vetor de flags visitados
	int flags[sizeHeap];
	for (i = 1; i <= sizeHeap; i++) {
		flags[i] = 0;
	}
	int firstElement;
	while (sizeHeap != 0) {
		// Retira menor elemento do heap
		firstElement = heap[1];
		if (d[firstElement] == INT_MAX) break;
		// Atualiza Heap
		heap[1] = heap[sizeHeap];
		sizeHeap--;
		minHeapify(heap, 1, sizeHeap, d);

		flags[firstElement] = 1;
		Edge *tmp = adjacencyList[firstElement].Prox;
		while (tmp != NULL) {
			relax(firstElement, tmp->vertice, tmp->weight, d, pi);
			tmp = tmp->Prox;
		}
		buildMinHeap(heap, sizeHeap, d);
	}
	free(heap);
	if (d[indexArrayEnd] == INT_MAX) {
		printf("-1\n");
	}else {
		printf("%d\n", d[indexArrayEnd]); 
	}
}

void initGraph(Edge *adjacencyList, int size) {
	int i = 1;
	for (; i <= size; i++) {
		adjacencyList[i].vertice = 0;
		adjacencyList[i].weight = 0;
		adjacencyList[i].Prox = NULL;
		adjacencyList[i].Ante = NULL;
	}
}

void printGraph(Edge *adjacencyList, int size) {
	int i = 1;
	for (; i<= size; i++) {
		printf("%d: ", i);
		Edge *tmp = adjacencyList[i].Prox;
		while (tmp != NULL) {
			printf("%d(%d) ", tmp->vertice, tmp->weight);
			tmp = tmp->Prox;
		}
		printf("\n");
	}
}

void insertEdge(Edge *adjacencyList, int a, int b, int weight) {
	Edge *aux = (Edge*) malloc(sizeof(Edge));
	aux->vertice = b;
	aux->Prox = NULL;
	aux->weight = weight;

	// Se a lista estiver vazia
	if (adjacencyList[a].Prox == NULL) {
		adjacencyList[a].Prox = aux;
	}else {
		Edge *tmp = adjacencyList[a].Prox;
		if (tmp->vertice > b) {
			aux->Prox = tmp;
			adjacencyList[a].Prox = aux;
		}else {
			// Procura valor a ser inserido ordenado
			while ((tmp->Prox != NULL) && (tmp->Prox->vertice < b)) {
				tmp = tmp->Prox;
			}
			aux->Prox = tmp->Prox;
			tmp->Prox = aux;
		}
	}
}

void insertNoRestriction(int i, int j, int width, int height, int **map, Edge *adjacencyList) {
	int a, b;
	int weight = 0;
	// Se pertence ao mapa
	if (j > 0) {
		// Se o destino nao for obstaculo
		if (map[i][j-1] != 0) {
			a = (width * i) + j + 1;
			b = (width * i) + j;
			if (map[i][j] != -1) {
				weight = map[i][j];
			}
			if (map[i][j-1] != -1) {
				weight += map[i][j-1];
			}
			// adiciona esquerda j-1
			insertEdge(adjacencyList, a, b, weight);
		}
	}
	weight = 0;
	// Pertence ao mapa
	if (j < width-1) {
		// Se o destino nao for obstaculo
		if (map[i][j+1] != 0) {
			a = (width * i) + j + 1;
			b = (width * i) + j + 2;
			if (map[i][j] != -1) {
				weight = map[i][j];
			}
			if (map[i][j+1] != -1) {
				weight += map[i][j+1];
			}
			// adiciona a direita j+1
			insertEdge(adjacencyList, a, b, weight);
		}
	}
	weight = 0;
	// Pertence ao mapa
	if (i > 0) {
		// Se o destino nao for obstaculo
		if (map[i-1][j] != 0) {
			a = (width * i) + j + 1;
			b = (width * (i-1)) + j + 1;
			if (map[i][j] != -1) {
				weight = map[i][j];
			}
			if (map[i-1][j] != -1) {
				weight += map[i-1][j];
			}
			// adiciona em cima i-1
			insertEdge(adjacencyList, a, b, weight);
		}
	}
	weight = 0;
	// Pertence ao mapa
	if (i < height-1) {
		// Se o destino nao for obstaculo
		if (map[i+1][j] != 0) {
			a = (width * i) + j + 1;
			b = (width * (i+1)) + j + 1;
			if (map[i][j] != -1) {
				weight = map[i][j];
			}
			if (map[i+1][j] != -1) {
				weight += map[i+1][j];
			}
			// adiciona em baixo i+1
			insertEdge(adjacencyList, a, b, weight);
		}
	}
}

int calculateWeightRightDown(int **map, int i, int j, int width, int height, int restrictionX, int restrictionY, int path) {
	int weight = 0;
	int index = 1;

	// Primeiro caminho
	if (path == 0) {
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j+1] != -1 && j+1 < width) {
				if (map[i][j+1] == 0) return 0;
				weight += map[i][j+1];
			}
			j++;
			index++;
		}
		index = 1;
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i+1][j] != -1 && i+1 < height) {
				if (map[i+1][j] == 0) return 0;
				weight += map[i+1][j];
			}
			i++;
			index++;
		}
	// Segundo caminho
	}else {
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i+1][j] != -1 && i+1 < height) {
				if (map[i+1][j] == 0) return 0;
				weight += map[i+1][j];
			}
			i++;
			index++;
		}
		index = 1;
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j+1] != -1 && j+1 < width) {
				if (map[i][j+1] == 0) return 0;
				weight += map[i][j+1];
			}
			j++;
			index++;
		}
	}
	return weight;
}

int calculateWeightLeftDown(int **map, int i, int j, int width, int height, int restrictionX, int restrictionY, int path) {
	int weight = 0;
	int index = 1;

	// Primeiro caminho
	if (path == 0) {
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j-1] != -1 && j-1 >= 0) {
				if (map[i][j-1] == 0) return 0;
				weight += map[i][j-1];
			}
			j--;
			index++;
		}
		index = 1;
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i+1][j] != -1 && i+1 < height) {
				if (map[i+1][j] == 0) return 0;
				weight += map[i+1][j];
			}
			i++;
			index++;
		}
	// Segundo caminho
	}else {
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i+1][j] != -1 && i+1 < height) {
				if (map[i+1][j] == 0) return 0;
				weight += map[i+1][j];
			}
			i++;
			index++;
		}
		index = 1;
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j-1] != -1 && j-1 >= 0) {
				if (map[i][j-1] == 0) return 0;
				weight += map[i][j-1];
			}
			j--;
			index++;
		}
	}
	return weight;
}

int calculateWeightRightUp(int **map, int i, int j, int width, int height, int restrictionX, int restrictionY, int path) {
	int weight = 0;
	int index = 1;

	// Primeiro caminho
	if (path == 0) {
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j+1] != -1 && j+1 < width) {
				if (map[i][j+1] == 0) return 0;
				weight += map[i][j+1];
			}
			j++;
			index++;
		}
		index = 1;
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i-1][j] != -1 && i-1 >= 0) {
				if (map[i-1][j] == 0) return 0;
				weight += map[i-1][j];
			}
			i--;
			index++;
		}
	// Segundo caminho
	}else {
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i-1][j] != -1 && i-1 >= 0) {
				if (map[i-1][j] == 0) return 0;
				weight += map[i-1][j];
			}
			i--;
			index++;
		}
		index = 1;
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j+1] != -1 && j+1 < width) {
				if (map[i][j+1] == 0) return 0;
				weight += map[i][j+1];
			}
			j++;
			index++;
		}
	}
	return weight;
}

int calculateWeightLeftUp(int **map, int i, int j, int width, int height, int restrictionX, int restrictionY, int path) {
	int weight = 0;
	int index = 1;

	// Primeiro caminho
	if (path == 0) {
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j-1] != -1 && j-1 >= 0) {
				if (map[i][j-1] == 0) return 0;
				weight += map[i][j-1];
			}
			j--;
			index++;
		}
		index = 1;
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i-1][j] != -1 && i-1 >= 0) {
				if (map[i-1][j] == 0) return 0;
				weight += map[i-1][j];
			}
			i--;
			index++;
		}
	// Segundo caminho
	}else {
		// Soma peso no eixo Y
		while (index <= restrictionY) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1) 
				weight += map[i][j];
			if (map[i-1][j] != -1 && i-1 >= 0) {
				if (map[i-1][j] == 0) return 0;
				weight += map[i-1][j];
			}
			i--;
			index++;
		}
		index = 1;
		// Soma peso no eixo X
		while (index <= restrictionX) {
			if (map[i][j] == 0) return 0;

			if (map[i][j] != -1)
				weight += map[i][j];
			if (map[i][j-1] != -1 && j-1 >= 0) {
				if (map[i][j-1] == 0) return 0;
				weight += map[i][j-1];
			}
			j--;
			index++;
		}
	}
	return weight;
}

void insertWithRestriction(int i, int j, int width, int height, int **map, Edge *adjacencyList, int restrictionX, int restrictionY) {
	int a, b;
	int weight1, weight2;

	// Se pertence ao mapa (direita, baixo)
	if (j+restrictionX <= width-1 && i+restrictionY <= height-1) {
		// Calcular peso primeiro caminho
		weight1 = calculateWeightRightDown(map, i, j, width, height, restrictionX, restrictionY, 0);
		// Calcular peso segundo caminho
		weight2 = calculateWeightRightDown(map, i, j, width, height, restrictionX, restrictionY, 1);
		// Inserir primeiro caminho
		a = (width * i) + j + 1;
		b = (width * (i+restrictionY)) + j + restrictionX +1;
		if (weight1 < weight2 && weight1 != 0) {
			insertEdge(adjacencyList, a, b, weight1);
		}else {
			if (weight2 != 0) {
				insertEdge(adjacencyList, a, b, weight2);
			}else {
				if (weight1 != 0) {
					insertEdge(adjacencyList, a, b, weight1);
				}
			}
		}
	}
	// Se pertence ao mapa (esquerda, baixo)
	if (j-restrictionX >= 0 && i+restrictionY <= height-1) {
		// Calcular peso primeiro caminho
		weight1 = calculateWeightLeftDown(map, i, j, width, height, restrictionX, restrictionY, 0);
		// Calcular peso segundo caminho
		weight2 = calculateWeightLeftDown(map, i, j, width, height, restrictionX, restrictionY, 1);
		// Inserir primeiro caminho
		a = (width * i) + j + 1;
		b = (width * (i+restrictionY)) + j - restrictionX +1;
		if (weight1 < weight2 && weight1 != 0) {
			insertEdge(adjacencyList, a, b, weight1);
		}else {
			if (weight2 != 0) {
				insertEdge(adjacencyList, a, b, weight2);
			}else {
				if (weight1 != 0) {
					insertEdge(adjacencyList, a, b, weight1);
				}
			}
		}
	}
	// Se pertence ao mapa (direita, cima)
	if (j+restrictionX <= width-1 && i-restrictionY >= 0) {
		// Calcular peso primeiro caminho
		weight1 = calculateWeightRightUp(map, i, j, width, height, restrictionX, restrictionY, 0);
		// Calcular peso segundo caminho
		weight2 = calculateWeightRightUp(map, i, j, width, height, restrictionX, restrictionY, 1);
		// Inserir primeiro caminho
		a = (width * i) + j + 1;
		b = (width * (i-restrictionY)) + j + restrictionX +1;
		if (weight1 < weight2 && weight1 != 0) {
			insertEdge(adjacencyList, a, b, weight1);
		}else {
			if (weight2 != 0) {
				insertEdge(adjacencyList, a, b, weight2);
			}else {
				if (weight1 != 0) {
					insertEdge(adjacencyList, a, b, weight1);
				}
			}
		}
	}
	// Se pertence ao mapa (esquerda, cima)
	if (j-restrictionX >= 0 && i-restrictionY >= 0) {
		// Calcular peso primeiro caminho
		weight1 = calculateWeightLeftUp(map, i, j, width, height, restrictionX, restrictionY, 0);
		// Calcular peso segundo caminho
		weight2 = calculateWeightLeftUp(map, i, j, width, height, restrictionX, restrictionY, 1);
		// Inserir primeiro caminho
		a = (width * i) + j + 1;
		b = (width * (i-restrictionY)) + j - restrictionX +1;
		if (weight1 < weight2 && weight1 != 0) {
			insertEdge(adjacencyList, a, b, weight1);
		}else {
			if (weight2 != 0) {
				insertEdge(adjacencyList, a, b, weight2);
			}else {
				if (weight1 != 0) {
					insertEdge(adjacencyList, a, b, weight1);
				}
			}
		}
	}
}

void insertAllEdges(int restrictionX, int restrictionY, int width, int height, int **map, Edge *adjacencyList) {
	int i, j;
	int maxSize = width*height;
	int shortcutList[maxSize];
	int numberShortcut = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			// Se for atalho salva posicao no vetor
			if (map[i][j] == -1) {
				shortcutList[numberShortcut] = (width*i) + j + 1;
				numberShortcut++;
			} 
			if (map[i][j] == 0) continue;

			// Se a restricao for 0,0
			if (restrictionX == 0 && restrictionY == 0) {
				insertNoRestriction(i, j, width, height, map, adjacencyList);
			}else {
				insertWithRestriction(i, j, width, height, map, adjacencyList, restrictionX, restrictionY);
			}
		}
	}
	// Insere aresta entre todos os atalhos
	int k, l;
	for (k = 0; k < numberShortcut; k++) {
		for (l = 0; l < numberShortcut; l++) {
			if (shortcutList[l] != shortcutList[k]) {
				insertEdge(adjacencyList, shortcutList[k], shortcutList[l], 0);
			}
		}
	}
}
