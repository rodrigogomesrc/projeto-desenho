#ifndef funcoes_h 
#define funcoes_h

void split(char string_entrada[], char delim[], char retorno[][50]);

void limpar_string_arquivo(char entrada[], char saida[]);

void desalocar_matriz(imagem img);

imagem alocar_matriz();

imagem realocar_matriz(imagem img);

#endif