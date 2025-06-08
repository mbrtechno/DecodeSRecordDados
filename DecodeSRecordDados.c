/*
 ============================================================================
 Name        : DecodeSRecordDados.c
 Author      : Clayton Junior
 Version     :
 Copyright   : Your copyright notice
 Description : Decode SRecord Dados, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	FILE *entrada, *saida;
	char linha[255]; 		//Buffer para armazenar dado de cada linha
	int i, hex = 0;
	int ndados;



	printf("Processando...\n");

	//Abrir o arquivo a ser analisado e o arquivo que receberá os dados tratados
	entrada = fopen("RAM.mot", "r");
	if(entrada == NULL){
		perror("Erro ao abrir o arquivo de entreda");
		return EXIT_FAILURE;
	}

	saida = fopen("analisado.txt", "w");
	if(saida == NULL){
		perror("Erro ao abrir arquivo de saida");
		return EXIT_FAILURE;
	}

	//Leitura de cada linha
	while(fgets(linha, sizeof(linha), entrada)){

		//informa quantos bytes foram adicionados
		ndados = (strlen(linha)-3);

		//Testar se linha contém dados ou endereços
		if((linha[1] == '3')){
			//salvar a partir do inicio de dados até o checksum
			for(i = 12; i < ndados; i++){
				if(hex == 0){
					fputs("0x", saida);
					fputc(linha[i], saida);	// somente dados - sem checksum
					hex = 1;
				}else{
					fputc(linha[i], saida);	// somente dados - sem checksum
					fputs(" ", saida);
					hex = 0;
				}
			}
			fputc('\n', saida);	//arquivo possue quebra de linha
		}else{
			//Não adiciona linha que possuem somente informações de endereços
		}
	}

	//fechamento dos arquivos aberto
	fclose(entrada);
	fclose(saida);

	printf("Finalizado.\n");
	return EXIT_SUCCESS;
}
