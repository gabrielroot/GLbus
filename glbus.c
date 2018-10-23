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
	float passagens;	
	endereco end;
 }Pessoa;
 
 typedef struct
 {
	char destino[20],duration[20];
	float distancia,preco;
	int passagensDisponiveis;
 }info;
 
 
info locais[10];
Pessoa cliente;
char rotas[30][10];
int x;
 
 void cadastra()
 { 
	 printf("Quantas passagens? ");
	 scanf(" %f",&cliente.passagens);		//estamos atendendo somente 1 cliente... precisamos de alocação dinamica aqui (prox. materia)
	 printf("Qual o seu nome?: ");
	 scanf(" %s", cliente.nome);
 }
 
 int insereRotas()
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
	
	for(int i=0; i<10; i++)
	{ 
		strcpy(locais[i].destino,rotas[i]);
		locais[i].distancia=1+rand()%1000-1;
		locais[i].preco=locais[i].distancia*0.4;
		locais[i].passagensDisponiveis=1+rand()%40-1;
	}
	return 0; 
 }
 int consultaTodasRotas()
 {
	for(int i=0; i<10; i++)
	{
			printf("\n");
				
			printf("Rota: %s\n",locais[i].destino);
			printf("Distância: %.0f Km\n",locais[i].distancia);
			printf("Preço: R$ %.2f\n",locais[i].preco);
			
			printf("\n");
	}
	return 0;
}
 int consultaRotas()
 {
	char rota[30];
	int bool=0;
	
	
	printf("Insira a rota: ");
	scanf(" %[^\n]s",rota);
	
	for(int i=0; i<10; i++)
	{
		bool=strcmp(locais[i].destino,rota)==0;
		if(bool)
		{
			system("clear");
			printf("Rota: %s\n",locais[i].destino);
			printf("Distância: %.0f Km\n",locais[i].distancia);
			printf("Preço: R$ %.2f\n",locais[i].preco);
			return i;    										// Existe a rota
		}
	}
		
	if(!bool)
	{
		system("clear");
		printf("Não Disponível!\n");
		return 0;												//não existe a rota	
	}
 }
 
 int comprarPassagem()
 {
	int retorno;
	char ida;
	
	while(retorno==0)
		retorno=consultaRotas();
	
	while((ida!='s')&&(ida!='n'))
	{
		printf("Ida & Volta? (s/n)");
		scanf(" %c",&ida);
	}
	//printf("Deseja realmente ir para %s?",locais[retorno].destino);
	cadastra();
	if(ida=='s')											// se cliente quer ida e volta então paga em dobro, senão...
		cliente.passagens*=locais[retorno].preco*2;
	else
		cliente.passagens*=locais[retorno].preco;	
	
	printf("Total: %.2f\n",cliente.passagens);
	
	return 0;
 }

 
int main()
{
	char key;

	srand(time(NULL));

	insereRotas();
	
	do
	{
		system("clear");
		printf("===============================================\n"); //Fazer outra função para MENU()
		printf("=          1 - Consultar Todas as Rotas       =\n");
		printf("=          2 - Pesquisar Rotas Específicas    =\n");
		printf("=          3 - Comprar Passagem               =\n");
		printf("=          0 - Sair                           =\n");
		printf("===============================================\n");
		
		setbuf(stdin,NULL);
		key=getch();
		
		switch (key)
		{
			case '1': consultaTodasRotas();break;
			case '2': consultaRotas();break;
			case '3': comprarPassagem();break;
		}
		
		printf("Tecle ENTER...\n");
		setbuf(stdin,NULL);
		getch();
		
	}while(key!='0');	
	return 0;
}

