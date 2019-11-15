#include "structs.h"
#include "funcoes.h"
#include "primitivas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Recebe a imagem e os comandos vindo do arquivo, chamando a 
função correspondente com a imagem a ser editada */
void interpretar(comando *entrada, imagem *img) {

    if(strcmp(entrada->nome_comando, "save") == 0){

        save(img, entrada->comando_string);
    }

    else if(strcmp(entrada->nome_comando, "image") == 0){

        image(img, entrada->parametros);   
    }

    else if(strcmp(entrada->nome_comando, "color") == 0){

        color(img, entrada->parametros);
    }

    else if(strcmp(entrada->nome_comando, "clear") == 0){

        clear(img, entrada->parametros);
    }

    else if(strcmp(entrada->nome_comando, "line") == 0){

        line(img, entrada->parametros);
    }

    else if(strcmp(entrada->nome_comando, "open") == 0){

        open(img, entrada->comando_string);
    }

    else if(strcmp(entrada->nome_comando, "polygon") == 0){

        polygon(img, *entrada);
    }

    else if(strcmp(entrada->nome_comando, "rect") == 0){

        rect(img, entrada->parametros);
    }

    else if(strcmp(entrada->nome_comando, "circle") == 0){

        circle(img, entrada->parametros);
    }

}

/* Lê o arquivo de comandos, criando uma struct de comando que é passado 
para a função que interpreta juntamente com uma instância da imagem*/
void executar(char nome_arquivo[]){

    imagem img = alocar_matriz();

    strcpy(img.nome_imagem, "imagem.ppm");

    FILE *file;
    file = fopen(nome_arquivo, "r");

    char text[50]; 
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

            strcpy(nome_comando, entradas[0]);

            comando instrucao;
            strcpy(instrucao.nome_comando, nome_comando);

            if(strcmp(nome_comando, "open") == 0 || strcmp(nome_comando, "save") == 0 ){

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
            
            interpretar(&instrucao, &img);

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

        desalocar_matriz(&img);
    }
}