#ifndef KMP_h
#define KMP_h


/**
 * @brief     Verifica as redundancias em cada CS
 *
 * @param[in]  SB				janela onde eh procurado as redundancias
 * @param[in]  CS 				padrao a ser procurado no SB
 * @param[in]  n 				tamanho do SB
 * @param[in]  m 				tamanho do CS(padrao)
 * @param[in]  tabelaPrefixos	tabela previamente calculada para usar no KMP
 * @param[in]  indicesMatch		indices onde comecam o match
 * @param[in]  indiceFlags		vetor que identifica se a ocorrencia ja foi CS
 *
 * @return     quantidade de matchs			
 */
int KMP_matcher(char *SB, char *CS, int n, int m, int *tabelaPrefixos, int *indicesMatch, int *indiceFlags);

/**
 * @brief     Calcula a tabela de prefixos
 *
 * @param[in]  CS				padrao a ser avaliado
 * @param[in]  m 				tamanho do padrao
 *
 * @return     tabela de prefixos preenchida			
 */
int* computarPrefixo(char *CS, int m);


#endif
