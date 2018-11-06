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
 /////////////////////////////////
 * 2 onibus para cada rota p/ dia
 * horario do onibus pre definido com RAND
 * ORGANIZAR AS FUNCOES (comprar passagem chama reservavagas)
 * configurar a ida volta
 * ///////////////////////////////
 * O Busão está aceitando a vaga 0!
 * CADASTRAR MAIS QUE 1 CLIENTE URGENTEMENTE (Atualmente, cada cliente pode comprar até 40 passagens, mas ainda não conseguimos cadastrar mais que 1 cliente)
 */
 typedef struct
 {
	char uf[2],cidade[30],rua[50],bairro[50];
	int num;
 }Endereco;

 typedef struct
 {
	char nome[50][40],sexo[40];
	int idade[40];
	float passagens;
	Endereco end[40];
 }Pessoa;

 typedef struct
 {
	char destino[20],duration[20];
	float distancia,preco;
	int passagensDisponiveis[40];
 }Info;


Info locais[10];
Pessoa cliente;

int contaPassagens;

 void cadastra()
 {
	 //int pass;

	 printf("Quantas passagens? ");
	 scanf(" %f",&cliente.passagens);		// ATENÇÃO = estamos atendendo somente 1 cliente... precisamos de alocação dinamica aqui (prox. materia)
	 for(int i=0; i<cliente.passagens; i++)
	 {
		system("clear");
		printf("Cadastrar(%d°)\n",i+1);

		printf("	Nome: ");
		scanf(" %s", cliente.nome[i]);
		printf("	Idade: ");
		scanf(" %d", &cliente.idade[i]);
		printf("	Sexo (M/F): ");
		scanf(" %c", &cliente.sexo[i]);

		printf("	Estado: (UF)");
		scanf(" %s", cliente.end[i].uf);
		printf("	Cidade: ");
		scanf(" %s", cliente.end[i].cidade);
		printf("	Rua: ");
		scanf(" %s", cliente.end[i].rua);
		printf("	Bairro: ");
		scanf(" %s", cliente.end[i].bairro);

		contaPassagens++;

		system("clear");
	}
 }

 int insereRotas()
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

	for(int i=0; i<10; i++)
	{
		strcpy(locais[i].destino,rotas[i]);
		locais[i].distancia=1+rand()%1000-1;
		locais[i].preco=locais[i].distancia*0.4;
		//locais[i].passagensDisponiveis = (1+rand()%39);
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

int reservaVagas(Info bus[],int n,float quantVagas)
{
    int vagaDesejada;
    int cont=0;

    do{
        getVagas(bus,40);
        printf("Digite o numero da Vaga Desejada:\n");
        scanf(" %d",&vagaDesejada);

        if(bus[0].passagensDisponiveis[vagaDesejada-1] == 0){
            bus[0].passagensDisponiveis[vagaDesejada-1] = 1;
            printf("Vaga Reservada com sucesso!\n");
            cont++;
            if(cont == quantVagas)
                return 1;
        }
        else if (bus[0].passagensDisponiveis[vagaDesejada-1] == 1)
            printf("ATENÇÃO! Esta vaga já foi reservada!\nFavor escolher outra vaga!\n");

    }while (cont!=quantVagas);

	return 0;
}

 int comprarPassagem(Info bus[])
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

	if(ida=='s')// se cliente quer ida e volta então paga em dobro, senão...
	{
		reservaVagas(bus,40,cliente.passagens);
		cliente.passagens*=locais[retorno].preco*2;
	}
	else
	{
		reservaVagas(bus,40,cliente.passagens);
		cliente.passagens*=locais[retorno].preco;
	}

	printf("Total: %.2f\n",cliente.passagens);


	return 0;
 }
void setVagas(Info bus[],int n)
{
    for(int i=0;i<n;i++)
        bus[0].passagensDisponiveis[i] = 0;
}

 void getClientes()
 {
	char pass[10];
	do
	{
		printf("Password Amnin: ");
		scanf(" %[^\n]s",pass);
		system("clear");
		if(strcmp(pass,"123")==0)
			for(int i=0; i<contaPassagens; i++)
			{
				printf("Consultar(%d°)\n",i+1);

				printf("	Nome: %s\n", cliente.nome[i]);
				printf("	Idade: %d\n", cliente.idade[i]);
				printf("	Sexo: %c\n", cliente.sexo[i]);

				printf("	Estado: %s\n", cliente.end[i].uf);
				printf("	Cidade: %s\n", cliente.end[i].cidade);
				printf("	Rua: %s\n", cliente.end[i].rua);
				printf("	Bairro: %s\n", cliente.end[i].bairro);
			}
		else
			printf("Senha incorreta!\n");
	}while(strcmp(pass,"123")!=0);
 }

int main()
{
	Info bus[10];
	char key;
	setVagas(bus,40); //Zerando o vetor vagas (bus[i].passagensDisponiveis)
	srand(time(NULL));
	insereRotas();

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
			case '1': consultaTodasRotas();break;
			case '2': consultaRotas();break;
			case '3': comprarPassagem(bus);break;
			case '4': getVagas(bus,40); break;
			case '5': getClientes(); break;
		}

		printf("Tecle ENTER...\n");
		setbuf(stdin,NULL);
		getch();

	}while(key!='0');
	return 0;
}
