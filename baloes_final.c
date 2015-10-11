/*
	Engenharia Informática 2014/2015
	Alexandre Monteiro - 2140247
	Emanuel Lopes - 2140825
	Programa para gerir Balões de Ar quente
*/

#include "header.h"

/**
O programa está organizado por funções
funções dos menus
funções globais
funções dos balões
funções das viagens e bilhetes
funções das estatisticas
**/

/** Funções Menus**/
//função principal do programa
/***MENUS***/
int main(void){
    /**declaração de variavies**/
    contadorStruct contador;
    baloesStruct baloes[MAXIMO_BALOES];
    listaEsperaStruct lista[MAX_LISTA];
    viagensStruct *viagens=NULL;
    int opcao=0, submenu=0;
    //os ponteiros são iniciados a null para que se possa usar o malloc para fazer a gestão da memória dinâmica
    limparLista(lista, NAO_LIMPAR_MEMORIA);
    //leitura do ficheiro binario
    viagens = lerRegistosFicheiroBinario(&contador, baloes, lista, viagens);
    do{
        opcao = menu(contador);//chama o menu principal que retorna a opcao escolhida
        switch(opcao){
            case 0:
                gravarRegistos(&contador, baloes, lista, viagens); //gravar as alteracoes no ficheiro binario
            break;
            case 1://menu baloes
                do{
                    printf("\n\n\n#############################################################\n");
                    printf("#_______________ MENU BALOES                 _______________#\n");
                    printf("#_______________ 1 - Inserir dados Baloes    _______________#\n");
                    printf("#_______________ 2 - Consultar dados Baloes  _______________#\n");
                    printf("#_______________ 3 - Alterar dados Baloes    _______________#\n");
                    printf("#_______________ 4 - Eliminar Baloes         _______________#\n");
                    printf("#_______________ 0 - Voltar ao menu principal_______________#\n");
                    printf("#############################################################\n");
                    printf("Escolha uma opcao: ");
                    submenu = lerNumero(0, 4);
                    menuBaloes(submenu, baloes, &contador); //chama a funcao que trata dos baloes e contadores
                }while(submenu!=0);
            break;
            case 2://menu viagens
                do{
                    printf("\n\n\n#############################################################\n");
                    printf("#_______________ MENU Viagens                _______________#\n");
                    printf("#_______________ 1 - Inserir Viagens         _______________#\n");
                    printf("#_______________ 2 - Consultar Viagens       _______________#\n");
                    printf("#_______________ 0 - Voltar ao menu principal_______________#\n");
                    printf("#############################################################\n");
                    printf("Escolha uma opcao: ");
                    submenu = lerNumero(0, 2);
                    switch(submenu){
                        case 1:
                                viagens = inserirViagem(baloes, viagens, &contador, lista);
                        break;
                        case 2:
                                infoViagens(viagens, contador);
                        break;
                    }
                }while(submenu!=0);
            break;
            case 3: //menu bilhetes
                do{
                    printf("\n\n\n#############################################################\n");
                    printf("#_______________ MENU Bilhetes               _______________#\n");
                    printf("#_______________ 1 - Vender Bilhetes         _______________#\n");
                    printf("#_______________ 2 - Consultar Bilhetes      _______________#\n");
                    printf("#_______________ 0 - Voltar ao menu principal_______________#\n");
                    printf("#############################################################\n");
                    printf("Escolha uma opcao: ");
                    submenu = lerNumero(0, 2);
                    menuBilhetes(submenu, &contador, lista);
                }while(submenu!=0);
            break;
            case 4:
                //Movimentar Baloes
                movimentarBaloes(baloes, &contador);
            break;
            case 5:
                //consultar dados estatisticos
                do{
                    printf("\n\n\n#############################################################\n");
                    printf("#_______ MENU Estatisticas                               ___#\n");
                    printf("#_______ 1 - Total viagens por cada balao                ___#\n");
                    printf("#_______ 2 - Media de turistas transportados por balao   ___#\n");
                    printf("#_______ 3 - Balao(oes) com mais viagens     _______________#\n");
                    printf("#_______ 4 - Percentagem de turistas por destino   _________#\n");
                    printf("#_______ 5 - Informacoes dos bilhetes              _________#\n");
                    printf("#_______ 0 - Voltar ao menu principal        _______________#\n");
                    printf("#############################################################\n");
                    printf("Escolha uma opcao: ");
                    submenu = lerNumero(0,5);
                    dadosEstatisticos(submenu, baloes, viagens, contador, lista);
                }while(submenu!=0);
            break;
            case 6:
                alterarPrecoBilhete(&contador);
            break;
        }
    }while(opcao!=0);
    limparLista(lista, LIMPAR_MEMORIA);
    free(viagens);
    viagens = NULL;
return 0;
}
//menu principal
int menu(contadorStruct contador){
    int opcao;
    printf("|--------------------MENU-----------------------------------|\n");
    printf(" Receita Obtida: %.2f \t Baloes Existentes: %d\n", contador.receita, contador.nrBaloes);
    printf(" Viagens Realizadas: %d \t Passageiros Transportados: %d\n", contador.viagensRealizadas, contador.passageirosTransportados);
    printf(" Passageiros em Lista de Espera: %d\n",  contador.pListaEspera);
    printf("|-----------------------------------------------------------|\n");
    printf("#############################################################\n");
    printf("#_______________ 1-BALOES                        ___________#\n");
    printf("#_______________ 2-VIAGENS                       ___________#\n");
    printf("#_______________ 3-BILHETES                      ___________#\n");
    printf("#_______________ 4-REGISTAR VIAGEM DO BALÃO      ___________#\n");
    printf("#_______________ 5-Consultar dados Estatisticos  ___________#\n");
    printf("#_______________ 6-Alterar Preco da viagem       ___________#\n");
    printf("#_______________ 0-Sair                          ___________#\n");
    printf("#############################################################\n");
    printf("Escolha uma opcao: ");
    opcao = lerNumero(0, 6);
    return opcao;
}

void menuBilhetes(int opcao,contadorStruct *contador, listaEsperaStruct lista[]){
    int submenu=1;
    switch(opcao){//comprar bilhetes
    case 1:
        comprarBilhetes(contador, lista);
    break;
    case 2://ler bilhetes
        do{
            printf("\n\n\n#############################################################\n");
            printf("#_______________ MENU  BILHETES -> Consultas _______________#\n");
            printf("#_______________ 1 - Ver todos os bilhetes   _______________#\n");
            printf("#_______________ 2 - Ver Bilhetes do ponto de origem _______#\n");
            printf("#_______________ 3 - Ver Bilhetes do ponto de destino ______#\n");
            printf("#_______________ 0 - Sair                    _______________#\n");
            printf("#############################################################\n");
            submenu = lerNumero(0, 3);
            mostrarBilhetesFiltro(submenu, lista);
        }while(submenu!=0);
        //mostrar todos os bilhetes
    break;
    }
}
/*** Fim Funcoes Menu***/

/***Funcoes  globais ***/
/*ler numero entre duas posicoes maximo e minimo
* Variaveis de entrada
* minimo - numero inteiro minimo
* maximo numero inteiro maximo
*/
void alterarPrecoBilhete(contadorStruct *contador){
    char letra;
    printf("O preco do bilhete e de: %.2f\n", contador->preco);
    do{
        printf("Deseja alterar o preco? (S/N)\n");
        letra = lerCaracter();
    }while(letra!='S' && letra!='N');
    if(letra=='S'){
        printf("Insira um novo Preco: ");
        scanf("%f", &contador->preco);
        printf("O novo Preco e: %.2f\n", contador->preco);
    }
}
int lerNumero(int minimo, int maximo){
    int numero, control;
    do{
        control = scanf("%d", &numero);
        limparBuffer();
        if(numero>maximo || numero<minimo)
        {
            printf("o numero encontra-se fora dos limites!\n O numero entre %d e %d\n", minimo, maximo);
            printf("Insira um novo numero: ");
        }
    }
    while(numero>maximo || numero<minimo || control!=1);
return numero;
}

//lê uma string a partir da teclado
void lerString(char str[], int maxCaracteres){
    do{
        char *ptr = NULL;
        fgets(str, maxCaracteres, stdin);
        ptr = strchr(str, '\n');
        if(ptr != NULL){
            *ptr = '\0';
        }
    }while(strcmp(str, "")==0);
}

//lê um caracter e converte o caracter para maiuscula
char lerCaracter(void){
    char opcao;
    scanf("%c", &opcao);
    opcao = toupper(opcao);
    limparBuffer(); //limpa o buffer antes de voltar a ler alguma coisa do teclado
return opcao;
}

//limpa o buffer
void limparBuffer(void){
    char chr;
    do{
        chr = getchar();
    }while(chr!='\n');
}

int validarData(int dia, int mes, int ano){ //verifica se a data se encontra correcta
    //se a data for inválida devolve 0
    int bissexto=0;
    if (( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 ){
        bissexto=1;
    }
    if(mes>=1 && mes<=12){
        switch(mes){
            case 2:
                if(bissexto==1){
                    if(dia>29){
                        printf("Data Invalida\n\n");
                        return 0;
                    }
                }else{
                    if(dia>28){
                        printf("Data Invalida\n\n");
                        return 0;
                    }
                }
            break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(dia>30){
                    printf("Data Invalida\n\n");
                    return 0;
                }
            break;
        }
    }
    else{
        printf("Mes invalido\n\n");
        return 0;
    }
    return 1;
}

//le os registos a partir do ficheiro binario
viagensStruct *lerRegistosFicheiroBinario(contadorStruct *contador, baloesStruct baloes[], listaEsperaStruct lista[], viagensStruct viagens[]){
    FILE *ficheiro;
    int contar=0;
    int i=0;
    ficheiro =fopen("data.dat", "rb");
    if(ficheiro == NULL){
        /**
        Como o ficheiro é nulo, não existe ou ocorreu algum erro na sua leitura
        o a estrutura contador vai ficar a 0
        **/
        contador->nrBaloes=0;
        contador->passageirosTransportados=0;
        contador->pListaEspera=0;
        contador->receita=0.00;
        contador->viagensRealizadas=0;
        contador->nrViagens=0;
        contador->destinoA=0;
        contador->destinoB=0;
        contador->destinoC=0;
        contador->preco = PRECO_DEFAULT;
        //elimina itens da lista de espera
        limparLista(lista, NAO_LIMPAR_MEMORIA);
    }
    else
    {
        limparLista(lista, NAO_LIMPAR_MEMORIA); //mete os elementos a 0 e inicia a null os ponteiros
        fread(contador, sizeof(contadorStruct), 1, ficheiro); //le e guarda o contador
        contar = fread(baloes, sizeof(baloesStruct), contador->nrBaloes, ficheiro);//le os baloes e guarda
        if(contar<contador->nrBaloes){//caso os baloes sejam menores que o contador de baloes
            printf("ocorreu um erro a ler do ficheiro apenas, leu %d registos\n", contar);
            contador->nrBaloes=0;
        }
        //ler lista de espera
       for(i=0; i<MAX_LISTA; i++){
            fread(&lista[i].nrBilhetes, sizeof(int), 1, ficheiro);
            lista[i].bilhetes = realloc(lista[i].bilhetes,lista[i].nrBilhetes*sizeof(bilhetesStruct));
            if(lista[i].bilhetes!=NULL){
                contar = fread(lista[i].bilhetes, sizeof(bilhetesStruct), lista[i].nrBilhetes, ficheiro);
                if(contar<lista[i].nrBilhetes){//caso os baloes sejam menores que o contador de baloes
                    printf("ocorreu um erro a ler do ficheiro, apenas leu %d registos\n", contar);
                    lista[i].nrBilhetes=0;
                }
            }else{
                printf("Ocorreu um erro a alocar a memoria!\n");
            }
        }
        //carregar dados das viagens
        viagens = realloc(viagens, contador->nrViagens*sizeof(viagensStruct));
        if(viagens!=NULL){
            contar = fread(viagens, sizeof(viagensStruct), contador->nrViagens, ficheiro);
                if(contar<contador->nrViagens){//caso os baloes sejam menores que o contador de baloes
                    printf("ocorreu um erro a ler do ficheiro, apenas leu %d registos\n", contar);
                    contador->nrViagens=0;
                }
        }else{
                printf("Ocorreu um erro a alocar a memoria!\n");
        }
        fclose(ficheiro);
    }
    return viagens;
}
//grava os registos num ficheiro binario
void gravarRegistos(contadorStruct *contador, baloesStruct baloes[], listaEsperaStruct lista[], viagensStruct viagens[]){
    char sair;
    int numelem=0, erro=0, i=0;
    FILE *ficheiro;
    do{
       //gravar dados no ficheiro
       printf("Deseja gravar as alteracoes? (S/N)\n");
       sair = lerCaracter();
       if(sair=='S'){
            ficheiro = fopen("data.dat", "wb");
            if(ficheiro==NULL){
                printf("Falha a abrir o ficheiro\n");
            }else{
                //escrever a informacao dos baloes
                fwrite(contador, sizeof(contadorStruct),1, ficheiro); //escreve o contador
                numelem=fwrite(baloes, sizeof(baloesStruct), contador->nrBaloes, ficheiro);
                if(numelem!=contador->nrBaloes){
                    printf("Ocorreu um erro a gravar os dados no ficheiro, apenas gravou %d Baloes", numelem);
                }
                //escrever a informacao da lista de espera e bilhetes
                for(i=0; i<MAX_LISTA; i++){
                    fwrite(&lista[i].nrBilhetes, sizeof(int), 1, ficheiro);//escreve o nr de bilhetes em cada lista de espera
                    numelem = fwrite(lista[i].bilhetes, sizeof(bilhetesStruct), lista[i].nrBilhetes, ficheiro);
                    if(numelem!=lista[i].nrBilhetes){//caso os baloes sejam menores que o contador de baloes
                        printf("Ocorreu um erro a gravar os dados no ficheiro, apenas gravou %d bilhetes", numelem);
                    }
                }
                //escrever dados das viagens
                numelem=fwrite(viagens, sizeof(viagensStruct), contador->nrViagens, ficheiro);
                if(numelem!=contador->nrViagens){
                    printf("Ocorreu um erro a gravar os dados no ficheiro, apenas gravou %d viagens", numelem);
                }
                //fecha o ficheiro
                erro = fclose(ficheiro);
                if(erro!=0){
                    printf("Erro %d a fechar o ficheiro", erro);
                }
            }
       }
      }while(sair!='S' && sair!='N');
}

//funcao para calcular o desconto dos bilhetes
float totalaPagar(float bilhetePreco, float desconto)
{
    float totalDesconto = (desconto*bilhetePreco);
    return bilhetePreco - totalDesconto;
}
/*
log das viagens num ficheiro de texto
*/
void logging(int nrViagem, int nrBalao, int passageiros){
    FILE *ficheiro;
    int erro=0;
    ficheiro = fopen("log.txt", "a");
    if(ficheiro==NULL){
        printf("Falha a abrir o ficheiro\n");
    }else{
        fprintf(ficheiro, "Log: Numero Viagem: %d ", nrViagem);
        fprintf(ficheiro, "Numero do balao: %d ", nrBalao);
        //fprintf(ficheiro, "Ponto de origem: %c ", pontoOrigem);
        fprintf(ficheiro, "Numero de passageiros: %d \n", passageiros);
        erro = fclose(ficheiro);
        if(erro!=0){
            printf("Erro %d no fecho do ficheiro", erro);
        }
    }
}
//devolve o indice do balao atraves da letra
int charToPos(char letra){
    switch(letra){
        case 'A':
            return POS_A;
        break;
        case 'B':
            return POS_B;
        break;
        case 'C':
            return POS_C;
        break;
    }
    return -1;
}
/***Fim Funcoes  globais ***/

/*** Funcões BALOES**/
/*
* funcao que trata dos baloes menu baloes
* Variaveis de entrada
* opcao - numero inteiro
* baloes - baloesStruct em vetor
* contador - contadorStruct por referência
*/
void menuBaloes(int opcao, baloesStruct baloes[], contadorStruct *contador){
    int posicao=-1;
    char letra;
    switch(opcao){
        case 1: //inserir baloes no vetor
            inserirBaloes(baloes, contador);
        break;
        case 2:
            //consultar dados dos baloes
            do{
                printf("\n\n\n#############################################################\n");
                printf("#_______________ MENU  BALOES -> Consultas   _______________#\n");
                printf("#_______________ 1 - Ver todos os baloes     _______________#\n");
                printf("#_______________ 2 - Escolher Balao          _______________#\n");
                printf("#_______________ 3 - Ver Baloes por posicao  _______________#\n");
                printf("#_______________ 0 - Sair                    _______________#\n");
                printf("#############################################################\n");
                printf("Escolha uma opcao: ");
                opcao = lerNumero(0,3);
                switch(opcao){
                    case 1:
                        //consultar dados de todos os baloes
                        consultarBaloes(baloes, contador->nrBaloes, '\0'); //passa o argumento \0 porque não quer filtrar pela posicao
                    break;
                    case 2:
                        //mostra a informacao de um balao
                        posicao = loopPesquisaBalaoValido(baloes, *contador);
                        infoBaloes(baloes[posicao]);
                    break;
                    case 3:
                        //consultar baloes por local A, B, C
                        letra = loopPedirPosicao("Ver Baloes nas Posicoes A, B ou C\n Escolha uma opcao:");
                        consultarBaloes(baloes, contador->nrBaloes, letra);//passa o argumento letra para filtrar as posicoes do balao
                    break;

                }
            }while(opcao!=0);
            /**fim consultar dados dos baloes**/
        break;
        case 3:
            //alterar dados dos baloes
            alterarDadosBalao(baloes, contador);
        break;
        case 4:
            //Eliminar Balao
            printf("Insira o numero do balao que pretende Eliminar:\n");
            opcao = lerNumero(1,MAXIMO_BALOES);
            posicao = procurarNumeroBalao(baloes, opcao, contador->nrBaloes);
            if(posicao!=-1){
                eliminarBaloes(baloes, contador, posicao);
            }else{
                printf("O numero do balao nao foi encontrado!\n");
            }
        break;
    }
}

/*
* funcao para inserir os baloes no vetor baloesStruct
* baloes - baloesStruct em vetor
* contador - contadorStruct por referência
*/
void inserirBaloes(baloesStruct baloes[], contadorStruct *contador){
    int numero;
    int novaposicao=contador->nrBaloes;
    if(contador->nrBaloes<MAXIMO_BALOES){
    //numero do balao
    numero = loopPesquisaBalaoinValido(baloes, contador->nrBaloes);
    baloes[novaposicao].numero=numero;
    //designacao
    printf("Insira a designacao do balao:\n");
    lerString(baloes[novaposicao].designacao, MAX_DESIGNACAO);
    baloes[novaposicao].data=loopDataBalao(baloes[novaposicao].data);
    //Lotacao maxima do balao
    printf("Insira a lotacao maxima MAX ate %d\n", LOTACAOMAXIMA);
    baloes[novaposicao].lotacaoMaxima = lerNumero(LOTACAOMINIMA, LOTACAOMAXIMA);
    //posicao do balao
    baloes[novaposicao].localInicio = loopPedirPosicao("Insira a sua posicao A, B ou C:\n");
    baloes[novaposicao].localFinal='\0';
    baloes[novaposicao].bilhetes=NULL;
    baloes[novaposicao].nrBilhetes=0;
    baloes[novaposicao].numeroPessoasTransportadas=0;
    baloes[novaposicao].Totalviagens=0;
    baloes[novaposicao].nrTuristasNobalao=0;
    infoBaloes(baloes[novaposicao]);
    printf("Balao inserido com sucesso!\n");
    contador->nrBaloes++;
    }else{
        printf("O maximo de baloes suportado e: %d\n Nao e possivel inserir mais baloes!", MAXIMO_BALOES);
    }
}

//loop para pedir a posicao do balao
char loopPedirPosicao(char msg[]){ //A, B ou C
    char letra;
    do{
        printf("%s", msg);
        letra = lerCaracter();
        if(letra!='A' && letra!='B' && letra!='C'){
            printf("Caracter invalido!\n");
        }
    }while(letra!='A' && letra!='B' && letra!='C');
return letra;
}


/*pede um numero ao utilizador até ser um numero valido e movimenta o balao para a proxia posicao,
* Variaveis de entrada
* baloes - baloesStruct em vetor
* contador - contadorStruct por referência
*/
void movimentarBaloes(baloesStruct baloes[], contadorStruct *contador){
    int posicao=-1;
    printf("\n\n\n#############################################################\n");
    printf("# Registar viagem do balao\n");
    if(contador->nrBaloes>0){
    posicao = loopPesquisaBalaoValido(baloes, *contador);
    baloes[posicao] = MovimentarBaloesManualmente(baloes[posicao], contador);
    }else{
        printf("Nao Existe baloes registados!\n\n");
    }
}

/* alterar a posicao do balao manualmente
* Variaveis de entrada
* baloes - baloesStruct em vetor
* contador - contadorStruct por referência
* localI - caracter para a posicao inicial, localF para a posicao final
*/
baloesStruct MovimentarBaloesManualmente(baloesStruct baloes, contadorStruct *contador){
    char localI=baloes.localInicio;
    switch(baloes.localInicio){
            case 'A':
                baloes.localInicio='B';
                baloes.localFinal='C';
            break;
            case 'B':
                baloes.localInicio='C';
                baloes.localFinal='A';
            break;
            case 'C':
                baloes.localInicio='A';
                baloes.localFinal='B';
            break;
    }
    printf("Balao movimentado de %c para %c\n", localI, baloes.localInicio);
    contador->viagensRealizadas++;
    baloes.Totalviagens++;
return baloes;
}

/* Alterar dados do balao
* Variaveis de entrada
*  baloes - baloesStruct em vetor
* contador - contadorStruct por referência
*/
void alterarDadosBalao(baloesStruct baloes[], contadorStruct *contador){
    int opcao, posicao=-1;
    printf("\n\n ALTERACAO DE DADOS NOS BALOES! \n \n");
    posicao = loopPesquisaBalaoValido(baloes, *contador);
    infoBaloes(baloes[posicao]); //mostra a info do balao
    do{
        printf("\n\n\n#############################################################\n");
        printf("#_______________ MENU BALAO -> Alterar Balao %d    _________#\n", baloes[posicao].numero);
        printf("#_______________ 1 - Alterar Tudo                  _________#\n");
        printf("#_______________ 2 - Alterar Designacao            _________#\n");
        printf("#_______________ 3 - Alterar data                  _________#\n");
        printf("#_______________ 4 - Alterar lotacao maxima        _________#\n");
        printf("#_______________ 5 - Alterar posicao inicial       _________#\n");
        printf("#_______________ 0 - Sair                          _________#\n");
        printf("#############################################################\n");
        printf("Escolha uma opcao: ");
        opcao = lerNumero(0,5);
        switch(opcao){
            case 1: //alterar tudo
                //elimina e cria um novo balao
                if(eliminarBaloes(baloes, contador, posicao)==1){
                    inserirBaloes(baloes, contador);
                }
            break;
            case 2: //alterar a designcao
                printf("Insira a nova designacao:\n");
                lerString(baloes[posicao].designacao, MAX_DESIGNACAO);
                infoBaloes(baloes[posicao]);
            break;
            case 3://alterar a data
                baloes[posicao].data=loopDataBalao(baloes[posicao].data);
                infoBaloes(baloes[posicao]);
            break;
            case 4://alterar a lotacao maxima
                printf("Insira a nova lotacao maxima:\n");
                baloes[posicao].lotacaoMaxima = lerNumero(LOTACAOMINIMA, LOTACAOMAXIMA);
                infoBaloes(baloes[posicao]);
            break;
            case 5: //alterar a localizaçao
                baloes[posicao].localInicio = loopPedirPosicao("Insira a sua posicao A, B ou C:\n");
                //baloes[posicao] = pedirPosicaoBalao(baloes[posicao]);
                infoBaloes(baloes[posicao]);
            break;
        }
    }while(opcao!=0);
}
/*pede a data em até que seja uma data correcta
* Variaveis de entrada
* baloes - Estrutura dos baloes
* devolve a estrutura baloes
*/
dataFabricoStruct loopDataBalao(dataFabricoStruct data){
    do{
        printf("Data do Balao\n Insira o dia:\n");
        data.dia = lerNumero(1,31);
        printf("Insira o mes:\n");
        data.mes = lerNumero(1, 12);
        printf("Insira o ano:\n");
        data.ano = lerNumero(DATA_MINIMA, ANO);
    }while(validarData(data.dia, data.mes, data.ano)==0);
return data;
}

//Listar info baloes
void infoBaloes(baloesStruct baloes){
    printf("##################################\n");
    printf("#            BALAO                \n");
    printf("# Numero: %d                      \n# Designacao: %s\n", baloes.numero, baloes.designacao);
    printf("# Data: %d/%d/%d                  \n# Lotacao Maxima: %d\n", baloes.data.dia, baloes.data.mes, baloes.data.ano, baloes.lotacaoMaxima);
    printf("# Posicao Inicial: %c             \n# Posicao Final: %c\n", baloes.localInicio, baloes.localFinal);
    printf("# Turistas transportados %d       \n# Total de Viagens: %d\n", baloes.numeroPessoasTransportadas, baloes.Totalviagens);
    printf("# turistas no balao %d            \n", baloes.nrTuristasNobalao);
    printf("__________________________________\n");
}

//consular baloes por numero
void consultarBaloes(baloesStruct baloes[], int totalBaloes, char caracter){
    int i=0;
    for(i=0; i<totalBaloes; i++){
        if(caracter==baloes[i].localInicio && (caracter=='A' || caracter=='B' || caracter=='C')){ //filtra os baloes pela posicao inicial
            infoBaloes(baloes[i]);
        }
        if(caracter=='\0'){ //devolve todos os baloes caso o caracter seja = a \0
            infoBaloes(baloes[i]);
        }
    }
    if(totalBaloes==0){ //caso nao exista baloes
        printf("Nao Existe baloes registados!\n");
    }
}
//loop pesquisar balao valido return posicao no vector
int loopPesquisaBalaoValido(baloesStruct baloes[], contadorStruct contador){ //pede um numero ao utilizador ate encontrar um balao valido e devolve a posicao
    int opcao, posicao=-1;
    printf("Insira o numero do balao:");
    do{
        opcao = lerNumero(MINIMO_BALOES, MAXIMO_BALOES);
        posicao = procurarNumeroBalao(baloes, opcao, contador.nrBaloes);
        if(posicao==-1){
           printf("O numero do balao nao foi encontrado\n Insira o numero do balao:");
        }
    }while(posicao==-1);
return posicao;
}
//loop pesquisar balao valido return numero valido
int loopPesquisaBalaoinValido(baloesStruct baloes[], int nrBaloes){ //pede um numero ao utilizador ate encontrar um numero sem balao associado
    int opcao, posicao=-1;
    printf("Insira o numero do balao:");
    do{
        opcao = lerNumero(MINIMO_BALOES, MAXIMO_BALOES);
        posicao = procurarNumeroBalao(baloes, opcao, nrBaloes);
        if(posicao!=-1){
           printf("O numero ja se encontra a ser utilizado\n Insira o numero do balao:");
        }
    }while(posicao!=-1);
return opcao;
}

//pesquisar posicao do balao devolve -1 se nao existir
int procurarNumeroBalao(baloesStruct baloes[], int numero, int totalBaloes){
    int i=0;
    for(i=0; i<totalBaloes; i++){
        if(baloes[i].numero==numero){
            return i;
        }
    }
return -1;
}
//eliminar baloes do vetor
int eliminarBaloes(baloesStruct baloes[], contadorStruct *contador, int posicao){
    char sair;
    int i=0;
    printf("Deseja Eliminar o Balao? S/N\n"); //confirma se deseja eliminar o balao selecionado
    sair = lerCaracter();
    if(sair=='S'){
        for(i=posicao; i<contador->nrBaloes-1; i++){
            baloes[i]= baloes[i+1];
        }
        contador->nrBaloes--;
        printf("Balao Eliminado com sucesso!\n\n\n");
        return 1;
    }else{
        printf("Balao Nao Eliminado!\n");
    }
    return 0;
}
/***Fim funções balões***/

/***Funcões Viagens e bilhetes***/
//funcao para ir deixando os turistas no seu destino
baloesStruct largarTuristas(baloesStruct balao, contadorStruct *contador, int nrViagem){
    int i=0;
    balao = MovimentarBaloesManualmente(balao, contador);
    logging(nrViagem, balao.numero,balao.nrTuristasNobalao);
    for(i=0; i<balao.nrBilhetes; i++){
        if(balao.bilhetes[i].destino==balao.localInicio){
            //remover turistas do balao
            balao.nrTuristasNobalao -= balao.bilhetes[i].nrPessoas;
            balao.bilhetes[i] = balao.bilhetes[i+1];
            balao.nrBilhetes--;
            i--;
        }
    }
    if(balao.nrTuristasNobalao>0){
        balao = largarTuristas(balao, contador, nrViagem);
    }
    return balao;
}
//limpa as listas de espera
void limparLista(listaEsperaStruct lista[MAX_LISTA], int limparMemoria){
    int i=0;
    for(i=0; i<MAX_LISTA; i++){
        lista[i].nrBilhetes=0;
        if(limparMemoria==LIMPAR_MEMORIA){
            free(lista[i].bilhetes);
        }
        lista[i].bilhetes=NULL;
    }
}

//funcoes para calcular o nr de viagens atraves da origem e destino do balao
int nrViagens(char localI, char localF){
    int lI, lF;
    lI = charToPos(localI);
    lF = charToPos(localF);
    switch(lI){
        case 0:
            return nrViagensDestinoFinal(lF, 3, 1, 2);
        break;
        case 1:
            return nrViagensDestinoFinal(lF, 2, 3, 1);
        break;
        case 2:
           return nrViagensDestinoFinal(lF, 1, 2, 3);
        break;
    }
    return -1;
}

int nrViagensDestinoFinal(int DF, int a, int b, int c){
    switch(DF){
    case 0:
        return a;
    break;
    case 1:
        return b;
    break;
    case 2:
        return c;
    break;
    }
return -1;
}
//mostrar os bilhetes friltrando pela posicao de origem ou destino
/*
* 1 - mostra tudo
* 2 - filtra por posição de origem
* 3 - filtra por posição de detino
*/
void mostrarBilhetesFiltro(int escolha, listaEsperaStruct lista[]){
    int i=0, j=0;
    char posicao;
    if(escolha==2 || escolha==3){
        posicao=loopPedirPosicao("Insira a posicao: ");
    }
    for(i=0; i<MAX_LISTA; i++){
        for(j=0; j<lista[i].nrBilhetes; j++){
            switch(escolha){
                case 1:
                    infoBilhetes(lista[i].bilhetes[j]);
                break;
                case 2:
                    if(lista[i].bilhetes[j].origem==posicao){
                        infoBilhetes(lista[i].bilhetes[j]);
                    }
                break;
                case 3:
                    if(lista[i].bilhetes[j].destino==posicao){
                        infoBilhetes(lista[i].bilhetes[j]);
                    }
                break;
            }
        }
    }
}
//compra bilhetes e adiciona automaticamente na sua lista de espera
void comprarBilhetes(contadorStruct *contador, listaEsperaStruct lista[]){
    int nrPessoas=0, i=0;
    bilhetesStruct bilhetesTemp;
    bilhetesStruct *bilhetesAUX;
    float totalBilheteIndividual =0;
    //pede o numero de pessoas ao utilizador para verificar se o bilhete +e idividual ou de grupo
    printf("Insira o numero de pessoas: ");
    nrPessoas = lerNumero(1, LOTACAOMAXIMA);
        bilhetesTemp.nrPessoas = nrPessoas;
        bilhetesTemp.preco=0;
        contador->pListaEspera +=nrPessoas;
        //pede a origem e o destino do balao
        bilhetesTemp.origem = loopPedirPosicao("Insira a sua posicao?\n");
        bilhetesTemp.destino = loopPedirPosicao("Insira o destino?\n");
        //bilhete em grupo
        if(nrPessoas>1){
            printf("Insira o nome do grupo: ");
            lerString(bilhetesTemp.nome, MAX_NOME);
            bilhetesTemp.grupo = GRUPO;
            for(i=0; i<nrPessoas; i++){
                bilhetesTemp.preco += contador->preco;
            }
            bilhetesTemp.preco = totalaPagar(bilhetesTemp.preco*nrViagens(bilhetesTemp.origem, bilhetesTemp.destino), DESCONTO); //preco*nr de viagens
            //mostra o total do preco dos bilhetes
            printf("Total de todos os bilhetes: %.2f\n", bilhetesTemp.preco);
            contador->receita+=bilhetesTemp.preco;
            //preco individual
            totalBilheteIndividual = totalaPagar(contador->preco*nrViagens(bilhetesTemp.origem, bilhetesTemp.destino), DESCONTO);
            //mostra o total do preco por pessoa
            printf("Preco por pessoa: %.2f\n", totalBilheteIndividual);
        }else{
            //bilhete individual
            bilhetesTemp.grupo = SEM_GRUPO;
            bilhetesTemp.preco = totalaPagar(contador->preco*nrViagens(bilhetesTemp.origem, bilhetesTemp.destino), SEM_DESCONTO);
            contador->receita+=bilhetesTemp.preco;
            printf("Total a pagar e: %.2f\n", bilhetesTemp.preco);
        }
        switch(bilhetesTemp.origem){
            case 'A':
                lista[POS_A].nrBilhetes+=1;
                contador->destinoA+=1;
                bilhetesAUX = realloc(lista[POS_A].bilhetes,lista[POS_A].nrBilhetes*sizeof(bilhetesStruct));
                if(bilhetesAUX!=NULL)
                {
                    lista[POS_A].bilhetes = bilhetesAUX;
                    lista[POS_A].bilhetes[lista[POS_A].nrBilhetes-1] = bilhetesTemp;
                }else{
                    printf("Ocorreu um erro na memoria");
                }
            break;
            case 'B':
                lista[POS_B].nrBilhetes+=1;
                contador->destinoB+=1;
                bilhetesAUX = realloc(lista[POS_B].bilhetes,lista[POS_B].nrBilhetes*sizeof(bilhetesStruct));
                if(bilhetesAUX!=NULL)
                {
                    lista[POS_B].bilhetes = bilhetesAUX;
                    lista[POS_B].bilhetes[lista[POS_B].nrBilhetes-1] = bilhetesTemp;
                }else{
                    printf("Ocorreu um erro na memoria");
                }
            break;
            case 'C':
                lista[POS_C].nrBilhetes+=1;
                contador->destinoC+=1;
                bilhetesAUX = realloc(lista[POS_C].bilhetes,lista[POS_C].nrBilhetes*sizeof(bilhetesStruct));
                if(bilhetesAUX!=NULL)
                {
                    lista[POS_C].bilhetes = bilhetesAUX;
                    lista[POS_C].bilhetes[lista[POS_C].nrBilhetes-1] = bilhetesTemp;
                }else{
                    printf("Ocorreu um erro na memoria");
                }
            break;
        }
}
//informacao dos bilehtes
void infoBilhetes(bilhetesStruct bilhete){
    printf("########################\n");
    if(bilhete.grupo==GRUPO){
        printf("# Bilhete em Grupo     \n");
        printf("# Nome do grupo: %s\n", bilhete.nome);
    }else{
        printf("# Bilhete Individual   \n");
    }
    printf("# Nr de Pessoas: %d        \n", bilhete.nrPessoas);
    printf("# Origem: %c           \n", bilhete.origem);
    printf("# Destino: %c           \n", bilhete.destino);
    printf("# Preco: %.2f\n", bilhete.preco);
}
//informacao das viagens
void infoViagens(viagensStruct viagens[], contadorStruct contador){
    int i=0;
    for(i=0; i<contador.nrViagens; i++){
        printf("########################\n");
        printf("# Nr do balao: %d     \n", viagens[i].nrBalao);
        printf("# Nr da viagem: %d     \n", viagens[i].nrViagem);
        printf("# Quantidade de turistas: %d\n", viagens[i].quantidadeTuristas);
    }
}
//inserir viagens
viagensStruct *inserirViagem(baloesStruct baloes[], viagensStruct *viagens, contadorStruct *contador, listaEsperaStruct lista[]){
    int indexBalao=-1, posLista=-1, i=0;
    viagensStruct *viagensAUX =NULL;
    bilhetesStruct *bilhetesBalaoAUX=NULL;
    indexBalao = loopPesquisaBalaoValido(baloes, *contador);
    //aumentar o contador das viagens
    contador->nrViagens++;
    viagensAUX = realloc(viagens, contador->nrViagens*sizeof(viagensStruct));
    if(viagensAUX!=NULL){
        viagens = viagensAUX;
        //adiciona o numero da viagem e o balao á estrutura das viagens
        viagens[contador->nrViagens-1].nrViagem = contador->nrViagens;
        viagens[contador->nrViagens-1].nrBalao = baloes[indexBalao].numero;
        //define-se o contador para zero porque é uma nova viagem e se não for iniciado a 0 o valor atribuido é aleatório
        viagens[contador->nrViagens-1].quantidadeTuristas=0;
        posLista = charToPos(baloes[indexBalao].localInicio); //converte a letra para o respectivo indice
        //verifica se ainda é possível adicionar mais turistas ao balao
        if(baloes[indexBalao].nrTuristasNobalao<baloes[indexBalao].lotacaoMaxima){
            for(i=0; i<lista[posLista].nrBilhetes; i++){
                if(baloes[indexBalao].nrTuristasNobalao+lista[posLista].bilhetes[i].nrPessoas<=baloes[indexBalao].lotacaoMaxima){
                    //adiciona turistas ao balao e actualiza os contadores
                    contador->pListaEspera-=lista[posLista].bilhetes[i].nrPessoas;
                    baloes[indexBalao].nrTuristasNobalao+=lista[posLista].bilhetes[i].nrPessoas;
                    viagens[contador->nrViagens-1].quantidadeTuristas+=lista[posLista].bilhetes[i].nrPessoas;
                    contador->passageirosTransportados+=lista[posLista].bilhetes[i].nrPessoas;
                    baloes[indexBalao].numeroPessoasTransportadas+=lista[posLista].bilhetes[i].nrPessoas;
                    //alocar a memoria para os bilhetes na estrutura dos baloes
                    baloes[indexBalao].nrBilhetes++;
                    bilhetesBalaoAUX = realloc(baloes[indexBalao].bilhetes, baloes[indexBalao].nrBilhetes*sizeof(bilhetesStruct));
                    if(bilhetesBalaoAUX!=NULL){
                        //copia os dados da lista de espera para o balao
                        baloes[indexBalao].bilhetes = bilhetesBalaoAUX;
                        baloes[indexBalao].bilhetes[baloes[indexBalao].nrBilhetes-1] =lista[posLista].bilhetes[i];
                    }else{
                        printf("Ocorreu um erro de memoria");
                    }
                    //remove o bilhete da lista de espera
                    lista[posLista].bilhetes[i] = lista[posLista].bilhetes[i+1];
                    lista[posLista].nrBilhetes--;
                    i--;
                }
            }
            //executa a viagem até o balao ficar vazio
            baloes[indexBalao] = largarTuristas(baloes[indexBalao], contador, viagens[contador->nrViagens-1].nrViagem);
        }
    }else{
        printf("Ocorreu um erro de memoria");
    }
return viagens;
}
/*** Fim Funcões Viagens e bilhetes***/

/***funcoes estatistica**/
void dadosEstatisticos(int submenu, baloesStruct baloes[], viagensStruct viagens[], contadorStruct contador, listaEsperaStruct lista[]){
    switch(submenu){
        case 1://numero de turistas transportados
            totalViagensBalao(baloes, contador);
        break;
        case 2://media de turistas por balao
            mediaTuristasBalao(baloes, contador);
        break;
        case 3://balao que efectuou mais viagens
            balaoMaisViagens(baloes, contador);
        break;
        case 4://percentagens de turistas por localizacao
            percentamTuristasDestino(viagens, contador);
        break;
        case 5://informacoes dos bilhetes e os maiores grupos
            estatisticaBilhetes(lista);
        break;
    }
}
//mostra a lista dos bilhetes e o maior grupo
void estatisticaBilhetes(listaEsperaStruct lista[]){
    int i=0, j=0;
    bilhetesStruct *MaiorGrupo=NULL;
    int contadorGrupos=0, grupomaior=0;
    for(i=0; i<MAX_LISTA; i++){
        for(j=0; j<lista[i].nrBilhetes; j++){
            infoBilhetes(lista[i].bilhetes[j]);
            if(lista[i].bilhetes[j].grupo==GRUPO && lista[i].bilhetes[j].nrPessoas>grupomaior){
                free(MaiorGrupo);
                contadorGrupos=1;
                MaiorGrupo = malloc(contadorGrupos * sizeof (bilhetesStruct));
                MaiorGrupo[contadorGrupos-1]=lista[i].bilhetes[j];
            }else{
                if(lista[i].bilhetes[j].nrPessoas==grupomaior && grupomaior!=0){//caso este balao tenha o mesmo numero de turistas
                    contadorGrupos++;
                    MaiorGrupo = malloc(contadorGrupos * sizeof (bilhetesStruct));
                    MaiorGrupo[contadorGrupos-1]=lista[i].bilhetes[j];
                }
            }
        }
    }
    for(i=0;i<contadorGrupos; i++){
        printf("# %s foi o maior(es) grupo(s) com %d pessoas", MaiorGrupo[i].nome, MaiorGrupo[i].nrPessoas);
    }
    free(MaiorGrupo);
}
//mostra as varias percentagens de turistas no destino A, B, C
void percentamTuristasDestino(viagensStruct viagens[], contadorStruct contador){
    if(contador.passageirosTransportados==0 || contador.destinoA==0){
       printf("Percentagem de pessoas no local A: 0%%\n");
    }else{
        printf("Percentagem de pessoas no local A: %.2f %%\n", (float)contador.destinoA/contador.passageirosTransportados*100);
    }
    if(contador.passageirosTransportados==0 || contador.destinoB==0){
        printf("Percentagem de pessoas no local B: 0%%\n");
    }else{
        printf("Percentagem de pessoas no local B: %.2f %%\n", (float)contador.destinoB/contador.passageirosTransportados*100);
    }
    if(contador.passageirosTransportados==0 || contador.destinoC==0){
        printf("Percentagem de pessoas no local C: 0%%\n");
    }else{
        printf("Percentagem de pessoas no local C: %.2f %%\n", (float)contador.destinoC/contador.passageirosTransportados*100);
    }
}
//Mostra o total de viagens para cada balao
void totalViagensBalao(baloesStruct baloes[], contadorStruct contador){
    int i=0;
    for(i=0; i<contador.nrBaloes; i++){
        printf("Total de %d viagens no balao %d\n", baloes[i].Totalviagens, baloes[i].numero);
    }
}
//media de turistas por cada balao
void mediaTuristasBalao(baloesStruct baloes[], contadorStruct contador){
    int i=0;
    if(contador.nrBaloes>1){
        for(i=0; i<contador.nrBaloes; i++){
            if(baloes[i].numeroPessoasTransportadas==0 || baloes[i].Totalviagens==0){
                printf("O balao %d teve uma media de 0%% turistas\n", i);
            }else{
                printf("O balao %d teve uma media de %.2f%% turistas\n",baloes[i].numero,
                       (float)baloes[i].numeroPessoasTransportadas/baloes[i].Totalviagens);
                }
            }
    }else{
        printf("Não existem baloes");
    }
}
//mostra o balao ou baloes com mais viagens
void balaoMaisViagens(baloesStruct baloes[], contadorStruct contador){
    int *nrBalao=NULL;
    int contadorBaloes=0;
    int maximoViagens=0, i=0;
    for(i=0; i<contador.nrBaloes; i++){
        if(baloes[i].Totalviagens>maximoViagens){
            free(nrBalao);
            contadorBaloes=1;
            nrBalao = malloc(contadorBaloes * sizeof (int));
            nrBalao[contadorBaloes-1]=baloes[i].numero;
            maximoViagens = baloes[i].Totalviagens;
        }else{
            if(baloes[i].Totalviagens==maximoViagens && maximoViagens!=0){//caso este balao tenha o mesmo numero de turistas
                contadorBaloes++;
                nrBalao = malloc(contadorBaloes * sizeof (int));
                nrBalao[contadorBaloes-1]=baloes[i].Totalviagens;
            }
        }
    }
    for(i=0;i<contadorBaloes; i++){
        printf("Balao %d, Com %d viagens", nrBalao[i], maximoViagens);
    }
    free(nrBalao);
}
/*** fim funcoes estatistica**/
