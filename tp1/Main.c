#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
#include "Serializacao.h"

int main(int argc, char **argv) {

	// Recebendo argumentos
	char *arquivoSaida = argv[1];
	char *arquivoEntrada = argv[2];
	int ordemArvore = atoi(argv[3]);
	int camposRegistro = atoi(argv[4]);
	int campoIndice = atoi(argv[5]);

	char operacao[7];
	char key[30];

	// Abre arquivo para ler entrada
	FILE *arq = fopen(arquivoEntrada, "r");
	if (arq == NULL) {
		printf("Erro ao abrir o arquivo.\n");
	}else {
		// Abre arquivo pra escrever a saida
		FILE *saida = fopen(arquivoSaida, "w");
		if (saida == NULL) {
			printf("Erro ao abrir o arquivo");
			return;
		}
		// Cria arquivo da arvore
		FILE *arquivoArvore = tmpfile();
		// Cria raiz e serializa
		TipoPagina *raiz = criarNo(camposRegistro, ordemArvore, Externa, arquivoArvore);
		serializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U1.offset);


		// Para quando identificar EOF
		while (1) {
			int c = fgetc(arq);
			if (c < 0) {
				fclose(arq);
				fclose(saida);
				fclose(arquivoArvore);
				desalocarNo(raiz, camposRegistro, ordemArvore);
				return;
			}
			int i = 0;
			// Armazena operacao
			while (c != '\t' && c >= 0 && c != '\n') {
				operacao[i] = c;
				c = fgetc(arq);
				i++;
			}
			operacao[i] = '\0';
			// Verifica se a operacao eh de pesquisa
			if (strcmp(operacao, "search") == 0) {
				fprintf(saida,"search\n");
				c = fgetc(arq);
				i = 0;
				// Armazena chave
				while (c != '\n' && c >= 0) {
					key[i] = c;
					c = fgetc(arq);
					i++;
				}
				if (i < 30) {
					key[i] = '\0';
				}
				// Recupera o valor da raiz
				if (raiz->Pt == Interna) {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U0.offset);
				}else {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U1.offset);
				}
				// Faz pesquisa
				char **dados = pesquisar(raiz, key, campoIndice, camposRegistro, ordemArvore, arquivoArvore);
				// Se nao achar a chave printa null
				if (dados == NULL) {
					fprintf(saida,"null\n");
					fprintf(saida,"search\n");
				}else {
					int x = 0;
					// Escreve na saida os registros
					for(; x < camposRegistro; x++) {
						fprintf(saida, "%s", dados[x]);
						if (x < camposRegistro-1) {
							fprintf(saida, "\t");
						}
					}
					fprintf(saida,"\n");
					fprintf(saida,"search\n");
				}
				// Se for final do arquivo
				if (c < 0) {
					fclose(arq);
					fclose(saida);
					fclose(arquivoArvore);
					desalocarNo(raiz, camposRegistro, ordemArvore);
					return;
				}
			}
			// Verifica se a operacao eh de insercao
			if (strcmp(operacao, "add") == 0) {
				// Aloca vetor de registros
				Registros *reg = (Registros*)malloc(sizeof(Registros));
				reg->elemento = (char**)malloc(camposRegistro * sizeof(char*));
				for (i = 0; i < camposRegistro; i++) {
					reg->elemento[i] = (char*)malloc(31*sizeof(char));
					memset(reg->elemento[i], 0, 31);
				}
				c = fgetc(arq);
				i = 0;
				// Armazena vetor de registros
				while (i < camposRegistro) {
					int j = 0;
					while (j < 30 && c != '\t' && c >= 0 && c != '\n') {
						reg->elemento[i][j] = c;
						c = fgetc(arq);
						j++;
					}
					if (c == '\t' || c < 0 || c == '\n') {
						if (j < 30) {
							reg->elemento[i][j] = '\0';
						}
					}
					if (c != '\n' && c >= 0) {
						c = fgetc(arq);
					}
					i++;
				}
				// Recupera a raiz
				if (raiz->Pt == Interna) {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U0.offset);
				}else {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U1.offset);
				}
				// Faz insercao
				inserirNaArvore(&raiz, reg, campoIndice, ordemArvore, camposRegistro, arquivoArvore);
				// Se for final do arquivo
				if (c < 0) {
					fclose(arq);
					fclose(saida);
					fclose(arquivoArvore);
					desalocarNo(raiz, camposRegistro, ordemArvore);
					return;
				}
			}
			// Verifica se a operacao eh de impressao
			if (strcmp(operacao, "dump") == 0) {
				fprintf(saida, "dump\n");
				// Recupera a raiz
				if (raiz->Pt == Interna) {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U0.offset);
				}else {
					deserializarPagina(raiz, arquivoArvore, camposRegistro, ordemArvore, raiz->UU.U1.offset);
				}
				// Faz impressao
				buscarEmLargura(raiz, ordemArvore, campoIndice, camposRegistro, saida, arquivoArvore);
				fprintf(saida, "dump\n");
				// Se for final do arquivo
				if (c < 0) {
					fclose(arq);
					fclose(saida);
					fclose(arquivoArvore);
					desalocarNo(raiz, camposRegistro, ordemArvore);
					return;
				}
			}
		}
		fclose(saida);
		fclose(arquivoArvore);
		desalocarNo(raiz,camposRegistro, ordemArvore);
	}
	fclose(arq); 
	return 0;
}