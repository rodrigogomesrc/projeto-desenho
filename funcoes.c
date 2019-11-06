#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

void split(char string_entrada[], char delim[], char retorno[][50]){
 
    int tam_delimitador = 0;
    int indice_str_atual = 0; // indice da string atual
    int indice_retorno = 0; // indice da posição no vetor de strings de retorno
 
    while(delim[tam_delimitador] != '\0'){
        tam_delimitador++;
    }
 
    int i = 0;
    while(string_entrada[i] != '\0'){
 
        // Se encontrar um primeiro caractere igual ao delimitador, compara os próximos com os próximos do delimitador
        if(string_entrada[i] == delim[0]){
 
            int corresponde = 1;
            int loops = 0;
            for (int j = 1; j < tam_delimitador; ++j)
            {
                loops++;
 
                //testa cada caractere da string seguindo com até o último do delimitador
                if(string_entrada[i + j] != delim[j] ){
 
                    corresponde = 0;
                    break;
                }
            }
            //se encontrou uma sequência igual ao delimitador
            if(corresponde == 1){
 
                retorno[indice_retorno][indice_str_atual] = '\0';
                i += tam_delimitador -1; // pula o delimitador
                indice_retorno++; // vai para a próxima string
                indice_str_atual = 0; // para começar a pegar o começo da próxima string
 
            } else {
 
                /*
                Quando no meio do processo de comparar as strings com as do delimitador
                é percebido que não são iguais, joga as que foi comparadas no vetor de retorno
                e pula pra depois delas
                */
                for (int l = i; l <= i + loops; ++l)
                {
                    retorno[indice_retorno][indice_str_atual] = string_entrada[l];
                    indice_str_atual++;
                }
                i += loops;
            }
 
        } else {
 
            // vai colocando a string no vetor de strings até encontrar o delimitador
            retorno[indice_retorno][indice_str_atual] = string_entrada[i];
            indice_str_atual++;
        }
        i++;
    }
    retorno[indice_retorno][indice_str_atual] = '\0'; // fecha a última string

    //printf("%d\n", indice_retorno);
}


void limpar_string_arquivo(char entrada[], char saida[]){

    int i = 0;
    while(1){

        if(isalpha(entrada[i]) || entrada[i] == '.'){

            saida[i] = entrada[i];

        } else if(entrada[i] == '\0'){

            break;
        }

        i++;
    }
}

void desalocar_matriz(imagem img){

    for (int i = 0; i < img.altura; ++i)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            free(img.matriz[i][j]);
                  
        }
    }

    for (int i = 0; i < img.altura; ++i)
    {
        free(img.matriz[i]);
    }

    free(img.matriz);

}

imagem alocar_matriz(){

    imagem img;

    img.matriz = calloc(1, sizeof(int**));
  
    for (int i = 0; i < 1; ++i)
    {
        img.matriz[i] = calloc(1, sizeof(int*));
        
    }

    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            img.matriz[i][j] = calloc(3, sizeof(int));
           
        }
    }

    return img;
}


imagem realocar_matriz(imagem img){

    img.matriz = realloc(img.matriz, sizeof(int**) * img.altura);
  
    for (int i = 0; i < img.altura; ++i)
    {
        img.matriz[i] = realloc(img.matriz[i], sizeof(int*) * img.largura);
    }

    for (int i = 0; i < img.altura; ++i)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            img.matriz[i][j] = realloc(img.matriz[i][j], sizeof(int) * 3); 
        }
    }

    return img;
}