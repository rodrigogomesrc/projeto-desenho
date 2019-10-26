
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct comando_t
{
    char nomeComando[20];
    int qtdParametros;
    int parametros[30];
    
}comando;


//possivelmente usar alocação dinâmica para a imagem
typedef struct  imagem_t
{
    //as dimensões são: altura, largura e pixel (3 cores rgb)
    int matriz[100][100][3];
    int altura;
    int largura;
    
}imagem;

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
}


void save_image(imagem img){


    for(int i = 0; i < img.altura; i++)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            for (int z = 0; z < 3; ++z)
            {
                img.matriz[i][j][z] = 255;
            }
        }

    }

    char altura[10];
    char largura[10];
    sprintf(altura, "%d", img.altura);
    sprintf(largura, "%d", img.largura);
    char cor[5];

    FILE *file = fopen("imagem.ppm", "wb");
    fprintf(file, "P3\n%s %s\n255\n", altura, largura);
    
    for (int i = 0; i < img.altura; ++i)
    {
        for (int j = 0; j < img.largura; ++j)
        {
            for (int z = 0; z < 3; ++z)
            {
                sprintf(cor, "%d", img.matriz[j][i][z]); 
                strcat(cor, " ");
                fprintf(file, "%s", cor);
            }
            
        }
    }

    fclose(file); 

}

imagem interpretar(comando entrada, imagem img) {

    if(strcmp(entrada.nomeComando, "save") == 0){
        save_image(img);
    }

    else if(strcmp(entrada.nomeComando, "image") == 0){
        img.altura = entrada.parametros[0];
        img.largura = entrada.parametros[1];
    }

    else if(strcmp(entrada.nomeComando, "color") == 0){
        puts("comando color");
    }

    else if(strcmp(entrada.nomeComando, "clear") == 0){
        puts("comando clear");
    }

    return img;

}

void input(char nome_arquivo[]){

    imagem img;

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

        printf("File not found\n");

    } else {

        while(fgets(text, 50, file) != NULL){

            qtd_parametros = 0;
            split(text, " ", entradas);

            // salvando o comando
            strcpy(nome_comando, entradas[0]);

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

            comando instrucao;
            strcpy(instrucao.nomeComando, nome_comando);
            instrucao.qtdParametros = qtd_parametros;

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
    }

}

int main(int argc, char const *argv[])
{

    input("input.txt");
    return 0;
}
