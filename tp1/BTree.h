#ifndef BTree_h
#define BTree_h

typedef enum {
	Interna, Externa // Tipo da pagina
} TipoIntExt;

typedef struct Registros {
	char **elemento; // [tamanho de campos][30]
} Registros;

typedef struct TipoPagina *TipoApontador;

typedef struct TipoPagina {
	TipoIntExt Pt;
	union {
		struct {
			int ni; // Numero de chaves inseridas
			size_t offset; // posicao no arquivo
			Registros *ri; // tamanho da ordem
			long int *pi; // Vetor de apontadores (offsets) de tamaho ordem+1
		} U0;
		struct {
			int ne; // Numero de elementos inseridos
			size_t offset; // posicao no arquivo
			Registros *re; // tamanho da ordem
		} U1;
	} UU;
} TipoPagina;

/**
 * @brief     Desaloca toda pagina se for interna
 *
 * @param[in]  pagina     			pagina para setar o offset
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore       	ordem da arvore
 */
void desalocarNoInterno(TipoPagina *pagina, int camposRegistro, int ordemArvore);

/**
 * @brief     Desaloca toda pagina se for externa
 *
 * @param[in]  pagina     			pagina para desalocar
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore       	ordem da arvore
 */
void desalocarNoExterno(TipoPagina *pagina, int camposRegistro, int ordemArvore);

/**
 * @brief     Coloca o valor do offset sendo o valor atual do ponteiro do arquivo da arvore
 *
 * @param[in]  pagina     			pagina para setar o offset
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore       	ordem da arvore
 */
void desalocarNo(TipoPagina *pagina, int camposRegistro, int ordemArvore);

/**
 * @brief     Converte um char* para unsigned long long int
 *
 * @param[in]  key     			chave a ser convertida
 */
unsigned long long int converter(char *key);

/**
 * @brief     Coloca o valor do offset sendo o valor atual do ponteiro do arquivo da arvore
 *
 * @param[in]  pagina     			pagina para setar o offset
 * @param[in]  arquivoArvore        arquivo da arvore onde se encontra a pagina
 */
void setOfsset(TipoPagina *pagina, FILE *arquivoArvore);

/**
 * @brief     Recupera o valor do offset de uma pagina
 *
 * @param[in]  pagina     			pagina para obter o offset
 */
long int getOffset(TipoPagina *pagina);

/**
 * @brief     Cria pagina interna
 *
 * @param[in]  camposRegistro     	numero total de campos que um registro tem
 * @param[in]  ordemArvore          numero que representa a ordem da arvore
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
TipoPagina* criarNoInterno(int camposRegistro, int ordemArvore, FILE *arquivoArvore);

/**
 * @brief     Cria pagina externa
 *
 * @param[in]  camposRegistro     	numero total de campos que um registro tem
 * @param[in]  ordemArvore          numero que representa a ordem da arvore
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
TipoPagina* criarNoExterno(int camposRegistro, int ordemArvore, FILE *arquivoArvore);

/**
 * @brief     Cria pagina
 *
 * @param[in]  camposRegistro     	numero total de campos que um registro tem
 * @param[in]  Pt 					Tipo da pagina
 * @param[in]  ordemArvore          numero que representa a ordem da arvore
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
TipoPagina* criarNo(int camposRegistro, int ordemArvore, TipoIntExt Pt, FILE *arquivoArvore);

/**
 * @brief     Retorna numero de registros de uma pagina
 *
 * @param[in]  pagina     			pagina para retornar o numero de registro
 */
int getNumeroRegistro(TipoPagina *pagina);

/**
 * @brief     Incrementa 1 no numero de registros da pagina
 *
 * @param[in]  pagina     			pagina para mudar o numero de registro
 */
void setNumeroRegistro(TipoPagina *pagina);

/**
 * @brief     Muda o numero de registro pra um valor especificado
 *
 * @param[in]  pagina     			pagina para mudar o numero de registro
 * @param[in]  valor        		numero que representa o valor a ser atribuido ao numero de registros
 */
void setNumeroRegistroValor(TipoPagina *pagina, int valor);

/**
 * @brief     Retorna o campo da chave do registro
 *
 * @param[in]  pagina     			pagina que possui o registro
 * @param[in]  campoIndice  		indice do campo que possui a chave
 * @param[in]  i 					indice do registro 
 */
char* getChaveCampoIndice(TipoPagina *pagina, int campoIndice, int i);

/**
 * @brief     Atribui um valor pra chave de um registro
 *
 * @param[in]  pagina     			pagina que possui o registro
 * @param[in]  campoIndice  		indice do campo que possui a chave
 * @param[in]  i 					indice do registro 
 * @param[in]  valor 				numero que representa o valor a ser atribuido ao numero de registros 
 */
void setChaveCampoIndice(TipoPagina *pagina, int campoIndice, int i, char *valor);

/**
 * @brief     Retorna um registro
 *
 * @param[in]  pagina     			pagina que possui o registro
 * @param[in]  indice          		indice do registro
 */
char** getRegistro(TipoPagina *pagina, int indice);

/**
 * @brief     Atribui valores para um registro
 *
 * @param[in]  pagina     			pagina que possui o registro
 * @param[in]  i          			indice do registro
 * @param[in]  registro 			vetor de registros 
 */
void setRegistro(TipoPagina *pagina, int i, char** registro);

/**
 * @brief     Aumenta tamanho fila estatica criada quando chega em seu limite
 *
 * @param[in]  tamanhoAlocado     	tamanho
 * @param[in]  tamanho          	tamanho usado anteriormente pra criacao
 * @param[in]  fila 				fila criada 
 */
TipoPagina* aumentarFila(int tamanhoAlocado, int tamanho, TipoPagina *fila);

/**
 * @brief     Imprime arvore em largura
 *
 * @param[in]  paginaRaiz     		raiz da arvore
 * @param[in]  ordem          		ordem da arvore
 * @param[in]  campoIndice 			indice da chave do registro 
 * @param[in]  camposRegistro 		numero de campos do registro
 * @param[in]  saida 				arquivo da saida do programa 
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
void buscarEmLargura(TipoPagina *paginaRaiz, int ordem, int campoIndice, int camposRegistro,
					 FILE *saida, FILE* arquivoArvore);

/**
 * @brief     pesquisa registro pela chave
 *
 * @param[in]  pagina     			pagina raiz
 * @param[in]  key          		chave a ser buscada
 * @param[in]  campoIndice 			indice da chave do registro 
 * @param[in]  camposRegistro 		numero de campos do registro 
 * @param[in]  ordemArvore 			ordem da arvore 
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
char** pesquisar(TipoPagina *pagina, char *key, int campoIndice, int camposRegistro,
				 int ordemArvore, FILE *arquivoArvore);

/**
 * @brief     Insere registro em pagina nao cheia
 *
 * @param[in]  pagina     			pagina que vai ser inserido o registro
 * @param[in]  reg 					registro a ser inserido
 * @param[in]  campoIndice 			indice da chave do registro 
 * @param[in]  ordemArvore			ordem da arvore 
 * @param[in]  camposRegistro		numero de campos do registro  
 * @param[in]  arquivoArvore		arquivo da arvore 
 */
void inserir(TipoPagina *pagina, Registros *reg, int campoIndice, int ordemArvore,
			 int camposRegistro, FILE* arquivoArvore);

/**
 * @brief     Usado na divisao de uma pagina, coloca os devidos registros na pagina nova interna
 *
 * @param[in]  paginaNova			pagina nova criada que vai ser atribuido os registros da direita
 * @param[in]  ordemArvore			ordem da arvore
 * @param[in]  filho 				pagina que possui todos os registros a serem divididos 
 */
void setRegistrosPaginaInterna(TipoPagina *paginaNova, int ordemArvore, TipoPagina *filho);

/**
 * @brief     Usado na divisao de uma pagina, coloca os devidos registros na pagina nova externa
 *
 * @param[in]  paginaNova			pagina nova criada que vai ser atribuido os registros da direita
 * @param[in]  ordemArvore			ordem da arvore
 * @param[in]  filho 				pagina que possui todos os registros a serem divididos 
 */
void setRegistrosPaginaExterna(TipoPagina *paginaNova, int ordemArvore, TipoPagina *filho);

/**
 * @brief     Divide filho que esta cheio, colocando a parte da direita em uma nova pagina,
 				a da esquerda no parametro 'pagina' e fazendo o elemento do meio subir para
 				o pai
 *
 * @param[in]  pagina				pagina pai
 * @param[in]  indice				indice da divisao
 * @param[in]  filho 				pagina que possui o maximo de registros 
 * @param[in]  ordemArvore 			ordem da arvore 
 * @param[in]  campoIndice 			indice da chave do registro
 * @param[in]  camposRegistro 		numero de campos do registro
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
void dividirFilho(TipoPagina *pagina, int indice, TipoPagina *filho, int ordemArvore,
				 int campoIndice, int camposRegistro, FILE* arquivoArvore);

/**
 * @brief     Verifica se a pagina raiz esta cheia para realizar a divisao.
 				Com essa analise chama a insercao de maneiras diferentes.
 *
 * @param[in]  pagina				pagina raiz
 * @param[in]  reg					registro a ser inserido
 * @param[in]  campoIndice 			indice da chave do registro
 * @param[in]  ordemArvore 			ordem da arvore 
 * @param[in]  camposRegistro 		numero de campos do registro
 * @param[in]  arquivoArvore 		arquivo da arvore 
 */
void inserirNaArvore(TipoPagina **pagina, Registros *reg, int campoIndice, int ordemArvore,
					 int camposRegistro, FILE* arquivoArvore);

#endif