#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void freeAdjacencyList(Edge *adjacencyList, int size) {
	int i = 1;
	for (; i <= size; i++) {
		Edge *aresta = adjacencyList[i].Prox;
		while (aresta != NULL) {
			Edge *tmp = aresta->Prox;
			free(aresta);
			aresta = tmp;
		}
	}
}

void printMap(int **map, int height, int width) {
	int i = 0;
	for (; i < height; i++) {
		int j = 0;
		for (; j < width; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

int** createMap(FILE *arq, int *size, int *width, int *height) {
	fscanf(arq, "%d %d", &(*width), &(*height));
	*size = (*width)*(*height);
	int** map = (int**)malloc((*width) * sizeof(int*));
	int i = 0;
	for (; i < *width; i++) {
		map[i] = (int*)malloc((*height) * sizeof(int));
	}
	i = 0;
	// Preenche o mapa com os valores dos pesos
	for (; i < *height; i++) {
		int j = 0;
		for (; j < *width; j++) {
			fscanf(arq, "%d", &map[i][j]);
		}
	}
	return map;
}

void** freeMap(int** map, int width) {
	int i;
	for (i = 0; i < width; i++) {
		free(map[i]);
	}
	free(map);
}

int main(int argc, char **argv) {
	// Parametros de execucao
	char *fileName = argv[1];
	int startX = atoi(argv[2]);
	int startY = atoi(argv[3]);
	int endX = atoi(argv[4]);
	int endY = atoi(argv[5]);
	int restrictionX = atoi(argv[6]);
	int restrictionY = atoi(argv[7]);

	FILE *arq = fopen(fileName, "r");
	if (arq == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	int size, width, height;
	// Cria, preenche o mapa e inicializa variaveis de largura e altura
	int **map = createMap(arq, &size, &width, &height);

	// Cria e inicializa lista de adjacencia
	Edge *adjacencyList = (Edge*) malloc(sizeof(Edge) * (size+1));
	initGraph(adjacencyList, size);

	insertAllEdges(restrictionX, restrictionY, width, height, map, adjacencyList);

	// Coordenadas iniciais/finais convertidas
	int indexArrayStart = (width * startY) + startX + 1;
	int indexArrayEnd = (width * endY) + endX + 1;

	dijkstra(adjacencyList, indexArrayStart, size, indexArrayEnd);

	fclose(arq);
	freeMap(map, width);
	freeAdjacencyList(adjacencyList, size);
	free(adjacencyList);
	return 0;
}
