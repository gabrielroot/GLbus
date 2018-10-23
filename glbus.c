#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gconio.h>
/*Authors: Gabriel Ferreira && Lucas Pimenta
 *Date:
 *Description: 
 * 
 * Cálculo do valor da passagem
 * Duração da viagem
 * Vagas disponiveis
 * Validações de rotas
 * 
 */
 typedef struct
 {
	char uf[2],cidade[30],rua[50],bairro[50];
	int num; 
 }endereco;
 
 typedef struct
 {
	char nome[50],sexo;
	int idade;
	endereco end;
 }Pessoa;
 
 typedef struct
 {
	char destino[20],duration[20];
	float distancia,preco;
	int passagens;
 }info;
 
 
info locais[10];
Pessoa cliente;
char rotas[30][10];
int x;
 
 void cadastra()
 { 
	 printf("Olá!\nQual o seu nome?: ");
	 scanf(" %s", cliente.nome);
 }
 
 int insereRotas(int i)
 {
	 
	
	 strcpy(rotas[0],"Brasília");
	 strcpy(rotas[1],"Tocantins"); 
	 strcpy(rotas[2],"Pernambuco");
	 strcpy(rotas[3],"Acre");
	 strcpy(rotas[4],"Goiânia");
	 strcpy(rotas[5],"Sergipe");
	 strcpy(rotas[6],"Bahia");
	 strcpy(rotas[7],"Sergipe");
	 strcpy(rotas[8],"Piauí");
	 strcpy(rotas[9],"Alagoas");
	 
	strcpy(locais[i].destino,rotas[i]);
	locais[i].distancia=1+rand()%1000-1;
	locais[i].preco=locais[i].distancia*0.4;
	locais[i].passagens=1+rand()%40-1;
	return 0; 
 }

 int consultaRotas()
 {
	char rota[30];
	int bool=0;
	
	printf("Ok %s!\nInsira a rota: ",cliente.nome);
	scanf(" %[^\n]s",rota);
	
	for(int i=0; i<10; i++)
	{
		bool=strcmp(locais[i].destino,rota)==0;
		if(bool)
		{
			printf("Rota: %s\n",locais[i].destino);
			printf("Distância: %.0f Km\n",locais[i].distancia);
			printf("Preço: R$ %.2f\n",locais[i].preco);
			return 1;    										// Existe a rota
		}
	}
		
	if(!bool)
	{
		printf("Não Disponível!\n");
		return 0;												//não existe a rota	
	}
 }
 
 int comprarPassagem()
 {
	int pass;
	cadastra();
	while(consultaRotas()!=1)
	{
		consultaRotas();
	}
	printf("Quantas passagens? ");
	scanf(" %d",&pass);
	return 0;
 }

 
int main()
{

	srand(time(NULL));
	
	for(int i=0; i<10; i++)
	{
		insereRotas(i);
	}	
	
	comprarPassagem();
	printf("%s",__TIME__);
	return 0;
}

