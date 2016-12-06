#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Algorithms.h"

char *readFile(int *maxWidth, int *maxHeight, int *exponent, int *factor, char *inputFileName) {
	FILE *arq = fopen(inputFileName, "r");
	if (arq == NULL) { 
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}
	fseek(arq, 0, SEEK_END);
	int size = ftell(arq);
	fseek(arq, 0, SEEK_SET);

	fscanf(arq, "%d %d\n%d %d\n", maxWidth, maxHeight, exponent, factor);
	char *text = (char*) malloc(sizeof(char)* size);
	fgets(text, size, arq);

	fclose(arq);
	return text;
}

int *createArrayOffset(char *text, int *numberWords) {
	char c = text[0];
	int i = 0;
	*numberWords = 1;
	// Conta o numero de palavras
	while (c != '\0') {
		if (c == ' ') *numberWords = *numberWords + 1;
		i++;
		c = text[i];
	}
	int *offsets = (int*) malloc((*numberWords + 1) * sizeof(int));
	i = 1;
	int k = 1;
	// Atribui valor inicial
	offsets[0] = 0;
	while (text[i] != '\0') {
		// Se for um espaco seguido de uma letra
		if (text[i-1] == ' ' && text[i] != ' ') {
			offsets[k] = i;
			k++;
		}
		i++;
	}
	if (text[i] == '\0') offsets[k] = i+1;
	return offsets;
}

int **createMemoMatrix(int numberWords, int maxHeight) {
	int **memo = (int**) malloc((numberWords+1) * sizeof(int*));
	int i;
	for (i = 0; i <= numberWords; i++) {
		memo[i] = (int*) malloc((maxHeight+1) * sizeof(int));
		int j;
		for (j = 0; j <= maxHeight; j++) {
			memo[i][j] = -1;
		}
	}
	return memo;
}

void freeMemo(int **memo, int numberWords) {
	int i;
	for (i = 0; i <= numberWords; i++) {
		free(memo[i]);
	}
	free(memo);
}

void defineOperation(char *type, int i, int *numberWords, int maxWidth, int maxHeight,
					 char *text, int *offsets, int exponent, int factor, char *outputFileName) {
	// Abre arquivo pra escrever a saida
	FILE *arq = fopen(outputFileName, "w");
	if (arq == NULL) { 
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}
	// Se o algoritmo for forca bruta
	if (strcmp(type, "-b") == 0) {
		// Cria vetor pai para auxiliar na impressao
		int *parent = (int*) malloc(*numberWords * sizeof(int));
		memset(parent, 0, (*numberWords)*sizeof(int));
		// Calcula/Imprime custo
		int cust = bruteForce(0, numberWords, maxWidth, maxHeight, text, offsets, exponent, factor, 0, parent);
		fprintf(arq, "%d\n", cust);
		// Insire as quebras de linhas no texto original
		int i = 0;
		while (i < *numberWords-2) {
			if (parent[i] != *numberWords) text[offsets[parent[i]]-1] = '\n';
			i = parent[i];
		}
		fprintf(arq, "%s", text);
		free(parent);
	}
	// Se o algoritmo for guloso
	if (strcmp(type, "-g") == 0) {
		int cust = greedy(0, text, numberWords, maxWidth, maxHeight, offsets, exponent, factor, 0);
		fprintf(arq, "%d\n%s", cust, text);
	}
	// Se o algoritmo for programacao dinamica
	if (strcmp(type, "-d") == 0) {
		// Cria vetor pai para auxiliar na impressao
		int *parent = (int*) malloc(*numberWords * sizeof(int));
		memset(parent, 0, (*numberWords)*sizeof(int));
		// Cria vetor para memorizacao
		int **memo = createMemoMatrix(*numberWords, maxHeight);
		// Calcula/Imprime custo
		int cust = dynamicProgramming(0, numberWords, maxWidth, maxHeight, text, offsets, exponent, factor, 0, parent, memo);
		fprintf(arq, "%d\n", cust);
		// Insire as quebras de linhas no texto original
		int i = 0;
		while (i < *numberWords-2) {
			if (parent[i] != *numberWords) text[offsets[parent[i]]-1] = '\n';
			i = parent[i];
		}
		fprintf(arq, "%s", text);
		free(parent);
		freeMemo(memo, *numberWords);
	}
	fclose(arq);
}

int main(int argc, char **argv) {
	// Recebe parametros de execucao
	char *type = argv[1];
	char *inputFileName = argv[2];
	char *outputFileName = argv[3];

	// Recebe parametros do arquivo de entrada
	int maxWidth, maxHeight, exponent, factor;
	char *text = readFile(&maxWidth, &maxHeight, &exponent, &factor, inputFileName);
	int size = strlen(text);
	// Trata casos onde o a entrada vier com \n e \r
	if (text[size-1] == '\n') {
		text[size-1] = '\0';
	}
	if (text[size-2] == '\r') {
		text[size-2] = '\0';
	}

	int *numberWords = (int*) malloc(sizeof(int));
	*numberWords = 0;
	int *offsets = createArrayOffset(text, numberWords);

	// Executa algoritmo especificado
	defineOperation(type, 0, numberWords, maxWidth, maxHeight, text, offsets, exponent, factor, outputFileName);
	free(numberWords);
	free(offsets);
	free(text);
	return 0;
}