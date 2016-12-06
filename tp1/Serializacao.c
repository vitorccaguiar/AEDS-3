#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

void serializarRegistros(Registros *reg, FILE *arquivoArvore, int camposRegistro, int ordemArvore) {
	int i;
	int j;
	// Serializa o numero maximo de registros possiveis
	for (i = 0; i < ordemArvore; i++) {
		for (j = 0; j < camposRegistro; j++) {
			fwrite(reg[i].elemento[j], sizeof(char), 31, arquivoArvore);
		}
	}
}

void serializarPonteiros(size_t *pi, FILE *arquivoArvore, int ordemArvore) {
	int i;
	// Serializa o maximo de ponteiros possiveis
	for (i = 0; i < ordemArvore+1; i++) {
		fwrite(&(pi[i]), sizeof(size_t), 1, arquivoArvore);
	}
}

void serializarPagina(TipoPagina *pagina, FILE* arquivoArvore, int camposRegistro, int ordemArvore, size_t offset) {
	// Muda ponteiro do arquivo pro offset determinado
	fseek(arquivoArvore, offset, SEEK_SET);
	if (pagina->Pt == Interna) {
		// Serializa variaveis primitivas
		fwrite(&(pagina->Pt), sizeof(int), 1, arquivoArvore);
		fwrite(&(pagina->UU.U0.ni), sizeof(int), 1, arquivoArvore);
		fwrite(&(pagina->UU.U0.offset), sizeof(size_t), 1, arquivoArvore);
		// Serializa vetores
		serializarRegistros(pagina->UU.U0.ri, arquivoArvore, camposRegistro, ordemArvore);
		serializarPonteiros(pagina->UU.U0.pi, arquivoArvore, ordemArvore);
	}else {
		// Serializa variaveis primitivas
		fwrite(&(pagina->Pt), sizeof(int), 1, arquivoArvore);
		fwrite(&(pagina->UU.U1.ne), sizeof(int), 1, arquivoArvore);
		fwrite(&(pagina->UU.U1.offset), sizeof(size_t), 1, arquivoArvore);
		// Serializa vetor
		serializarRegistros(pagina->UU.U1.re, arquivoArvore, camposRegistro, ordemArvore);
	}
	// Muda ponteiro do arquivo para o final
	fseek(arquivoArvore, 0, SEEK_END);
}

void deserializarRegistros(Registros *reg, FILE *arquivoArvore, int camposRegistro, int ordemArvore) {
	int i;
	int j;
	// Deserializa o numero maximo de registros possiveis
	for (i = 0; i < ordemArvore; i++) {
		for (j = 0; j < camposRegistro; j++) {
			fread(reg[i].elemento[j], sizeof(char), 31, arquivoArvore);
		}
	}
}

long int* deserializarPonteiros(size_t *pi, FILE *arquivoArvore, int ordemArvore) {
	int i;
	// Deserializa o maximo de ponteiros possiveis
	for (i = 0; i < ordemArvore+1; i++) {
		fread(&(pi[i]), sizeof(size_t), 1, arquivoArvore);
	}
}

void deserializarPagina(TipoPagina *pagina, FILE* arquivoArvore, int camposRegistro, int ordemArvore, size_t offset) {
	// Muda ponteiro do arquivo pro offset determinado
	fseek(arquivoArvore, offset, SEEK_SET);
	if (pagina->Pt == Interna) {
		// Deserializa variaveis primitivas
		fread(&(pagina->Pt), sizeof(int), 1, arquivoArvore);
		fread(&(pagina->UU.U0.ni), sizeof(int), 1, arquivoArvore);
		fread(&(pagina->UU.U0.offset), sizeof(size_t), 1, arquivoArvore);
		// Deserializa vetores
		deserializarRegistros(pagina->UU.U0.ri, arquivoArvore, camposRegistro, ordemArvore);
		deserializarPonteiros(pagina->UU.U0.pi, arquivoArvore, ordemArvore);
	}else {
		// Deserializa variaveis primitivas
		fread(&(pagina->Pt), sizeof(int), 1, arquivoArvore);
		fread(&(pagina->UU.U1.ne), sizeof(int), 1, arquivoArvore);
		fread(&(pagina->UU.U1.offset), sizeof(size_t), 1, arquivoArvore);
		// Deserializa vetor
		deserializarRegistros(pagina->UU.U1.re, arquivoArvore, camposRegistro, ordemArvore);
	}
	// Muda ponteiro do arquivo para o final
	fseek(arquivoArvore, 0, SEEK_END);
}