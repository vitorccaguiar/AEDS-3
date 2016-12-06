#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"

int lerArquivoDeEntrada(char *arquivoEntrada, char **conteudo) {
	long tamanhoArquivo;
	FILE *arq = fopen(arquivoEntrada, "rb");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
		return 0;
	}else {
		// Verifica o tamanho do arquivo
		fseek(arq, 0, SEEK_END);
		tamanhoArquivo = ftell(arq);
		rewind(arq);
		*conteudo = (char*) malloc((tamanhoArquivo+20)*sizeof(char));
		size_t quantidadeSucesso = fread(*conteudo, 1, tamanhoArquivo+20, arq);
		if (quantidadeSucesso != tamanhoArquivo) {
			printf("Erro ao ler o arquivo\n");
		}
	}
	fclose(arq);
	return tamanhoArquivo;
}

void escreverSaida(char *arquivoSaida, unsigned char *saida, int indiceSaida) {
	int resultado;
	long tamanho = (indiceSaida/8)+1;
	FILE *arq = fopen(arquivoSaida, "wb");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
		return;
	}else {
		resultado = fwrite(saida, sizeof(unsigned char), tamanho, arq);
		if (resultado != tamanho) {
			printf("Erro ao ler o arquivo\n");
		}
	}
	fclose(arq);
}

