#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "funcoes.h"

void save(imagem img){

    FILE *file = fopen("imagem.ppm", "wb");
    fprintf(file, "P3\n%d %d\n255\n", img.altura, img.largura);
    
    for (int i = 0; i < img.altura; ++i)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            for (int z = 0; z < 3; ++z)
            {
            
                fprintf(file, "%d ", img.matriz[j][i][z]);
            }
            
        }
    }

    fclose(file); 
}

imagem line(imagem img, int parametros[]) {

    int x0 = parametros[0];
    int x1 = parametros[2];
    int y0 = parametros[1];
    int y1 = parametros[3];
    int err, dy, dx, sx, sy, e2;

    dx = abs(x1 - x0);

    if(x0 < x1){

        sx = 1;

    } else {

        sx = -1;
    }

    dy = abs(y1 - y0) * -1;

    if(y0 < y1){

        sy = 1;

    } else {

        sy = -1;
    }
    
    err = dx+dy;
    while (1){

        img.matriz[x0][y0][0] = img.cor_atual[0];
        img.matriz[x0][y0][1] = img.cor_atual[1];
        img.matriz[x0][y0][2] = img.cor_atual[2];

        if (x0==x1 && y0==y1){
            break;
        }
        e2 = 2*err;
        if (e2 >= dy){

            err += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            err += dx;
            y0 += sy;
        }
    }

    return img;   
}

imagem color(imagem img, int parametros[]){
    
    img.cor_atual[0] = parametros[0];
    img.cor_atual[1] = parametros[1];
    img.cor_atual[2] = parametros[2];
    return img;
}

imagem clear(imagem img, int parametros[]){

    for(int i = 0; i < img.altura; i++)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            img.matriz[i][j][0] = parametros[0];
            img.matriz[i][j][1] = parametros[1];
            img.matriz[i][j][2] = parametros[2];
        } 
    }

    return img; 
}
 
imagem open(imagem img, char nome_arquivo[]){

    char text[10];
    char text_split[3][50];
    char altura[5];
    char largura[5];
    char nome_arquivo_tratado[30];

    for (int i = 0; i < 30; ++i)
    {
        nome_arquivo_tratado[i] = '\0';
    }

    limpar_string_arquivo(nome_arquivo, nome_arquivo_tratado);

    FILE *file;
    file = fopen(nome_arquivo_tratado, "r");

    if(file == NULL){

        puts("Arquivo não encontrado");

    } else {
        
        fgets(text, 10, file);
        fgets(text, 10, file);
        
        split(text, " ", text_split);
        
        strcpy(altura, text_split[0]);
        strcpy(largura, text_split[1]);
        
        imagem img;

        sscanf(altura, "%d", &img.altura);
        sscanf(largura, "%d", &img.largura);

        printf("%d\n", img.altura);
        printf("%d\n", img.largura);
    }

    return img;
}

imagem image(imagem img, int parametros[]) {

    img.altura = parametros[0];
    img.largura = parametros[1];
    img = realocar_matriz(img);

    return img;
}

imagem interpretar(comando entrada, imagem img) {

    if(strcmp(entrada.nome_comando, "save") == 0){

        save(img);
    }

    else if(strcmp(entrada.nome_comando, "image") == 0){

        img = image(img, entrada.parametros);   
    }

    else if(strcmp(entrada.nome_comando, "color") == 0){

        img = color(img, entrada.parametros);
    }

    else if(strcmp(entrada.nome_comando, "clear") == 0){

        img = clear(img, entrada.parametros);
    }

    else if(strcmp(entrada.nome_comando, "line") == 0){

        img = line(img, entrada.parametros);
    }

    else if(strcmp(entrada.nome_comando, "open") == 0){

        img = open(img, entrada.comando_string);
    }

    return img;

}

void input(char nome_arquivo[]){

    imagem img = alocar_matriz();

    FILE *file;
    file = fopen(nome_arquivo, "r");

    // usar alocação dinâmica nesses vetores
    char text[50]; // essa variável tem tamanho fixo
    char entradas[50][50];
    char nome_comando[50];
    int parametros[30];
    int qtd_parametros = 0;

    //limpa os vetores
    for (int i = 0; i < 30; ++i)
    {
        parametros[i] = -1;
    }

    for (int i = 0; i < 49; ++i)
    {   
        text[i] = ' ';
        strcpy(entradas[i], " ");
    }
    text[49] = ' ';
    strcpy(entradas[49], " ");


    if(file == NULL){

        printf("Arquivo não encontrado\n");

    } else {

        while(fgets(text, 50, file) != NULL){

            qtd_parametros = 0;
            split(text, " ", entradas);

            // salvando o comando
            strcpy(nome_comando, entradas[0]);

            comando instrucao;
            strcpy(instrucao.nome_comando, nome_comando);

            if(strcmp(nome_comando, "open") == 0){

                 strcpy(instrucao.comando_string, entradas[1]);
            }

            // separando os comandos
            for (int i = 0; i < 29; ++i)
            {
                //converte a string vindo de entradas para o vetor de inteiros "parametros"
                sscanf(entradas[i + 1], "%d", &parametros[i]);
            }

            for (int i = 0; i < 30; ++i)
            {
                if(parametros[i] == -1){
                    break;
                }

                else{
                    qtd_parametros++;
                }
            }

            instrucao.qtd_parametros = qtd_parametros;

            //talvez substituir criando uma função para copiar um vetor pra outro

            // limpa o vetor de instrução da struct
            for (int i = 0; i < 30; ++i)
            {
               instrucao.parametros[i] = -1;
            }

            //copiar os parâmetros extraídos para o vetor de parâmetros
            for (int i = 0; i < 10; ++i)
            {
               instrucao.parametros[i] = parametros[i];
            }
            
            img = interpretar(instrucao, img);

            //limpa os vetores para guardar novos valores
            for (int i = 0; i < 30; ++i)
            {
                parametros[i] = -1;
            }

            for (int i = 0; i < 49; ++i)
            {   
                text[i] = ' ';
                strcpy(entradas[i], " ");
            }
            text[49] = ' ';
            strcpy(entradas[49], " ");

        }
        
        fclose(file);

        desalocar_matriz(img);
    }
}

int main(int argc, char const *argv[])
{

    input("input.txt");
    return 0;
}