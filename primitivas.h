/*! \file */ 

#ifndef primitivas_h 
#define primitivas_h

//! Salva a Imagem
/*!
	Copiar os pixels da matriz de pixel para um arquivo .ppm, gerando a imagem.

	\param img recebe o ponteiro com a imagem a salva.
	\param nome_arquivo é passado o nome do arquivo de imagem a ser salvo.
*/
void save(imagem *img, char nome_arquivo[]);

//! Cria uma linha.
/*!
	A função cria uma linha entre duas coordenadas x y dadas.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor com o ponto inicial e final da reta.
*/
void line(imagem *img, int parametros[]);

//! Cria um polígono.
/*!
	A função cria um polígono que passa pelos pontos dados.

	A função recebe na primeira posição do vetor de parâmetros a quantidade de pontos.
	Os outros parâmetros a seguir são cada uma das ordenadas.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor com a quantidade de pontos e as coordenadas deles.
*/
void polygon(imagem *img, comando cmd);

//! Cria um círculo
/*!
	A função cria um círculo recebendo as coordenadas do ponto central e o raio.

	\param img recebe o ponteiro com a imagem a salva.
	\param cmd recebe uma struct comando, de onde é retirado os parâmetros necessários para a execução da matriz.
*/
void circle(imagem *img, int parametros[]);

//! Preenche superfícies.
/*!
	A função preenche figuras ou qualquer superfície da imagem com a cor atual, até encontrar uma borda.

	Para isso a função recebe as coodernadas do ponto onde será pintado.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor, sendo as primeiras posições a coordenadas do ponto central, seguido do raio.
*/
void fill(imagem *img, int parametros[]);

//! Define uma cor
/*!
	A função define uma cor (rgb) a ser usada para as primitivas que se seguem a essa instrução.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo os três valores (rgb) para definir a cor.
*/
void color(imagem *img, int parametros[]);

//! Limpa uma imagem.
/*!
	A função recebe uma cor para preencher todos os pixels da imagem.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo os três valores (rgb) para definir a cor a ser usada no preenchimento.
*/
void clear(imagem *img, int parametros[]);

//! Cria um retângulo.
/*!
	A função cria um retângulo, recebendo o ponto inicial e o tamanho nos eixos x e y.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo a coordenada e os tamanhos x e y.
*/
void rect(imagem *img, int parametros[]);

//! Repete uma linha.
/*!
	A função repete uma linha definido a quantidade de repetições e os incrementos no x e no y.
	Dessa forma, a reta é repetida pela quantidade definida, somando a altura e a largura dos incrementos
	para gerar as novas retas.

	A linha a ser repetida é a última definida.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo a quantidade de repetições e os incrementos.
*/
void repeat_line(imagem *img, int parametros[], comando *ultima_entrada);

//! Repete um polígono.
/*!
	A função repete um polígono definido a quantidade de repetições e os incrementos no x e no y.
	Dessa forma, o polígono é repetido pela quantidade definida, somando a altura e a largura dos incrementos
	em cada um dos pontos, para gerar os novos polígonos.

	O polígono a ser repetído é o último definido.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo a quantidade de repetições e os incrementos.
	\param ultima_entrada recebe um ponteiro referente a uma struct comando que contem a última instrução que contem o polígono
	a ser repetido.
*/
void repeat_polygon(imagem *img, int parametros[], comando *ultima_entrada);

//! Copia um polígono.
/*!
	Define uma nova coordenada e um novo polígono é copiado para essa nova posição, tomando como referência
	seu primeiro ponto.
	
	O polígono a ser copiado é o último definido.

	\param img recebe o ponteiro com a imagem a salva.
	\param parametros recebe um vetor contendo a quantidade de repetições e os incrementos.
	\param ultima_entrada recebe um ponteiro referente a uma struct comando que contem a última instrução que contem o polígono
	a ser repetido.
*/
void copy_polygon(imagem *img, int parametros[], comando *ultima_entrada);

//! Abre uma imagem.
/*!
	A função lê um arquivo de imagem e copia os pixels para uma matrix de pixels, podendo ser editada pelo programa.

	\param img recebe o ponteiro com a imagem para qual a informação vinda do arquivo de imagem será salvada.
	\param nome_arquivo recebe o nome do arquivo de imagem que será aberto.
*/
void open(imagem *img, char nome_arquivo[]);

//! Define a resolução da imagem a ser criada.
/*!
	A função cria uma imagem a se definir a resolução.

	A função recebe no vetor de parâmetro os dois valores referentes a quantidade de pixels no eixo x e y, chamando
	a função de alocação em seguida, reservando a memória necessária para a imagem.

	\param img recebe o ponteiro com a imagem e salva a resolução nela, além de passá-la para fazer a alocação.
	\param parametros recebe um vetor com os valores referentes a resolução da imagem a ser criada.
*/
void image(imagem *img, int parametros[]);

#endif