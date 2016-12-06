#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BTree.h"
#include "Serializacao.h"

void setOfsset(TipoPagina *pagina, FILE *arquivoArvore) {
	if (pagina->Pt == Interna) {
		pagina->UU.U0.offset = ftell(arquivoArvore);
	}else {
		pagina->UU.U1.offset = ftell(arquivoArvore);
	}
}

long int getOffset(TipoPagina *pagina) {
	if (pagina->Pt == Interna) {
		return pagina->UU.U0.offset;
	}else {
		return pagina->UU.U1.offset;
	}
}

void desalocarNoInterno(TipoPagina *pagina, int camposRegistro, int ordemArvore) {
	int i;
	int j;
	for(j = 0; j < ordemArvore; j++) {
		for (i = 0; i < camposRegistro; i++) {
			free(pagina->UU.U0.ri[j].elemento[i]);
		}
		free(pagina->UU.U0.ri[j].elemento);
	}
	free(pagina->UU.U0.ri);
	free(pagina->UU.U0.pi);
	free(pagina);
}

void desalocarNoExterno(TipoPagina *pagina, int camposRegistro, int ordemArvore) {
	int i;
	int j;
	for(j = 0; j < ordemArvore; j++) {
		for (i = 0; i < camposRegistro; i++) {
			free(pagina->UU.U1.re[j].elemento[i]);
		}
		free(pagina->UU.U1.re[j].elemento);
	}
	free(pagina->UU.U1.re);
	free(pagina);
}

void desalocarNo(TipoPagina *pagina, int camposRegistro, int ordemArvore) {
	if (pagina->Pt == Interna) {
		desalocarNoInterno(pagina, camposRegistro, ordemArvore);
	}else {
		desalocarNoExterno(pagina, camposRegistro, ordemArvore);
	}
}

TipoPagina* criarNoExterno(int camposRegistro, int ordemArvore, FILE *arquivoArvore) {
	TipoPagina *pagina = (TipoPagina*)malloc(sizeof(TipoPagina));
	pagina->Pt = Externa;
	pagina->UU.U1.ne = 0;
	// Coloca offset na posicao do ponteiro do arquivo atual
	setOfsset(pagina, arquivoArvore);

	// Aloca registros
	Registros *reg = (Registros*)malloc(ordemArvore*sizeof(Registros));
	int i;
	int j;
	for(j = 0; j < ordemArvore; j++) {
		reg[j].elemento = (char**)malloc(camposRegistro * sizeof(char*));
		for (i = 0; i < camposRegistro; i++) {
			reg[j].elemento[i] = (char*)malloc(31*sizeof(char));
			memset(reg[j].elemento[i], 0, 31);
		}
	}
	pagina->UU.U1.re = reg;
	//escrever disco
	return pagina;
}

TipoPagina* criarNoInterno(int camposRegistro, int ordemArvore, FILE *arquivoArvore) {
	TipoPagina *pagina = (TipoPagina*)malloc(sizeof(TipoPagina));
	pagina->Pt = Interna;
	pagina->UU.U0.ni = 0;
	// Coloca offset na posicao do ponteiro do arquivo atual
	setOfsset(pagina, arquivoArvore);
	// Aloca ponteiros de offsets e inicializa
	pagina->UU.U0.pi = (size_t*)malloc((ordemArvore+1)*sizeof(size_t));
	memset(pagina->UU.U0.pi, 0, (ordemArvore+1)*sizeof(size_t));

	// Aloca registros
	Registros *reg = (Registros*)malloc(ordemArvore*sizeof(Registros));
	int i;
	int j;
	for(j = 0; j < ordemArvore; j++) {
		reg[j].elemento = (char**)malloc(camposRegistro * sizeof(char*));
		for (i = 0; i < camposRegistro; i++) {
			reg[j].elemento[i] = (char*)malloc(31*sizeof(char));
			memset(reg[j].elemento[i], 0, 31);
		}
	}
	pagina->UU.U0.ri = reg;
	//escrever disco
	return pagina;
}

TipoPagina* criarNo(int camposRegistro, int ordemArvore, TipoIntExt Pt, FILE *arquivoArvore) {
	if (Pt == Externa) {
		return criarNoExterno(camposRegistro, ordemArvore, arquivoArvore);
	}else {
		return criarNoInterno(camposRegistro, ordemArvore, arquivoArvore);
	}
}

TipoPagina* aumentarFila(int tamanhoAlocado, int tamanho, TipoPagina *fila) {
	TipoPagina *filaMaior = (TipoPagina*)malloc(tamanhoAlocado*sizeof(TipoPagina));
	int k = 0;
	while (k < tamanho) {
		filaMaior[k] = fila[k];
		k++;
	}
	free(fila);
	return filaMaior;
}

void buscarEmLargura(TipoPagina *paginaRaiz, int ordem, int campoIndice, int camposRegistro, 
					FILE *saida, FILE* arquivoArvore) {
	int tamanho = 1;
	int frente = 0;
	int posicaoValida = 1;
	int tamanhoAlocado = ordem;
	TipoPagina *fila = (TipoPagina*)malloc(tamanhoAlocado*sizeof(TipoPagina));
	// Adiciona raiz na fila
	fila[0] = *paginaRaiz;
	// Define raiz pra ser a pagina analisada
	TipoPagina pagina = *paginaRaiz;
	while (tamanho != 0) {
		// Se a pagina for interna
		if (pagina.Pt == Interna) {
			int i = 0;
			// Coloca os filhos na fila
			while (i < (pagina.UU.U0.ni)+1) {
				// Recupera pagina no disco
				TipoPagina *paginaDeserializada = criarNo(camposRegistro, ordem, Interna, arquivoArvore);
				deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordem, pagina.UU.U0.pi[i]);

				fila[posicaoValida] = *paginaDeserializada;
				i++;
				tamanho++;
				posicaoValida++;
				// Aumenta tamanho da fila se chegar no maximo
				if (posicaoValida == tamanhoAlocado) {
					tamanhoAlocado = 2 * posicaoValida;
					fila = aumentarFila(tamanhoAlocado, posicaoValida, fila);
				}
			}
			// Tira da fila o pai
			TipoPagina paginaImprimir = fila[frente];
			frente++;
			tamanho--;
			int j = 0;
			// Se o pai for interno
			if (paginaImprimir.Pt == Interna) {
				while (j < paginaImprimir.UU.U0.ni) {
					// Escreve na saida
					fprintf(saida, "%s,", paginaImprimir.UU.U0.ri[j].elemento[campoIndice]);
					j++;
				}
				fprintf(saida, "\n");
			}else {
				// Se o pai for externo
				while (j < paginaImprimir.UU.U1.ne) {
					// Escreve na saida
					fprintf(saida, "%s,", paginaImprimir.UU.U1.re[j].elemento[campoIndice]);
					j++;
				}
				fprintf(saida, "\n");
			}
			// Define a proxima pagina da fila
			pagina = fila[frente];
		}else {
			int j = 0;
			while (j < pagina.UU.U1.ne) {
				// Escreve na saida
				fprintf(saida, "%s,", pagina.UU.U1.re[j].elemento[campoIndice]);
				j++;
			}
			fprintf(saida, "\n");
			frente++;
			tamanho--;
			if (tamanho != 0) {
				// Define a proxima pagina da fila
				pagina = fila[frente];
			}
		}
	}
	free(fila);
}

unsigned long long int converter(char *key){
	unsigned long long int k = 0;
	int j;
	int tamanho = strlen(key);
	int valorCasaDecimal = tamanho;
	for (j = 0; j < tamanho; j++) {
		int num = key[j] - '0';
		k += num * pow(10.0, valorCasaDecimal-1);
		valorCasaDecimal--;
	}
	return k;
}

char** pesquisar(TipoPagina *pagina, char *key, int campoIndice, int camposRegistro, 
				int ordemArvore, FILE *arquivoArvore) {
	int i = 1;
	// Converte chave
	unsigned long long int k = converter(key);

	if (pagina->Pt == Interna) {
		// Incrementa o i ate sabe o indice correto pra analisar
		while (i <= pagina->UU.U0.ni && k >= converter(pagina->UU.U0.ri[i-1].elemento[campoIndice])) i++;
		TipoPagina *paginaDeserializada = criarNo(camposRegistro, ordemArvore, Interna, arquivoArvore);
		// Se pagina nao tiver registro
		if (i == 1) {
			// Se for menor que o ultimo registro comparado
			if (k < converter(pagina->UU.U0.ri[i-1].elemento[campoIndice])) {
				deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i-1]);
				// Busca na subarvore da esquerda
				return pesquisar(paginaDeserializada, key, campoIndice, camposRegistro, ordemArvore, arquivoArvore);
			}else {
				deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i]);
				// Busca na subarvore da direita
				return pesquisar(paginaDeserializada, key, campoIndice, camposRegistro, ordemArvore, arquivoArvore);
			}
		}else {
			// Se for menor que o ultimo registro comparado
			if (k < converter(pagina->UU.U0.ri[i-2].elemento[campoIndice])) {
				deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i-2]);
				// Busca na subarvore da esquerda
				return pesquisar(paginaDeserializada, key, campoIndice, camposRegistro, ordemArvore, arquivoArvore);
			}else {
				deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i-1]);
				// Busca na subarvore da direita
				return pesquisar(paginaDeserializada, key, campoIndice, camposRegistro, ordemArvore, arquivoArvore);
			}
		}
	}
	i = 1;
	// Incrementa o i ate sabe o indice correto pra analisar
	while (i <= pagina->UU.U1.ne && k > converter(pagina->UU.U1.re[i-1].elemento[campoIndice])) i++;
	// Se nao achar o registro e o i crescer alem do permitido
	if (i == pagina->UU.U1.ne+1 && i != 1) {
		i = i - 1;
	}
	// Se a chave for igual a do elemento analisado
	if (k == converter(pagina->UU.U1.re[i-1].elemento[campoIndice])) {
		return pagina->UU.U1.re[i-1].elemento;
	}else {
		return NULL;
	}
}

int getNumeroRegistro(TipoPagina *pagina) {
	if (pagina->Pt == Interna) {
		return pagina->UU.U0.ni;
	}else {
		return pagina->UU.U1.ne;
	}
}

void setNumeroRegistro(TipoPagina *pagina) {
	if (pagina->Pt == Interna) {
		pagina->UU.U0.ni++;
	}else {
		pagina->UU.U1.ne++;
	}
}

void setNumeroRegistroValor(TipoPagina *pagina, int valor) {
	if (pagina->Pt == Interna) {
		pagina->UU.U0.ni = valor;
	}else {
		pagina->UU.U1.ne = valor;
	}
}

char* getChaveCampoIndice(TipoPagina *pagina, int campoIndice, int i) {
	if (pagina->Pt == Interna) {
		return pagina->UU.U0.ri[i].elemento[campoIndice];
	}else {
		return pagina->UU.U1.re[i].elemento[campoIndice];
	}
}

void setChaveCampoIndice(TipoPagina *pagina, int campoIndice, int i, char *valor) {
	if (pagina->Pt == Interna) {
		pagina->UU.U0.ri[i].elemento[campoIndice] = valor;
	}else {
		pagina->UU.U1.re[i].elemento[campoIndice] = valor;
	}
}

char** getRegistro(TipoPagina *pagina, int indice) {
	if (pagina->Pt == Interna) {
		return pagina->UU.U0.ri[indice].elemento;
	}else {
		return pagina->UU.U1.re[indice].elemento;
	}
}

void setRegistro(TipoPagina *pagina, int i, char** registro) {
	pagina->UU.U1.re[i].elemento = registro;
}

void inserir(TipoPagina *pagina, Registros *reg, int campoIndice, int ordemArvore, int camposRegistro, 
			FILE* arquivoArvore) {
	int i = getNumeroRegistro(pagina) - 1;
	if (pagina->Pt == Externa) {
		while (i >= 0 && converter(reg->elemento[campoIndice]) < converter(getChaveCampoIndice(pagina, campoIndice, i))) {
			// Empurra os outros elementos pra abrir espaco pro novo
			setRegistro(pagina, i+1, getRegistro(pagina, i));
			i = i - 1;
		}
		// Adiciona o novo registro
		setRegistro(pagina, i+1, reg->elemento);
		// Atualiza o numero de registros
		setNumeroRegistro(pagina);
		serializarPagina(pagina, arquivoArvore, camposRegistro, ordemArvore, getOffset(pagina));
	}else {
		while (i >= 0 && converter(reg->elemento[campoIndice]) < converter(getChaveCampoIndice(pagina, campoIndice, i))) {
			i = i - 1;
		}
		TipoPagina *paginaDeserializada = criarNo(camposRegistro, ordemArvore, Interna, arquivoArvore);
		deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i+1]);
		// Se a pagina a ser inseria estiver com o limite de registros
		if (getNumeroRegistro(paginaDeserializada) == ordemArvore) {
			dividirFilho(pagina, i+1, paginaDeserializada, ordemArvore, campoIndice, camposRegistro, arquivoArvore);
			// Verifica qual particao da divisao deve-se inserir
			if (converter(reg->elemento[campoIndice]) > converter(getChaveCampoIndice(pagina, campoIndice, i+1))) {
				i = i + 1;
			}
		}
		deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[i+1]);
		inserir(paginaDeserializada, reg, campoIndice, ordemArvore, camposRegistro, arquivoArvore);
	}
}

void setRegistrosPaginaInterna(TipoPagina *paginaNova, int ordemArvore, TipoPagina *filho) {
	int j;
	// Se a ordem for impar
	if (ordemArvore%2 != 0) {
		// Insere registros na pagina nova
		for (j = 0; j < ordemArvore/2; j++) {
			int numIteracoes = (ordemArvore/2)+1;
			setRegistro(paginaNova, j, getRegistro(filho, j+ordemArvore-numIteracoes));
			setNumeroRegistro(paginaNova);
		}
	}else {
		// Insere registros na pagina nova
		for (j = 0; j < (ordemArvore/2)-1; j++) {
			int numIteracoes = (ordemArvore/2)-1;
			setRegistro(paginaNova, j, getRegistro(filho, j+ordemArvore-numIteracoes));
			setNumeroRegistro(paginaNova);
		}
	}
}

void setRegistrosPaginaExterna(TipoPagina *paginaNova, int ordemArvore, TipoPagina *filho) {
	int j;
	// Se a ordem for impar
	if (ordemArvore%2 != 0) {
		// Insere registros na pagina nova
		for (j = 0; j <= ordemArvore/2; j++) {
			int numIteracoes = (ordemArvore/2)+1;
			setRegistro(paginaNova, j, getRegistro(filho, j+ordemArvore-numIteracoes));
			setNumeroRegistro(paginaNova);
		}
	}else {
		// Insere registros na pagina nova
		for (j = 0; j < ordemArvore/2; j++) {
			int numIteracoes = ordemArvore/2;
			setRegistro(paginaNova, j, getRegistro(filho, j+ordemArvore-numIteracoes));
			setNumeroRegistro(paginaNova);
		}
	}	
}

void dividirFilho(TipoPagina *pagina, int indice, TipoPagina *filho, int ordemArvore, int campoIndice,
					int camposRegistro, FILE* arquivoArvore) {
	TipoPagina *paginaNova = criarNo(camposRegistro, ordemArvore, filho->Pt, arquivoArvore);

	int j;
	// Insere os maiores registros da particao
	if (paginaNova->Pt == Interna) {
		setRegistrosPaginaInterna(paginaNova, ordemArvore, filho);
	}else {
		setRegistrosPaginaExterna(paginaNova, ordemArvore, filho);
	}
	// Insere os ponteiros dos maiores registros da particao
	if (filho->Pt == Interna) {
		// Se a ordem for impar
		if (ordemArvore % 2 == 1) {
			int numIteracoes = (ordemArvore/2)+2;
			for (j = 0; j <= (ordemArvore/2)+1; j++) {
				paginaNova->UU.U0.pi[j] = filho->UU.U0.pi[j+ordemArvore-numIteracoes+1];
			}
		} else {
			int numIteracoes = (ordemArvore/2);
			for (j = 0; j < (ordemArvore/2); j++) {
				paginaNova->UU.U0.pi[j] = filho->UU.U0.pi[j+ordemArvore-numIteracoes+1];
			}
		}
	}
	// Atualiza o numero de registros de filho
	setNumeroRegistroValor(filho, ordemArvore/2);
	// Arreda os ponteiros da raiz se necessario
	for (j = getNumeroRegistro(pagina)+1; j > indice+1; j--) {
		pagina->UU.U0.pi[j] = pagina->UU.U0.pi[j-1];
	}
	// Faz a nova raiz apontar pra nova pagina
	pagina->UU.U0.pi[indice+1] = ftell(arquivoArvore);
	// Arreda os registros da raiz se necessario
	for (j = getNumeroRegistro(pagina); j >= indice+1; j--) {
		pagina->UU.U0.ri[j].elemento[campoIndice] = getChaveCampoIndice(pagina, campoIndice, j-1);
	}
	// Sobe o elemento do meio para o pai
	pagina->UU.U0.ri[indice].elemento[campoIndice] = filho->UU.U0.ri[ordemArvore/2].elemento[campoIndice];
	setNumeroRegistroValor(pagina, getNumeroRegistro(pagina)+1);
	// Serializa as paginas envolvidas no processo
	if (filho->Pt == Interna) {
		serializarPagina(filho, arquivoArvore, camposRegistro, ordemArvore, filho->UU.U0.offset);
	}else {
		serializarPagina(filho, arquivoArvore, camposRegistro, ordemArvore, filho->UU.U1.offset);
	}
	serializarPagina(paginaNova, arquivoArvore, camposRegistro, ordemArvore, ftell(arquivoArvore));
	serializarPagina(pagina, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.offset);
	TipoPagina *paginaDeserializada = criarNo(camposRegistro, ordemArvore, Interna, arquivoArvore);
	deserializarPagina(paginaDeserializada, arquivoArvore, camposRegistro, ordemArvore, pagina->UU.U0.pi[0]);
}

void inserirNaArvore(TipoPagina **pagina, Registros *reg, int campoIndice, int ordemArvore, 
					int camposRegistro, FILE* arquivoArvore) {
	// Guarda informacao da raiz
	TipoPagina *r = *pagina;
	// Se a raiz estiver com o maximo de registros permitidos
	if (getNumeroRegistro(*pagina) == ordemArvore) {
		// Cria nova pagina
		TipoPagina *paginaNova = criarNo(camposRegistro, ordemArvore, Interna, arquivoArvore);
		// Define nova pagina sendo a nova raiz
		*pagina = paginaNova;
		if (r->Pt == Interna) {
			(*pagina)->UU.U0.pi[0] = r->UU.U0.offset;
		}else {
			(*pagina)->UU.U0.pi[0] = r->UU.U1.offset;
		}
		serializarPagina(*pagina, arquivoArvore, camposRegistro, ordemArvore, paginaNova->UU.U0.offset);
		// Divide raiz antiga
		dividirFilho(*pagina, 0, r, ordemArvore, campoIndice, camposRegistro, arquivoArvore);
		inserir(*pagina, reg, campoIndice, ordemArvore, camposRegistro, arquivoArvore);
	}else {
		inserir(r, reg, campoIndice, ordemArvore, camposRegistro, arquivoArvore);
	}
}