#ifndef VetorSaida_h
#define VetorSaida_h

/**
 * @brief     Adiciona o byte que repsenta o literal ou o ponteiro no vetor final de saida.
 *
 * @param[in]  saida     			vetor final de saida
 * @param[in]  caracter             caracter que faz parte do literal ou do ponteiro
 * @param[in]  indiceSaida      	valor do comprimento do vetor final de saida 
 */
void adicionarNoByte(unsigned char *saida, unsigned char caracter, unsigned int *indiceSaida);

/**
 * @brief     Adapta o valor do literal pra representacao binaria juntamente com o seu identificador.
 *
 * @param[in]  saida     			vetor final de saida
 * @param[in]  indiceSaida          comprimento do vetor final de saida
 * @param[in]  literal      		literal a ser processado 
 */
void mudarLiteral(unsigned char *saida, unsigned int *indiceSaida, unsigned char literal);

/**
 * @brief     Adapta o valor do ponteiro pra representacao binaria juntamente com o seu identificador.
 *
 * @param[in]  saida     			vetor final de saida
 * @param[in]  indiceSaida          comprimento do vetor final de saida
 * @param[in]  comprimento      	valor do comprimento do ponteiro
 * @param[in]  offset 				valor do offset do ponteiro 
 */
void mudarPonteiro(unsigned char *saida, int *indiceSaida, unsigned char comprimento, unsigned short offset);

#endif