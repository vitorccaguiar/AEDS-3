#ifndef Serializacao_h
#define Serializacao_h

/**
 * @brief     Faz serializacao do tipo nao primitivo Registro
 *
 * @param[in]  reg     				pagina para setar o offset
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore        	ordem da arvore
 */
void serializarRegistros(Registros *reg, FILE *arquivoArvore, int camposRegistro, int ordemArvore);

/**
 * @brief     Faz serializacao do tipo vetor de long int
 *
 * @param[in]  pi     				vetor de offsets
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  ordemArvore        	orde da arvore
 */
void serializarPonteiros(long int *pi, FILE *arquivoArvore, int ordemArvore);

/**
 * @brief     Serializa a pagina especificada
 *
 * @param[in]  pagina     			pagina que vai ser serializada
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore        	ordem da arvore
 * @param[in]  offset        		posicao no arquivo
 */
void serializarPagina(TipoPagina *pagina, FILE* arquivoArvore, int camposRegistro, int ordemArvore, size_t offset);

/**
 * @brief     Faz deserializacao do tipo nao primitivo Registro
 *
 * @param[in]  reg     				pagina para setar o offset
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore        	ordem da arvore
 */
void deserializarRegistros(Registros *reg, FILE *arquivoArvore, int camposRegistro, int ordemArvore);

/**
 * @brief     Faz deserializacao do tipo vetor de long int
 *
 * @param[in]  pi     				pagina para setar o offset
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  ordemArvore        	ordem da arvore
 */
void deserializarPonteiros(long int *pi, FILE *arquivoArvore, int ordemArvore);

/**
 * @brief     Deserializa a pagina especificada
 *
 * @param[in]  pagina     			pagina a ser deserializada
 * @param[in]  arquivoArvore        arquivo da arvore
 * @param[in]  camposRegistro       numero de campos do registro
 * @param[in]  ordemArvore        	ordem da arvore
 * @param[in]  offset        		posicao no arquivo
 */
void deserializarPagina(TipoPagina *pagina, FILE* arquivoArvore, int camposRegistro, int ordemArvore, size_t offset);

#endif