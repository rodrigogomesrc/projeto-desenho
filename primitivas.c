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

        for (int i = 0; i < 3; ++i)
        {

           img->matriz[y0][x0][i] = img->cor_atual[i];

        }

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

void repeat_line(imagem *img, int parametros[], comando *ultima_entrada){

    if(strcmp(ultima_entrada->nome_comando, "line") == 0){

        int quantidade = parametros[0];
        int deltax0 = parametros[1];
        int deltay0 = parametros[2];
        int deltax1 = parametros[3];
        int deltay1 = parametros[4];
        int novos_parametros[4];

        for (int i = 0; i < quantidade; ++i)
        {   

            novos_parametros[0] = ultima_entrada->parametros[0] + deltax0 * (i + 1);
            novos_parametros[1] = ultima_entrada->parametros[1] + deltay0 * (i + 1);
            novos_parametros[2] = ultima_entrada->parametros[2] + deltax1 * (i + 1);
            novos_parametros[3] = ultima_entrada->parametros[3] + deltay1 * (i + 1);
            line(img, novos_parametros);
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
        for (int j = 0; j < 4; ++j)
        {

            parametros[j] = retas[i][j];  

        }

        line(img, parametros);
    }
}

void copy_polygon(imagem *img, int parametros[], comando *ultima_entrada){

    int distanciax = parametros[0] - ultima_entrada->parametros[1];
    int distanciay = parametros[1] - ultima_entrada->parametros[2];

    int pontos = ultima_entrada->parametros[0];

    int qtd_parametros = pontos * 2 + 1;

    int novos_parametros[qtd_parametros];
    novos_parametros[0] = ultima_entrada->parametros[0];

    comando cmd;
    cmd.qtd_parametros = qtd_parametros;

    for (int i = 0; i < pontos * 2; i += 2)
    {
        novos_parametros[i + 1] = ultima_entrada->parametros[i + 1] + distanciax;
        novos_parametros[i + 2] = ultima_entrada->parametros[i + 2] + distanciay;
    }

    for (int i = 0; i < qtd_parametros; ++i)
    {
        cmd.parametros[i] = novos_parametros[i];
    }

    polygon(img, cmd);

}

//Define a cor atual
void color(imagem *img, int parametros[]){
    
    for (int i = 0; i < 3; ++i)
    {
        img->cor_atual[i] = parametros[i];
    }
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

//Cria círculos
//Algoritmo adaptado de https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C
void circle(imagem *img, int parametros[]){

    int raio = parametros[2];
    int x0 = parametros[0];
    int y0 = parametros[1];
    int f = 1 - raio;
    int ddF_x = 0;
    int ddF_y = -2 * raio;
    int x = 0;
    int y = raio;

    for (int i = 0; i < 3; ++i)
    {
        img->matriz[x0][y0 + raio][i] = img->cor_atual[i];
        img->matriz[x0][y0 - raio][i] = img->cor_atual[i];
        img->matriz[x0 + raio][y0][i] = img->cor_atual[i];
        img->matriz[x0 - raio][y0][i] = img->cor_atual[i];
    }

    while(x < y){

        if(f >= 0){
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        for (int i = 0; i < 3; ++i)
        {
            img->matriz[x0 + x][y0 + y][i] = img->cor_atual[i];
            img->matriz[x0 - x][y0 + y][i] = img->cor_atual[i];
            img->matriz[x0 + x][y0 - y][i] = img->cor_atual[i];
            img->matriz[x0 - x][y0 - y][i] = img->cor_atual[i];
            img->matriz[x0 + y][y0 + x][i] = img->cor_atual[i];
            img->matriz[x0 - y][y0 + x][i] = img->cor_atual[i];
            img->matriz[x0 + y][y0 - x][i] = img->cor_atual[i];
            img->matriz[x0 - y][y0 - x][i] = img->cor_atual[i];
        }

    }

}

//Função recursiva para a execução do fill
void rec_fill(imagem *img, int x, int y, int cor_inicial[]){

    int pixel_valido = 1;

    for (int i = 0; i < 3; ++i)
    {
        if(cor_inicial[i] != img->matriz[y][x][i]){

            pixel_valido = 0;
            break;
        }
    }

    if(pixel_valido == 1){


        for (int i = 0; i < 3; ++i)
        {
            img->matriz[y][x][i] = img->cor_atual[i];
        }

        if(x - 1 >= 0){

            rec_fill(img, x - 1, y, cor_inicial);
        }

        if(x + 1 < img->largura){

            rec_fill(img, x + 1, y, cor_inicial);
        }

        if(y - 1 >= 0){

            rec_fill(img, x, y - 1, cor_inicial);
        }
    
        if(y + 1 < img->altura){

            rec_fill(img, x, y + 1, cor_inicial);
        }

    }

}

// preenche figuras
void fill(imagem *img, int parametros[]){

    int x = parametros[0];
    int y = parametros[1];
    int cor_inicial[3];
    int pintado = 1;

    for (int i = 0; i < 3; ++i)
    {
        cor_inicial[i] = img->matriz[y][x][i];
    }

    for (int i = 0; i < 3; ++i)
    {
       if(img->cor_atual[i] != img->matriz[y][x][i]){

            pintado = 0;
            break;
        }
    }

    if(pintado == 0){

        rec_fill(img, x, y, cor_inicial);  

    } 
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

        //printf(">>>Altura: %d\n", img->altura);
        //printf(">>>Largura: %d\n", img->largura);

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
