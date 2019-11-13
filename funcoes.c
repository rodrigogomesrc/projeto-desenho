#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

//Divide uma string em um vetor de strings usando um delimitador
void split(char string_entrada[], char delim[], char retorno[][50]){
 
    int tam_delimitador = 0;
    int indice_str_atual = 0; 
    int indice_retorno = 0; 
 
    while(delim[tam_delimitador] != '\0'){
        tam_delimitador++;
    }
 
    int i = 0;
    while(string_entrada[i] != '\0'){

        if(string_entrada[i] == delim[0]){
 
            int corresponde = 1;
            int loops = 0;
            for (int j = 1; j < tam_delimitador; ++j)
            {
                loops++;
 
                if(string_entrada[i + j] != delim[j] ){
 
                    corresponde = 0;
                    break;
                }
            }

            if(corresponde == 1){
 
                retorno[indice_retorno][indice_str_atual] = '\0';
                i += tam_delimitador -1; 
                indice_retorno++; 
                indice_str_atual = 0; 
 
            } else {
 
                for (int l = i; l <= i + loops; ++l)
                {
                    retorno[indice_retorno][indice_str_atual] = string_entrada[l];
                    indice_str_atual++;
                }
                i += loops;
            }
 
        } else {
 
            retorno[indice_retorno][indice_str_atual] = string_entrada[i];
            indice_str_atual++;
        }
        i++;
    }
    retorno[indice_retorno][indice_str_atual] = '\0'; 
}

int numero(char entrada){

    int i = 0;
    int indice = 0;
    int numeros[] = {'1','2','3','4','5','6','7','8','9','0'};

    for (int i = 0; i < 10; ++i)
    {
       if(entrada == numeros[i]){
            return 1;
       }
    }
    return 0;
}

//Retira os espaços em branco e caracteres que não são alfanuméricos ou em branco
void limpar_string_arquivo(char entrada[], char saida[]){

    int i = 0;
    while(1){

        if(isalpha(entrada[i]) || entrada[i] == '.' || entrada[i] == '_' || numero(entrada[i])){

            saida[i] = entrada[i];

        } else if(entrada[i] == '\0'){

            break;
        }

        i++;
    }
}

//Limpa a matriz que representa a imagem na memória
void desalocar_matriz(imagem img){

    for (int i = 0; i < img.largura; ++i)
    {
        for (int j = 0; j < img.altura; ++j)
        {
            free(img.matriz[i][j]);
                  
        }
    }

    for (int i = 0; i < img.largura; ++i)
    {
        free(img.matriz[i]);
    }

    free(img.matriz);
}

//Cria uma imagem com uma alocação inicial na memória
imagem* alocar_matriz(){

    imagem *img = malloc(sizeof(imagem));

    return img;
}

//Realoca a matriz que representa a imagem na memória de acordo com resolução desejada
void realocar_matriz(imagem *img){

    img->matriz = realloc(img->matriz, sizeof(int**) * img->altura);
  
    for (int i = 0; i < img->altura; ++i)
    {
        img->matriz[i] = realloc(img->matriz[i], sizeof(int*) * img->largura);
    }

    for (int i = 0; i < img->altura; ++i)
    {
        for (int j = 0; j < img->largura; ++j)
        {
            img->matriz[i][j] = realloc(img->matriz[i][j], sizeof(int) * 3); 
        }
    }

    //return img;
}