/*
	Engenharia Informática 2014/2015
	Alexandre Monteiro - 2140247
	Emanuel Lopes - 2140825
	Programa para gerir Balões de Ar quente
*/
//bibliotecas
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//constantes do programa
#define MAXIMO_BALOES 10
#define MINIMO_BALOES 1
#define DATA_MINIMA 1940
#define ANO 2013
#define LOTACAOMAXIMA 25
#define LOTACAOMINIMA 1
#define MAX_DESIGNACAO 60

#define MAX_LISTA 3 // Letras A B C

#define PRECO_DEFAULT 10
#define DESCONTO 0.10
#define SEM_DESCONTO 0

#define GRUPO 1
#define SEM_GRUPO 0

#define POS_A 0
#define POS_B 1
#define POS_C 2
#define LIMPAR_MEMORIA 1
#define NAO_LIMPAR_MEMORIA 0
#define MAX_NOME 20
/*****Estruturas*********/

//estrutura bilhetes
typedef struct{
    char nome[MAX_NOME];
    int nrPessoas;
    char origem;
    char destino;
    int grupo; //verificar se é grupo 0- nao é grupo 1- é grupo
    float preco;
} bilhetesStruct;

//estrutura listas
typedef struct{
    int nrBilhetes;
    bilhetesStruct *bilhetes;
} listaEsperaStruct;
//Estruturas baloes
//estrutura da DATA
typedef struct
{
    int dia, mes, ano;
} dataFabricoStruct;

//estrutura dos baloes
typedef struct
{
    int numero;
    char designacao[MAX_DESIGNACAO];
    dataFabricoStruct data;
    int lotacaoMaxima;
    char localInicio;
    char localFinal;
    int Totalviagens; //usado para a estatistica
    int numeroPessoasTransportadas; //usado para a estatistica
    //informacao do passageiros
    int nrBilhetes;
    int nrTuristasNobalao;
    bilhetesStruct *bilhetes;
} baloesStruct;

//Estrutura contadores
typedef struct
{
    int nrBaloes;
    int passageirosTransportados;
    int viagensRealizadas;
    int pListaEspera;
    float receita;
    int nrViagens;
    int destinoA;
    int destinoB;
    int destinoC;
    float preco;
} contadorStruct;

//estrutura viagens
typedef struct{
    int nrViagem;
    int nrBalao;
    int quantidadeTuristas;
}viagensStruct;


/************************/

/*Prototipos das funcoes*/
/****baloes*****/
int menu(contadorStruct contador);
void menuBaloes(int opcao, baloesStruct baloes[], contadorStruct *contador);
void inserirBaloes(baloesStruct baloes[], contadorStruct *contador);
char loopPedirPosicao(char msg[]);
void movimentarBaloes(baloesStruct baloes[], contadorStruct *contador);
baloesStruct MovimentarBaloesManualmente(baloesStruct baloes, contadorStruct *contador);
void alterarDadosBalao(baloesStruct baloes[], contadorStruct *contador);
dataFabricoStruct loopDataBalao(dataFabricoStruct data);
void infoBaloes(baloesStruct baloes);
void consultarBaloes(baloesStruct baloes[], int totalBaloes, char caracter);
int loopPesquisaBalaoValido(baloesStruct baloes[], contadorStruct contador);
int loopPesquisaBalaoinValido(baloesStruct baloes[], int nrBaloes);
int procurarNumeroBalao(baloesStruct baloes[], int numero, int totalBaloes);
int eliminarBaloes(baloesStruct baloes[], contadorStruct *contador, int posicao);
/***fim baloes**/
/***globais***/
int lerNumero(int minimo, int maximo);
void lerString(char str[], int maxCaracteres);
char lerCaracter(void);
void limparBuffer(void);
int validarData(int dia, int mes, int ano);
viagensStruct *lerRegistosFicheiroBinario(contadorStruct *contador, baloesStruct baloes[], listaEsperaStruct lista[], viagensStruct viagens[]);
void gravarRegistos(contadorStruct *contador, baloesStruct baloes[], listaEsperaStruct lista[], viagensStruct viagens[]);
void logging(int nrViagem, int nrBalao, int passageiros);
void alterarPrecoBilhete(contadorStruct *contador);
/*********Viagens e bilhetes***************/
void menuBilhetes(int opcao, contadorStruct *contador, listaEsperaStruct listaEspera[]);
void infoBilhetes(bilhetesStruct bilhete);
void limparLista(listaEsperaStruct lista[],int limparMemoria);
void comprarBilhetes(contadorStruct *contador, listaEsperaStruct lista[]);
void mostrarBilhetesFiltro(int escolha, listaEsperaStruct lista[]);
void mostrarLocalizacaoBaloes(baloesStruct baloes[], contadorStruct *contador, char local);
void infoViagens(viagensStruct viagens[], contadorStruct contador);
viagensStruct *inserirViagem(baloesStruct baloes[], viagensStruct *viagens, contadorStruct *contador, listaEsperaStruct lista[]);
int charToPos(char letra);
baloesStruct largarTuristas(baloesStruct balao, contadorStruct *contador, int nrViagem);
int nrViagens(char localI, char localF);
int nrViagensDestinoFinal(int DF, int a, int b, int c);
/***Dados estatisticos***/
void dadosEstatisticos(int submenu, baloesStruct baloes[], viagensStruct viagens[], contadorStruct contador, listaEsperaStruct lista[]);
void mediaTuristasBalao(baloesStruct baloes[], contadorStruct contador);
void balaoMaisViagens(baloesStruct baloes[], contadorStruct contador);
void totalViagensBalao(baloesStruct baloes[], contadorStruct contador);
void percentamTuristasDestino(viagensStruct viagens[], contadorStruct contador);
void estatisticaBilhetes(listaEsperaStruct lista[]);

