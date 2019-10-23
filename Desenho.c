#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

// converter a entrada para uma struct
void interpretar(char comando[50], int tamanho_vetor, int parametros[tamanho_vetor] ) {

	//interpretação dos comandos
}

void input(char nome_arquivo[]){


	FILE *file;
	file = fopen(nome_arquivo, "r");

	// usar alocação dinâmica nesses vetores
	char text[50]; // essa variável tem tamanho fixo
	char entradas[50][50];
	char comando[50];
	int parametros[50];

	if(file == NULL){

		printf("File not found\n");

	} else {

		while(fgets(text, 50, file) != NULL){

			split(text, " ", entradas);

			// salvando o comando
			strcpy(comando, entradas[0]);

			// separando os comandos
			for (int i = 0; i < 49; ++i)
			{
				sscanf(entradas[i + 1], "%d", &parametros[i]);
			}

			/*
			puts("parametros:");
			for (int i = 0; i < 49; ++i)
			{
				printf("%d\n", parametros[i]);
			}*/
		}
		
		fclose(file);
	}

}

int main(int argc, char const *argv[])
{

	input("input.txt");
	return 0;
}