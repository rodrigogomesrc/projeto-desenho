#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "funcoes.h"

//Salva a imagem no arquivo de acordo com a matriz de pixels
//Algoritmo adaptado de https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
void save(imagem img, char nome_arquivo[]){

    FILE *file = fopen(nome_arquivo, "wb");
    fprintf(file, "P3\n%d %d\n255\n", img.altura, img.largura);
    
    for (int i = 0; i < img.largura; ++i)
    {
        for (int j = 0; j < img.altura; ++j)
        {
            for (int z = 0; z < 3; ++z)
            {   
                fprintf(file, "%d ", img.matriz[i][j][z]);
            }
            
        }
    }

    fclose(file); 
}

//Função para criar uma reta na imagem
//Algoritmo adptado de https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#All_cases
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

        img.matriz[y0][x0][0] = img.cor_atual[0];
        img.matriz[y0][x0][1] = img.cor_atual[1];
        img.matriz[y0][x0][2] = img.cor_atual[2];

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

//Função para criar uma reta na imagem
imagem polygon(imagem img, comando cmd){

    int qtd_pontos = cmd.parametros[0];
    int ordenadas = cmd.qtd_parametros -1;
    int parametros[4];
    double det;

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
        img = line(img, parametros);
    }

    return img;
}

//Define a cor atual
imagem color(imagem img, int parametros[]){
    
    img.cor_atual[0] = parametros[0];
    img.cor_atual[1] = parametros[1];
    img.cor_atual[2] = parametros[2];

    return img;
}

//Limpa a imagem deixando todos os pixels com a cor recebida por parâmetro
imagem clear(imagem img, int parametros[]){

    for(int i = 0; i < img.largura; i++)
    {
        for (int j = 0; j < img.altura; ++j)
        {   

            img.matriz[i][j][0] = parametros[0];
            img.matriz[i][j][1] = parametros[1];
            img.matriz[i][j][2] = parametros[2];
        }
    }

    return img; 
}

//Cria retângulos
imagem rect(imagem img, int parametros[]){

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

    img = polygon(img, cmd);

    return img;

}
 
//Abre um arquivo de imagem ppm para edição
imagem open(imagem img, char nome_arquivo[]){

    char text[10];
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

        img = alocar_matriz();
        
        fgets(text, 10, file);
        fgets(text, 10, file);
        
        split(text, " ", text_split);
        
        strcpy(altura, text_split[0]);
        strcpy(largura, text_split[1]);
        
        strcpy(img.nome_imagem, nome_arquivo_tratado);

        sscanf(altura, "%d", &img.altura);
        sscanf(largura, "%d", &img.largura);
        img = realocar_matriz(img);

        qtd_cores = img.altura * img.largura * 3;

        char cores[(qtd_cores + 1) * 12];
        char vetor_cores[qtd_cores][50];

        //erro na linha de baixo para imagens retangulares
        fgets(text, 10, file);
        fgets(cores, qtd_cores * 4 , file);

        split(cores, " ", vetor_cores);

        int indice = 0;
        for (int i = 0; i < img.altura; ++i)
        {
            for (int j = 0; j < img.largura; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {   
                    sscanf(vetor_cores[indice], "%d", &img.matriz[i][j][k]);
                    indice++;
                }
            }
        }
    }


    return img;
}

//Define a resolução da imagem
imagem image(imagem img, int parametros[]) {

    img.altura = parametros[0];
    img.largura = parametros[1];
    img = realocar_matriz(img);

    return img;
}

/*Recebe a imagem e os comandos vindo do arquivo, chamando a 
função correspondente com a imagem a ser editada */
imagem interpretar(comando entrada, imagem img) {

    if(strcmp(entrada.nome_comando, "save") == 0){

        save(img, entrada.comando_string);
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

    else if(strcmp(entrada.nome_comando, "polygon") == 0){

        img = polygon(img, entrada);
    }
    else if(strcmp(entrada.nome_comando, "rect") == 0)
    {
        img = rect(img, entrada.parametros);
    }

    return img;

}
/* Lê o arquivo de comandos, criando uma struct de comando que é passado 
para a função que interpreta juntamente com uma instância da imagem*/
void input(char nome_arquivo[]){

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