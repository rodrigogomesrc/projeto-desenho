#ifndef structs_h 
#define structs_h

typedef struct comando_t
{
    char nome_comando[20];
    int qtd_parametros;
    int parametros[30];
    char comando_string[30];
    
}comando;

typedef struct  imagem_t
{
    int ***matriz;
    int altura;
    int largura;
    int cor_atual[3];
    char nome_imagem[31];
    
}imagem;

#endif