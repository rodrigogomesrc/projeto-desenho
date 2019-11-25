#ifndef structs_h 
#define structs_h

//! Struct de comando.
/*! Recebe as instruções de cada linha do arquivo de input.*/
typedef struct comando_t
{
    char nome_comando[20]; /*!< Nome da primitiva. */  
    int qtd_parametros; /*!< Quantidade de parâmetros passados na primitiva. */  
    int parametros[30]; /*!< Parâmetros da primitiva. */  
    char comando_string[30]; /*!< Parêmetros em String da primitiva*/  
    
}comando;

//! Struct da Imagem.
/*! Armazena os pixels da imagem, além de dados relacionados a ela
tais como as dimensões, nome e a cor usada na primitiva atual.*/
typedef struct  imagem_t
{
    int ***matriz; /*!< Vetor tridimensional de pixels. */  
    int altura; /*!< Altura da imagem. */  
    int largura; /*!< Largura da imagem. */  
    int cor_atual[3]; /*!< Cor atual para uso nas primitivas. */  
    char nome_imagem[31]; /*!< Nome do arquivo de imagem. */  
    
}imagem;

#endif