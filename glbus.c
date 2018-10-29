#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <gconio.h>
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
 }Endereco;

 typedef struct
 {
	char nome[50],sexo;
	int idade;
	float passagens;
	Endereco end;
 }Pessoa;

 typedef struct
 {
	char destino[20],duration[20];
	float distancia,preco;
	int passagensDisponiveis[40];
 }Info;


Info locais[10];
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
void setVagas(Info bus[],int n)
{
    for(int i=0;i<n;i++)
        bus[0].passagensDisponiveis[i] = 0;
}
void getVagas(Info bus[],int n)
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

int reservaVagas(Info bus[],int n)
{
    int vagaDesejada;
    int quantVagas;
    int cont=0;

    printf("Deseja reservar quantas vagas?\n");
    scanf(" %d",&quantVagas);

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
		printf("===============================================\n"); //Fazer outra função para MENU()
		printf("=          1 - Consultar Todas as Rotas       =\n");
		printf("=          2 - Pesquisar Rotas Específicas    =\n");
		printf("=          3 - Comprar Passagem               =\n");
		printf("=          4 - Consultar Vagas                =\n");
		printf("=          5 - Reservar Vagas                 =\n");
		printf("=          0 - Sair                           =\n");
		printf("===============================================\n");

		setbuf(stdin,NULL);
		key=getch();

        int vagaDesejada;
		switch (key)
		{
			case '1': consultaTodasRotas();break;
			case '2': consultaRotas();break;
			case '3': comprarPassagem();break;
			case '4': getVagas(bus,40); break;
			case '5': reservaVagas(bus,40); break;
		}

		printf("Tecle ENTER...\n");
		setbuf(stdin,NULL);
		getch();

	}while(key!='0');
	return 0;
}





