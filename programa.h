/*! \file */ 

#ifndef programa_h 
#define programa_h

//! Função Executar, chamada no main.
/*!
	\param nome_arquivo recebe uma string correspondente ao nome do arquivo de instruções.
*/
void executar(char nome_arquivo[]);

//! Função de interpretação dos comandos.
/*!
	Essa função recebe as informações de uma linha de comando representando as primitivas 
	e chama a função da primitiva correspondente com os parâmetros necessários

	\param entrada recebe um ponteiro de uma struct comando com as informações da instrução a ser executada.
	\param ultima_entrada recebe um ponteiro de uma struct comando com a ultima primitiva salva *.
	\param img recebe um ponteiro dde uma struct imagem com a imagem a ser modificada pelas primitivas

	(*) ultima_entrada somente armazena uma primitiva quando corresponde a line ou polygon, 
	para uso das funções repeat_line e repeat_polygon
*/
void interpretar(comando *entrada, comando *ultima_entrada, imagem *img);

#endif