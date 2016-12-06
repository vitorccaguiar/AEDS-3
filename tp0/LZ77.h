#ifndef LZ77_h
#define LZ77_h

typedef struct {
	int comprimento;
	int offset;
} match;

/**
 * @brief     Faz a compressao dos dados lidos do arquivo
 *
 * @param[in]  entrada     			conteudo do arquivo
 * @param[in]  tamanhoTexto         tamanho do conteudo do arquivo
 * @param[in]  arquivoSaida 		nome do arquivo de saida 
 */
void comprimirEntrada(char *entrada, long tamanhoTexto, char *arquivoSaida);

#endif