#ifndef Algorithms_h
#define Algorithms_h

/**
 * @brief       Faz operacao de potencia com numero inteiros
 *
 * @param[in]   a                   primeiro numero inteiro.
 * @param[in]   b                   segundo numero inteiro.
 */
int powInt(int a, int b);

/**
 * @brief       Soma dois numeros inteiros com validacao de 
 *              limite do tipo inteiro (INT_MAX)
 *
 * @param[in]   a                   primeiro numero inteiro.
 * @param[in]   b                   segundo numero inteiro.
 */
int sum(int a, int b);

/**
 * @brief       Calcula o menor valor entre 'a' e 'b'. 
 *              Calcula o indice 'minJ' que sera o 'j' do valor minimo. 
 *
 * @param[in]   a                   primeiro numero inteiro.
 * @param[in]   b                   segundo numero inteiro.
 * @param[in]   j                   indice que indica ate qual palavra esta calculando.
 * @param[in]   minJ                indice j do menor valor calculado.
 */
int min(int a, int b, int j, int *minJ);

/**
 * @brief       Faz o algoritmo forca bruta. 
 *
 * @param[in]   i                   primeiro numero inteiro.
 * @param[in]   numberWords         numero de palavras do texto.
 * @param[in]   maxWidth            tamanho maximo de caracteres por linha.
 * @param[in]   maxHeight           tamanho maximo de linhas.
 * @param[in]   text                texto inicial.
 * @param[in]   offsets             vetor de offsets das palavras.
 * @param[in]   exponent            expoente dado como parametro da funcao de custo.
 * @param[in]   factor              fator dado como parametro da funcao de custo.
 * @param[in]   lines               contador de linhas.
 * @param[in]   parent              vetor utilizado para impressao.
 */
int bruteForce(int i, int *numberWords, int maxWidth, int maxHeight,
                char *text, int *offsets, int exponent, int factor, int lines, int *parent);

/**
 * @brief       Calcula o custo de i ate j. 
 *
 * @param[in]   a                   primeiro numero inteiro.
 * @param[in]   b                   segundo numero inteiro.
 * @param[in]   j                   indice que indica ate qual palavra esta calculando.
 * @param[in]   minJ                indice j do menor valor calculado.
 */
int badness(int i, int j, int maxWidth, char *text, int *offsets, int exponent, int factor);

/**
 * @brief       Faz o algoritmo programacao dinamica. 
 *
 * @param[in]   i                   primeiro numero inteiro.
 * @param[in]   numberWords         numero de palavras do texto.
 * @param[in]   maxWidth            tamanho maximo de caracteres por linha.
 * @param[in]   maxHeight           tamanho maximo de linhas.
 * @param[in]   text                texto inicial.
 * @param[in]   offsets             vetor de offsets das palavras.
 * @param[in]   exponent            expoente dado como parametro da funcao de custo.
 * @param[in]   factor              fator dado como parametro da funcao de custo.
 * @param[in]   lines               contador de linhas.
 * @param[in]   parent              vetor utilizado para impressao.
 * @param[in]   memo                matriz que guarda valores que ja foram calculados.
 */
int dynamicProgramming(int i, int *numberWords, int maxWidth, int maxHeight,
                        char *text, int *offsets, int exponent, int factor, int lines, int *parent, int **memo);

/**
 * @brief       Faz o algoritmo guloso. 
 *
 * @param[in]   i                   primeiro numero inteiro.
 * @param[in]   text                texto inicial.
 * @param[in]   numberWords         numero de palavras do texto.
 * @param[in]   maxWidth            tamanho maximo de caracteres por linha.
 * @param[in]   maxHeight           tamanho maximo de linhas.
 * @param[in]   offsets             vetor de offsets das palavras.
 * @param[in]   exponent            expoente dado como parametro da funcao de custo.
 * @param[in]   factor              fator dado como parametro da funcao de custo.
 * @param[in]   count               contador de linhas.
 */
int greedy(int i, char *text, int *numberWords, int maxWidth, int maxHeight,
			int *offsets, int exponent, int factor, int count);

#endif