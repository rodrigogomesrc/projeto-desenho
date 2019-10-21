#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *file;
	file = fopen("input.txt", "r");
	char text[50];

	if(file == NULL){
		printf("File not found\n");

	} else {

		while(fgets(text, 50, file) != NULL){

			printf("%s", text);
		}
		
		fclose(file);
	}
	return 0;
}