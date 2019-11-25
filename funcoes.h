/*! \file */ 

#ifndef funcoes_h 
#define funcoes_h

//! Reparte uma string.
/*!
	Recebe uma string e quebra ela em um vetor de strings de acordo com uma string usada como separadora.
	\param string_entrada recebe a string a ser repartida.
	\param delim recebe a string utilizada para quebrar a string em substrings.
	\param retorno recebe um vetor de string que é usado para colocar a substrings geradas
*/
void split(char string_entrada[], char delim[], char retorno[][50]);

//! Limpa strings.
/*!
	Retira caracteres especiais e outras "sujeiras" que possam estar na string remanescentes daquela posição da memória
	\param entrada recebe a string a ser limpa
	\param saida recebe uma string para depositar a string após ser limpa
*/
void limpar_string_arquivo(char entrada[], char saida[]);

//! Retira a quebra de linha de uma string.
/*!
	\param entrada recebe a string para ser retirada a quebra de linha.
	\param saida recebe a string para ser colocada a string limpa.
*/
void retira_barraN(char entrada[], char saida[]);

//! Aloca a matriz da imagem
/*!
	Faz a alocação inicial do vetor tridimensional que guarda os pixels referentes a imagem que está sendo editada.
	\return Uma instancia da struct imagem com a matriz tridimensional alocada.
*/
imagem alocar_matriz();

//! Realoca a matriz de pixels com o tamanho necessário.
/*!
	Usa a informação recebida da struct imagem, para pegar a resolução da imagem a ser editada para realocar a matriz com a quantidade
	de bytes de bytes necessária para armazenar todos os pixels da imagem com tal resolução.

	\param img recebe o ponteiro com a imagem a ser realocada.
*/
void realocar_matriz(imagem *img);

//! Desaloca a matriz de pixels.
/*!
	Usa a informação recebida da struct imagem, para pegar a resolução da imagem a ser editada para desalocar todos os bytes que
	foram alocados na matriz de acordo com essa resolução.

	\param img recebe o ponteiro com a imagem a ser desalocada.
*/
void desalocar_matriz(imagem *img);

#endif