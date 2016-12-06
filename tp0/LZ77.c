#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KMP.h"
#include "LZ77.h"
#include "Arquivo.h"
#include "VetorSaida.h"

void comprimirEntrada(char *entrada, long tamanhoTexto, char *arquivoSaida) {
	int *tabelaPrefixos; 
	char *LAB = entrada;
	int comprimento;
	// Cria e inicializa o vetor Search Buffer
	char *SB = (char*) malloc((tamanhoTexto+20)*sizeof(char));
	memset(SB, 0, (tamanhoTexto+20)*sizeof(char));
	// Cria e inicializa o vetor Current Substring
	unsigned char *CS = (unsigned char*) malloc(3*sizeof(unsigned char));
	memset(CS, 0, 3*sizeof(unsigned char));
	// Cria vetor e indice da saida final
	long tamanhoSaida = (tamanhoTexto*9)/8+1;
	unsigned char *saida = (unsigned char*) malloc(tamanhoSaida*sizeof(unsigned char));
	memset(saida, 0, tamanhoSaida);

	// Cria e inicializa vetor de flags para diferenciar os matchs entre si e dos literais
	int *indiceFlags = (int*)malloc((sizeof(int)*tamanhoTexto)+16);
	memset(indiceFlags, 0, (tamanhoTexto*sizeof(int))+16);

	// Inicializa o Search Buffer
	SB[0] = LAB[0];
	SB[1] = LAB[1];
	SB[2] = LAB[2];
	SB[3] = LAB[3];
	SB[4] = LAB[4];

	// Inicializa o Current Substring
	CS[0] = LAB[3];
	CS[1] = LAB[4];
	CS[2] = LAB[5];
	indiceFlags[0] = 1;
	indiceFlags[1] = 1;
	indiceFlags[2] = 1;

	unsigned int *indiceSaida = (unsigned int*) malloc(sizeof(unsigned int));
	*indiceSaida = 0;
	// Inicializa o vetor de saida
	mudarLiteral(saida, indiceSaida, SB[0]);
	mudarLiteral(saida, indiceSaida, SB[1]);
	mudarLiteral(saida, indiceSaida, SB[2]);

	int tamanhoSB = 5;
	int *indicesMatch = (int*) malloc(tamanhoTexto*sizeof(int));
	memset(indicesMatch, 0, tamanhoTexto*sizeof(int));
	int countMatch;
	
	int i = 3;
	int j = 6;
	// Verifica todas as redundancias
	while (i<tamanhoTexto) {
		int desalocarTabela = 0;

		if(i>=tamanhoTexto-2){
			countMatch = 0;
			desalocarTabela = 0;
		}else{
			desalocarTabela = 1;
			tabelaPrefixos = computarPrefixo(CS, 3);
			// Pega o CS e retorna o numero de matchs com ele e seus indices
			countMatch = KMP_matcher(SB, CS, tamanhoSB, 3, tabelaPrefixos, indicesMatch, indiceFlags);
		}

		// Se nao tiver nenhum match
		if (countMatch == 0) {
			// Modifica o literal para ser adicionado no vetor de saida corretamente
			mudarLiteral(saida, indiceSaida, CS[0]);

			// Preeche o SB
			SB[tamanhoSB] = LAB[j-1];
			tamanhoSB++;
			// Muda os valores de i,j e o novo CS
			indiceFlags[i] = 1;
			i++;
			j++;
			CS[0] = LAB[i];
			CS[1] = LAB[i+1];
			CS[2] = LAB[i+2];

		}else {
			// Se tiver match, selecionar o que tiver maior comprimento ou menor offset nessa ordem de prioridade
			match matchEscolhido;
			matchEscolhido.comprimento = 2;
			matchEscolhido.offset = 0;
			int indice = 0;
			for (; indice < countMatch; indice++) {
				int j1, j2;
				comprimento = 3;
				j1 = indicesMatch[indice]+1;
				j2 = i+1;
				// Se tiver comprimento > 3, selecionar o maior comprimento 
				// nao deixar o while crescer indefinidamente. colocar um && para j2-3 < 322525
				while (LAB[j1+2] == LAB[j2+2] && j2+2 < tamanhoTexto) {
					comprimento++;
					j1++;
					j2++;
				}
				if (matchEscolhido.comprimento <= comprimento) {
					matchEscolhido.comprimento = comprimento;
					matchEscolhido.offset = i - indicesMatch[indice];
				}
			}
			// Armazena ponteiro escolhido
			mudarPonteiro(saida, indiceSaida, (unsigned char) matchEscolhido.comprimento, (unsigned short) matchEscolhido.offset);

			indiceFlags[i] = 1;
			// Muda os valores de i,j e o novo CS
			i = i + matchEscolhido.comprimento;
			j = j + matchEscolhido.comprimento;
			CS[0] = LAB[i];
			CS[1] = LAB[i+1];
			CS[2] = LAB[i+2];
		
			// Preeche o SB ate o segundo elemento do proximo CS
			for (; tamanhoSB <= i+1; tamanhoSB++) {
				SB[tamanhoSB] = LAB[tamanhoSB];
			}
			
			// Volta variaveis pro estado original
			comprimento = 3;
			matchEscolhido.comprimento = 2;
			matchEscolhido.offset = 0;	
		}
		if (desalocarTabela == 1) {
			free(tabelaPrefixos);
		}
	}
	// Escrever o vetor de saida binario 
	escreverSaida(arquivoSaida, saida, *indiceSaida);	

	free(indicesMatch);
	free(LAB);
	free(CS);
	free(SB);
	free(saida);
	free(indiceSaida);
	free(indiceFlags);
}
