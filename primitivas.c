#include "structs.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Salva a imagem no arquivo de acordo com a matriz de pixels
//Algoritmo adaptado de https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
void save(imagem *img, char nome_arquivo[]){

    FILE *file = fopen(nome_arquivo, "wb");
    fprintf(file, "P3\n%d %d\n255\n", img->largura, img->altura);
    
    for (int i = 0; i < img->altura; ++i)
    {
        for (int j = 0; j < img->largura; ++j)
        {
            for (int z = 0; z < 3; ++z)
            {   
                fprintf(file, "%d ", img->matriz[i][j][z]);
            }
            
        }
    }

    fclose(file); 
}

//Função para criar uma reta na imagem
//Algoritmo adptado de https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#All_cases
void line(imagem *img, int parametros[]) {

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

        img->matriz[y0][x0][0] = img->cor_atual[0];
        img->matriz[y0][x0][1] = img->cor_atual[1];
        img->matriz[y0][x0][2] = img->cor_atual[2];

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
}

//Função para criar uma reta na imagem
void polygon(imagem *img, comando cmd){

    int qtd_pontos = cmd.parametros[0];
    int ordenadas = cmd.qtd_parametros -1;
    int parametros[4];

    int retas[ordenadas][4];
    int indice_retas = 0;

    //cria as retas
    for (int i = 0; i < ordenadas; i += 2)
    {
        if(i == ordenadas - 2) {

            retas[indice_retas][0] = cmd.parametros[i + 1];
            retas[indice_retas][1] = cmd.parametros[i + 2];
            retas[indice_retas][2] = cmd.parametros[1];
            retas[indice_retas][3] = cmd.parametros[2];

            indice_retas++;
                
        } else {

            retas[indice_retas][0] = cmd.parametros[i + 1];
            retas[indice_retas][1] = cmd.parametros[i + 2];
            retas[indice_retas][2] = cmd.parametros[i + 3];
            retas[indice_retas][3] = cmd.parametros[i + 4];

            indice_retas++;
        }
    }

    //coloca as retas na imagem.
    for (int i = 0; i < indice_retas; ++i)
    {
        parametros[0] = retas[i][0];
        parametros[1] = retas[i][1];
        parametros[2] = retas[i][2];
        parametros[3] = retas[i][3];
        line(img, parametros);
    }
}

//Define a cor atual
void color(imagem *img, int parametros[]){
    
    img->cor_atual[0] = parametros[0];
    img->cor_atual[1] = parametros[1];
    img->cor_atual[2] = parametros[2];

}

//Limpa a imagem deixando todos os pixels com a cor recebida por parâmetro
void clear(imagem *img, int parametros[]){

    for(int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; ++j)
        {   

            img->matriz[i][j][0] = parametros[0];
            img->matriz[i][j][1] = parametros[1];
            img->matriz[i][j][2] = parametros[2];
        }
    }

}

//Cria retângulos
void rect(imagem *img, int parametros[]){

    comando cmd;

    cmd.qtd_parametros = 9;

    cmd.parametros[0] = 4;
    cmd.parametros[1] = parametros[0];
    cmd.parametros[2] = parametros[1];
    cmd.parametros[3] = parametros[0] + parametros[2];
    cmd.parametros[4] = parametros[1];
    cmd.parametros[5] = parametros[0] + parametros[2];
    cmd.parametros[6] = parametros[1] + parametros[3];
    cmd.parametros[7] = parametros[0];
    cmd.parametros[8] = parametros[1] + parametros[3];

    polygon(img, cmd);

}
 
//Abre um arquivo de imagem ppm para edição
void open(imagem *img, char nome_arquivo[]){

    char text[15];
    char text_split[3][50];
    char altura[5];
    char largura[5];
    char nome_arquivo_tratado[30];
    int qtd_cores;

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
        
        strcpy(altura, text_split[1]);
        strcpy(largura, text_split[0]);
        
        strcpy(img->nome_imagem, nome_arquivo_tratado);

        sscanf(altura, "%d", &img->altura);
        sscanf(largura, "%d", &img->largura);

        realocar_matriz(img);

        printf(">>>Altura: %d\n", img->altura);
        printf(">>>Largura: %d\n", img->largura);

        qtd_cores = img->altura * img->largura * 3;

        char cores[(qtd_cores + 1) * 12];
        char vetor_cores[qtd_cores][50];

        fgets(text, 15, file);
        fgets(cores, qtd_cores * 4 , file);

        split(cores, " ", vetor_cores);

        int indice = 0;
        for (int i = 0; i < img->altura; ++i)
        {
            for (int j = 0; j < img->largura; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {   
                    sscanf(vetor_cores[indice], "%d", &img->matriz[i][j][k]);
                    indice++;
                }
            }
        }
    }

}

//Define a resolução da imagem
void image(imagem *img, int parametros[]) {

    img->altura = parametros[1];
    img->largura = parametros[0];
    //printf("Largura: %d\n", img->largura);
    //printf("Altura: %d\n", img->altura);
    realocar_matriz(img);
}
