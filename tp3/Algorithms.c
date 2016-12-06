#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "Algorithms.h"

int powInt(int a, int b) {
	int i, total = a;
	for (i = 1; i < b; i++) total = total *a;
	return total;
}

int sum(int a, int b) {
    if (a == INT_MAX || b == INT_MAX) return INT_MAX;
    if (b > INT_MAX - a || a > INT_MAX - b) return INT_MAX;
    return a + b;
}

int min(int a, int b, int j, int *minJ) {
	if (a <= b) return a;
	else {
        *minJ = j;
        return b;
    }
}

int bruteForce(int i, int *numberWords, int maxWidth, int maxHeight,
                char *text, int *offsets, int exponent, int factor, int lines, int *parent) {
    int j = i+1;
    // Se o numero de linha ultrapassar o limite
    if (lines > maxHeight) return INT_MAX;
    // Caso base
    if (i >= *numberWords) {
        return factor * (powInt((maxHeight-lines), exponent));
    }
    int minJ = INT_MAX;
    int value = INT_MAX;
    for (; j <= *numberWords; j++) {
        // Calcula o custo da linha de i ate j
        int lineCust = badness(i, j, maxWidth, text, offsets, exponent, factor);
        // Se o custo da linha der INT_MAX nao ha porque continuar pois todos serao INT_MAX pra frente
        if (lineCust == INT_MAX) break;

        value = min(value, sum(bruteForce(j, numberWords, maxWidth, maxHeight, text, offsets, exponent, factor, lines+1, parent),
                            lineCust),
                j, &minJ);
    }
    parent[i] = minJ;
    return value;
}

int badness(int i, int j, int maxWidth, char *text, int *offsets, int exponent, int factor) {
	// Calcula caracteres entre da palavra i ate j
	int value = offsets[j] - offsets[i];
	// Se nao for a ultima palavra
	if (text[j+1] != '\0') value--;
	if (value > maxWidth) return INT_MAX;
	return (factor * (powInt((maxWidth-value), exponent)));
}

int dynamicProgramming(int i, int *numberWords, int maxWidth, int maxHeight,
                        char *text, int *offsets, int exponent, int factor, int lines, int *parent, int **memo) {
	int j = i+1;
    // Se o numero de linha ultrapassar o limite
    if (lines > maxHeight) return INT_MAX;
    // Se o valor ja tiver sido calculado anteriormente
    if (memo[i][lines] != -1) return memo[i][lines];
    // Caso base
	if (i >= *numberWords) {
        return factor * (powInt((maxHeight-lines), exponent));
    }
    int minJ = INT_MAX;
	int value = INT_MAX;
    for (; j <= *numberWords; j++) {
        value = min(value, sum(badness(i, j, maxWidth, text, offsets, exponent, factor),
                    dynamicProgramming(j, numberWords, maxWidth, maxHeight, text, offsets, exponent, factor, lines+1, parent, memo)),
                    j, &minJ);
    }
    parent[i] = minJ;
    memo[i][lines] = value;
	return value;
}

int greedy(int i, char *text, int *numberWords, int maxWidth, int maxHeight,
			int *offsets, int exponent, int factor, int count) {
	// Grava inicio da linha e o numero de palavras
	int startLine = offsets[i];
	int k = *numberWords;
	// Caso base
	if (k == 0) return factor * (powInt((maxHeight-count), exponent));
	int value = 0;
	int first = 1;
	// Equanto tiver palavras pra usar
	while (k > 0) {
		// Primeira palavra a ser verificada
		if (first == 1) {
            // Verifica se pode inserir palavra
			if ((value+offsets[i+1]-offsets[i]-1) <= maxWidth) {
				value += offsets[i+1] - offsets[i]-1;
				k--;
				i++;
				first = 0;
			}
		}else {
            // Verifica se pode inserir palavra
			if ((value+offsets[i+1]-offsets[i]) <= maxWidth) {
				value += offsets[i+1] - offsets[i];
				k--;
				i++;
			}else {
                // Substitui espaco por quebra de linha no texto original
				text[value+startLine] = '\n';
				break;
			}
		}
	}
	// Soma numero de linhas
	count++;
	value = factor * (powInt((maxWidth-value), exponent));
	return value + greedy(i, text, &k, maxWidth, maxHeight, offsets, exponent, factor, count);
}