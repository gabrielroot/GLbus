#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gconio.h>
/*Authors: Gabriel Ferreira && Lucas Pimenta
 *Date:
 *Description:
 *
 /////////////////////////////////
 * 2 onibus para cada rota p/ dia
 * horario do onibus pre definido com RAND
 * ///////////////////////////////
 * Ao imprimir o relatório, o sistema deverá informar qual assento o cliente escolheu, quanto ele pagou e se quer ida e volta
 */

 typedef struct
 {
	char uf[2],cidade[30],rua[50],bairro[50];
	int num;
 }Endereco;

 typedef struct
 {
	char nome[50][40],sexo[40],destino[20];
	int idade[40],passagens,contaPassagens;
	float preco;
	Endereco end[40];
 }Pessoa;

 typedef struct
 {
	char destino[20],duration[20];
	float distancia,preco;
	int passagensDisponiveis[40];
 }Info;

 void cadastra(Pessoa *cliente)
 {
	 //int pass;
	 printf("Quantas passagens? ");
	 scanf(" %d",&cliente->passagens);		// ATENÇÃO = estamos atendendo somente 1 cliente... precisamos de alocação dinamica aqui (prox. materia)
	 for(int i=0; i<cliente->passagens; i++)
	 {
		system("clear");
		printf("Cadastrar(%d°)\n",i+1);

		printf("	Nome: ");
		scanf(" %[^\n]s", cliente->nome[i]);
		printf("	Idade: ");
		scanf(" %d", &cliente->idade[i]);
		printf("	Sexo (M/F): ");
		scanf(" %c", &cliente->sexo[i]);

		printf("	Estado: (UF)");
		scanf(" %[^\n]s", cliente->end[i].uf);
		printf("	Cidade: ");
		scanf(" %[^\n]s", cliente->end[i].cidade);
		printf("	Rua: ");
		scanf(" %[^\n]s", cliente->end[i].rua);
		printf("	Bairro: ");
		scanf(" %[^\n]s", cliente->end[i].bairro);

		cliente->contaPassagens++;

		system("clear");
	}
 }

 Info insereRotas(Info locais[],int cont)
 {
	char rotas[30][10];

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

		strcpy(locais[cont].destino,rotas[cont]);
		locais[cont].distancia=1+rand()%1000-1;
		locais[cont].preco=locais[cont].distancia*0.4;
		//locais[i].passagensDisponiveis = (1+rand()%39);

	return locais[cont];
 }
 int consultaTodasRotas(Info locais[])
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
 int consultaRotas(Info locais[])
 {
	char rota[30];
	int bool=0;


	printf("Insira o Destino: ");
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

	}
					return 0;												//não existe a rota

 }

Info getVagas(Info bus[],int n)
{
    int cont=0;

    for(int i=0;i<n;i++)
    {
        if(bus[0].passagensDisponiveis[i]==0)
            printf("%2d[O]",i+1);
            else
                printf("%2d[X] ",i+1);
        cont++;
        if(cont==10)
            printf("\n");
        if(cont==20)
            printf("\n\n");
        if(cont==30)
            printf("\n");
    }
    printf("\n");
    return bus[n];

}

int reservaVagas(Info bus[],int* quantVagas)
{
    int vagaDesejada;
    int cont=0;

    do{
        getVagas(bus,40);
        printf("Digite o numero da Vaga Desejada (de 1-40):\n");
        do
			scanf(" %d",&vagaDesejada);
		while(vagaDesejada<1 || vagaDesejada>40);

        if(bus[0].passagensDisponiveis[vagaDesejada-1] == 0){
            bus[0].passagensDisponiveis[vagaDesejada-1] = 1;
            printf("Vaga Reservada com sucesso!\n");
            cont++;
            if(cont == *quantVagas)
                return 1;
        }
        else if (bus[0].passagensDisponiveis[vagaDesejada-1] == 1)
            printf("ATENÇÃO! Esta vaga já foi reservada!\nFavor escolher outra vaga!\n");

    }while (cont!=*quantVagas);

	return 0;
}

 int comprarPassagem(Info bus[], Pessoa *cliente,Info locais[])
 {
	int retorno;
	char ida;
	cliente->preco=0;
	cliente->contaPassagens=0;

	do
	{
		retorno=consultaRotas(locais);
	}while(!retorno);

	while((ida!='s')&&(ida!='n'))
	{
		printf("Ida & Volta? (s/n)");
		scanf(" %c",&ida);
	}
	//printf("Deseja realmente ir para %s?",locais[retorno].destino);
	cadastra(&*cliente);

	printf("\n--%d--\n",retorno);

	if(ida=='s')// se cliente quer ida e volta então paga em dobro, senão...
	{
		reservaVagas(bus,&cliente->passagens);
		cliente->preco=cliente->passagens*locais[retorno].preco*2;
	}
	else
	{
		reservaVagas(bus,&cliente->passagens);
		cliente->preco=cliente->passagens*locais[retorno].preco;
	}

	strcpy(cliente->destino,locais[retorno].destino);
	printf("Total: %.2f\n",cliente->preco);


	return 0;
 }
void setVagas(Info bus[],int n)
{
    for(int i=1;i<=n;i++)
        bus[0].passagensDisponiveis[i] = 0;
}

 void getClientes(Pessoa cliente[],int cont)
 {
	char pass[10];
	do
	{
		printf("Password Amnin: ");
		scanf(" %[^\n]s",pass);
		system("clear");
		if(strcmp(pass,"123")==0)
			for(int j=0; j<cont; j++)
			{
				for(int i=0; i<cliente[j].contaPassagens; i++)
				{
					printf("%s  >>>\n", cliente[j].nome[i]);
					printf("	Idade: %d\n", cliente[j].idade[i]);
					printf("	Sexo: %c\n", cliente[j].sexo[i]);

					printf("	Estado: %s\n", cliente[j].end[i].uf);
					printf("	Cidade: %s\n", cliente[j].end[i].cidade);
					printf("	Rua: %s\n", cliente[j].end[i].rua);
					printf("	Bairro: %s\n", cliente[j].end[i].bairro);
					printf("	Destino: %s\n\n", cliente[j].destino);
				}
			}
		else
			printf("Senha incorreta!\n");
	}while(strcmp(pass,"123")!=0);
 }

int main()
{
	Info bus[10];
	char key;
	Info locais[10];
	Pessoa cliente[100];
	int cont=0;

	setVagas(bus,40); //Zerando o vetor vagas (bus[i].passagensDisponiveis)
	srand(time(NULL));

	for(int i=0; i<10; i++)
		locais[i]=insereRotas(locais,i);


	do
	{
		system("clear");
		printf("===============================================\n");
		printf("=          1 - Consultar Todas as Rotas       =\n");
		printf("=          2 - Pesquisar Rotas Específicas    =\n");
		printf("=          3 - Comprar Passagem               =\n");
		printf("=          4 - Consultar Vagas                =\n");
		printf("=          5 - Relatório de Vendas            =\n");
		printf("=          0 - Sair                           =\n");
		printf("===============================================\n");

		setbuf(stdin,NULL);
		key=getch();

		switch (key)
		{
			case '1': consultaTodasRotas(locais);break;
			case '2': consultaRotas(locais);break;
			case '3': comprarPassagem(bus,&cliente[cont++],locais);break;
			case '4': getVagas(bus,40); break;
			case '5': getClientes(cliente,cont); break;
		}

		printf("Tecle ENTER...\n");
		setbuf(stdin,NULL);
		getch();

	}while(key!='0');
	return 0;
}
