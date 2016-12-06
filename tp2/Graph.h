#ifndef Graph_h
#define Graph_h

typedef struct Edge {
	int vertice;
	int weight;
	struct Edge *Prox;
	struct Edge *Ante;
}Edge;

/**
 * @brief		Inicializa o vetor 'd' com INT_MAX e 'pi' com 0. A posicao d[0]
 				eh inicializada com 0.
 *
 * @param[in]	s					Valor da posicao inicial.
 * @param[in]	size				numero de vertices.
 * @param[in]	d					Vetor que armazena o peso do caminho mais curto
 * 									ate aquele indice.
 * @param[in]	pi					Vetor de predecessores.
 */
void initializeSingleSource(int s, int size, int *d, int *pi);

/**
 * @brief		Verifica se o valor de d[v] eh maior que d[u] mais o peso ate v,
 * 				se for d[v] recebe essa soma e pi guarda o predecessor (relaxamento).
 *
 * @param[in]	u					Vertice u.
 * @param[in]	v					Vertice v.
 * @param[in]	weight				Peso da aresta (u,v).
 * @param[in]	d					Vetor que armazena o peso do caminho mais curto
 * 									ate aquele indice.
 * @param[in]	pi					Vetor de predecessores.
 */
void relax(int u, int v, int weight, int *d, int *pi);

/**
 * @brief		Imprime o caminho mais curto.
 *
 * @param[in]	s					Inicio.
 * @param[in]	v					Final.
 * @param[in]	pi					Vetor de predecessores.
 */
void printPath(int s, int v, int *pi);

/**
 * @brief		Calcula os menores caminhos entre os vertices dado uma posicao inicial.
 *
 * @param[in]	adjacencyList		Grafo.
 * @param[in]	s					Posicao inicial no grafo.
 * @param[in]	size				Numero de vertices.
 * @param[in]	indexArrayEnd		Posicao final do caminho a ser verificado.
 */
void dijkstra(Edge *adjacencyList, int s, int size, int indexArrayEnd);

/**
 * @brief		Inicializa os vertices do grafo.
 *
 * @param[in]	adjacencyList		Grafo.
 * @param[in]	size				Numero de vertices.
 */
void initGraph(Edge *adjacencyList, int size);

/**
 * @brief		Imprime todo o grafo, mostrando todas as arestas.
 *
 * @param[in]	adjacencyList		Grafo.
 * @param[in]	size				Numero de vertices.
 */
void printGraph(Edge *adjacencyList, int size);

/**
 * @brief		Insere uma aresta no grafo.
 *
 * @param[in]	adjacencyList		Grafo.
 * @param[in]	a					Vertice a.
 * @param[in]	b					Vertice b.
 * @param[in]	weight				Peso para se descolar de um vertice ate o outro.
 */
void insertEdge(Edge *adjacencyList, int a, int b, int weight);

/**
 * @brief		Prepara a insercao da aresta sem restricao de movimento.
 *
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	adjacencyList		Grafo.
 */
void insertNoRestriction(int i, int j, int width, int height, int **map, Edge *adjacencyList);

/**
 * @brief		Calcula peso na direcao direita->baixo e baixo->direita.
 *
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 * @param[in]	path				Define por qual eixo comeca a movimentacao para calcular o peso.
 */
int calculateWeightRightDown(int **map, int i, int j, int width, int height, int restrictionX,
							int restrictionY, int path);

/**
 * @brief		Calcula peso na direcao esquerda->baixo e baixo->esquerda.
 *
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 * @param[in]	path				Define por qual eixo comeca a movimentacao para calcular o peso.
 */
int calculateWeightLeftDown(int **map, int i, int j, int width, int height, int restrictionX,
							int restrictionY, int path);

/**
 * @brief		Calcula peso na direcao direita->cima e cima->direita.
 *
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 * @param[in]	path				Define por qual eixo comeca a movimentacao para calcular o peso.
 */
int calculateWeightRightUp(int **map, int i, int j, int width, int height, int restrictionX,
							int restrictionY, int path);

/**
 * @brief		Calcula peso na direcao esquerda->cima e cima->esquerda.
 *
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 * @param[in]	path				Define por qual eixo comeca a movimentacao para calcular o peso.
 */
int calculateWeightLeftUp(int **map, int i, int j, int width, int height, int restrictionX,
							int restrictionY, int path);

/**
 * @brief		Prepara a insercao da aresta com restricao de movimento.
 *
 * @param[in]	i					Indice que representa a linha no mapa.
 * @param[in]	j					Indice que representa a coluna no mapa.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	adjacencyList		Grafo.
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 */
void insertWithRestriction(int i, int j, int width, int height, int **map, Edge *adjacencyList,
							int restrictionX, int restrictionY);

/**
 * @brief		Insere todas as arestas existentes em cada coordenada do mapa considerando
 				as restricoes de movimento, obstaculo e atalho.
 *
 * @param[in]	restrictionX		Numero maximo de movimentacoes pelo eixo X.
 * @param[in]	restrictionY		Numero maximo de movimentacoes pelo eixo Y.
 * @param[in]	width				Numero de colunas no mapa.
 * @param[in]	height				Numero de linhas no mapa.
 * @param[in]	map					Mapa com os custos de acesso de cada coordenada.
 * @param[in]	adjacencyList		Grafo.
 */
void insertAllEdges(int restrictionX, int restrictionY, int width, int height, int **map, Edge *adjacencyList);

#endif