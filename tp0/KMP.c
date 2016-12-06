#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KMP.h"


int KMP_matcher(char *SB, char *CS, int n, int m, int *tabelaPrefixos, int *indicesMatch, int *indicesFlag) {
	int q = -1;
	int i = 0;
	int countMatch = 0;
	for (; i< n; i++) {
		while (q > -1 && CS[q+1] != SB[i]) {
			q = tabelaPrefixos[q];
		}
		if (CS[q+1] == SB[i]) {
			q = q + 1;
		}
		if (q == m-1) {
			// Verifica se o match pode ser feito analisando os CSs existentes
			if(indicesFlag[i-q] == 1){
				indicesMatch[countMatch] = i-q;
				countMatch++;
			}
			q = tabelaPrefixos[q];
		}
	}
	return countMatch;
}

int* computarPrefixo(char *CS, int m) {
	int* tabelaPrefixos = (int*) malloc(3*sizeof(int));
	memset(tabelaPrefixos, 0, 3*sizeof(int));
	tabelaPrefixos[0] = -1;
	int k = -1;
	int q = 1;

	for (; q < m; q++) {
		while (k > -1 && CS[k+1] != CS[q]) {
			k = tabelaPrefixos[k];
		}
		if (CS[k+1] == CS[q]) {
			k = k + 1;
		}
		tabelaPrefixos[q] = k;
	}
	return tabelaPrefixos;
}
