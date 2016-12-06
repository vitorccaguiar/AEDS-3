#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"
#include "LZ77.h"

int main(int argc, char **argv) {
	// Valida se os argumentos foram passados corretamente
	if (argc != 3) {
		printf("\n\tO numero de argumentos esta errado. O programa deve receber 2 argumentos.\n\n");
		exit(0);
	}
	char *arquivoEntrada = argv[1];
	char *arquivoSaida = argv[2];

	//char *texto = (char*) malloc(32769*sizeof(char));
	//memset(texto, 0, 32769);
	char *texto = "\0";
	long tamanhoTexto = lerArquivoDeEntrada(arquivoEntrada, &texto);

	//printf("Texto: %s\n", texto);
	//printf("Tamanho texto: %d\n", tamanhoTexto);

	comprimirEntrada(texto, tamanhoTexto, arquivoSaida);
}