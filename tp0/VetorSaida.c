#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VetorSaida.h"

void adicionarNoByte(unsigned char *saida, unsigned char caracter, unsigned int *indiceSaida) {
	// Se nao tiver espaco pro byte
	if (*indiceSaida % 8 != 0) {
		// Coloca o numero de bits que sobrou de um byte
		saida[(*indiceSaida) / 8] |= caracter >> ((*indiceSaida) % 8);
		// Coloca o resto no outro byte
		saida[((*indiceSaida) / 8) + 1] |= caracter << (8 - ((*indiceSaida) % 8));
	}else {
		// Se o caracter couber, coloca ele no byte
	saida[(*indiceSaida)/ 8] = caracter;
	}
	*indiceSaida += 8;
}

void mudarLiteral(unsigned char *saida, unsigned int *indiceSaida, unsigned char literal) {
	// Aumenta o comprimento do vetor para deixar o 0 representando o literal
	*indiceSaida = *indiceSaida + 1;

	// Adiciona o caracter corretamente no byte
	adicionarNoByte(saida, literal, indiceSaida);
}

void mudarPonteiro(unsigned char *saida, int *indiceSaida, unsigned char comprimento, unsigned short offset) {
	// Subtrai 3 do comprimento pois este eh o valor minimo e sera representado com tudo 0 em binario
	comprimento = comprimento - 3;
	// Subtrai 1 do offset pois este eh o valor minimo e sera representado com tudo 0 em binario
	offset = offset - 1;

	// Coloca o bit 1 na frente representando o ponteiro
	(saida[*indiceSaida/8]) |= (1 << (7 - ((*indiceSaida) % 8)));
	*indiceSaida = *indiceSaida + 1;

	// Coloca os caracteres do ponteiro corretamente no byte
	adicionarNoByte(saida, comprimento, indiceSaida);
	adicionarNoByte(saida, (offset >> 8) << 1, indiceSaida);
	*indiceSaida = *indiceSaida -1; 
	adicionarNoByte(saida, (unsigned char)offset, indiceSaida); 
}

