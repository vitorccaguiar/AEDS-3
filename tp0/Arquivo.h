#ifndef Arquivo_h
#define Arquivo_h

/**
 * @brief     Le o arquivo de entrada texto, imagem ou video 
 *
 * @param[in]  arquivoEntrada     nome do arquivo de entrada
 * @param[in]  conteudo			  conteudo do arquivo para ser preechido	
 *
 * @return     tamanho do arquivo
 */
int lerArquivoDeEntrada(char *arquivoEntrada, char **conteudo);

/**
 * @brief     Escreve saida binaria no arquivo 
 *
 * @param[in]  arquivoSaida     nome do arquivo de entrada
 * @param[in]  saida 			vetor binario com a saida
 * @param[in]  indiceSaida 		comprimento do vetor	
 */
void escreverSaida(char *arquivoSaida, unsigned char *saida, int indiceSaida);

#endif