#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

    int main(){

    setlocale(LC_ALL, "Portuguese");
    int op, i = 0, cont,flag = 0, menor, maior, opcao = 1;
    char nome_arq[20];
    char palavra[30];
    char resp[1]= "s";
    FILE *arquivo, *cache;
    mapa mp;

    do{     //Looping menu
        if(flag == 0){ //flag para saber se o usuario ja digitou um arquivo.
            do{ //se nao digitou forca ele a entrar na op 1 para digitar um diretorio.
            printf("Menu: caso seja o seu primeiro acesso, por favor selecionar opção 1.\n1- Ler Arquivo txt.\n2- Exibir ranking completo.\n3- Exibir intervalo de ranking.\n4- Buscar palavra.\n5- Opções.\n6- Sair.\n\nInsira a opcões desejada:");
            scanf("%i", &op);
                if(op != 1){ //se op for diferente de 1, pedir pro usuario entrar na primeira opcao.
                    printf("\n\nDesculpe no primeiro acesso só é permitido entrar na opção 1. \nTENTE NOVAMENTE\n\n");
                    system("pause");
                    system("cls");
                }
            }while(op != 1); //ate ele digitar 1.

            }else{
                printf("Menu:\n1- Ler Arquivo txt.\n2- Exibir ranking completo.\n3- Exibir intervalo de ranking.\n4- Buscar palavra.\n5- Opções.\n6- Sair.\n\nInsira a opcões desejada:");
                scanf("%i", &op); //menu sem ciclo while, com flag = 1;
            }

        system("cls");
        switch(op){
            case 1:
                cache = fopen("cache", "rb"); //Abrindo o arquivo de cache no modo leitura.
                fread(&opcao, sizeof(int), 1, cache); //lendo e armazendo em opcao.
                fclose(cache); //fecha arquivo.

                do{

                if(flag == 1){
                    libera_mapa(&mp);// na segunda vez que o usuario entrar na opcao de ler um arquivo, DA FREE NO MAPA ANTERIOR.
                }

                printf("1 - Ler Arquivo\ndigite o nome do arquivo(exemplo.txt):"); //lendo nome do arquivo a ser aberto.
                scanf("%s", nome_arq);

                arquivo = fopen(nome_arq, "r"); //abre arquivo no modo read.
                if(arquivo == NULL){
                    printf("ARQUIVO NÃO ENCONTRADO, TENTE NOVAMENTE.\n\n"); // se o ponteiro for NULL, arquivo nao foi encontrado.
                    system("pause");
                    system("cls");
                }
                }while(arquivo == NULL);

                inicia_mapa(&mp); //iniciando o mapa com 1 bloco.
                printf("\nAtualmente a QTD minima de caracteres:%i", opcao);
                while(fscanf(arquivo,"%s ", palavra) != EOF){ //lendo palavra do arquivo.
                    remov_pont(palavra); //removendo as pontuacoes da palavra.
                    minusc(palavra); //colocando todas as letras em minuculos.
                    if(strlen(palavra) >= opcao){
                        if(incrementa(&mp, palavra) == 1){ //caso incrementa me retoner 1, eu chamo insere_termo.
                            insere_termo(&mp, palavra); //inserindo palavra nova no mapa.
                            ordena_map(&mp); //ordenando o mapa.
                        }
                    }
                }
                ordena_map(&mp);
                printf("\nTotal de itens alocados no mapa:%i\nTotal de palavras dentro do arquivo:%i\n\nI   palavra  QTD\n\n", tamanho_mapa(&mp), tot_palavras(&mp));

                for(i = 0; i < (mp.total / 2); i++){ //coloquei o ciclo "for" para até metade do mapa para fazer uma desmontração dos 5 primeiros indices do mapa.
                    le_termo(&mp, i, mp.lista[i]->termo, &cont); //le cada termo do mapa e retonar o indice, a palavra e o contador respectivo dela.
                    printf("%i - %s - %2i\n", i, mp.lista[i]->termo, cont);
                }
                fclose(arquivo); //fecha arquivo.

                system("pause");
                system("cls");
                flag = 1;
            break;
            case 2:
                printf("Atualmente a QTD minima de caracteres:%i\n", opcao); //Mostrando quanto esta o minimo de caracteres
                printf("2 - ranking completo -- arquivo:%s\n\nTotal de itens alocados no mapa:%i\nTotal de palavras dentro do arquivo:%i\n\nI   PALAVRA    QTD\n", nome_arq, tamanho_mapa(&mp), tot_palavras(&mp));
                for(i = 0; i < tamanho_mapa(&mp); i++){
                    le_termo(&mp, i, mp.lista[i]->termo, &cont); //le todas as palavras e mostra o ranking completo.
                    printf("%i - %s - %2i\n", i, mp.lista[i]->termo, cont);
                }
                system("\npause");
                system("cls");
            break;
            case 3:
                printf("Atualmente a QTD minima de caracteres:%i\n", opcao); //mostrando quanto esta o minimo de caracter
                printf("3 - Intervalo de Ranking -- arquivo:%s\n\nTotal de itens alocados no mapa:%i\nTotal de palavras dentro do arquivo:%i\n\nI  PALAVRA  QTD\n", nome_arq, tamanho_mapa(&mp), tot_palavras(&mp));
                printf("Digite QTD MAX:");
                scanf("%i", &maior);

                printf("Digite QTD MIN:");
                scanf("%i", &menor);

                for(i = 0; i < tamanho_mapa(&mp); i++){
                    if((le_contador(&mp, mp.lista[i]->termo) <= maior) && (le_contador(&mp, mp.lista[i]->termo) >= menor)){
                        printf("%i - %s - %2i\n", i, mp.lista[i]->termo, mp.lista[i]->cont);
                    }
                }
                system("\npause");
                system("cls");
            break;
            case 4:
                printf("4 -Buscar palavra -- Arquivo:%s", nome_arq); //busca palavra
                do{
                printf("\ndigite a palavra:");
                scanf("%s", palavra);

                    if(le_contador(&mp, palavra) != 0){ //se a palavra tem no mapa retonar o contador e a palavra.
                        printf("\nPALAVRA ENCONTRADA:%s   %i\n", palavra, le_contador(&mp, palavra));
                    }else{
                        printf("\nPALAVRA NÃO EXISTE NO MAPA.");
                    }
                    fflush(stdin);
                    printf("\nDeseja buscar outra palavra? <y/n>:");
                    scanf("%c", resp);
                    while((resp[0] != 'n') && (resp[0] != 'N') && (resp[0] != 'y') && (resp[0] != 'Y')){
                        printf("TENTE NOVAMENTE y = quer fazer outra busca || n = Não quer fazer outra busca.");
                        printf("\nDeseja buscar outra palavra? <y/n>:");
                        fflush(stdin);
                        scanf("%c", resp);
                    }
                  }while((resp[0] != 'n') && (resp[0] != 'N'));
                system("pause");
                system("cls");
            break;
            case 5:
                printf("5 -Opções\nDigite o numero de caracteres a se considerar:");
                scanf("%i", &opcao); //pego a opcao que o usuario quer.

                inicia_mapa(&mp); //inicia mapa do 0.

                arquivo = fopen(nome_arq, "r"); //abre o arquivo denovo.

                while(fscanf(arquivo,"%s ", palavra) != EOF){ //lendo palavra do arquivo.
                    remov_pont(palavra); //removendo as pontuacoes da palavra.
                    minusc(palavra); //colocando todas as letras em minuculos.
                        if(strlen(palavra) >= opcao){
                            if(incrementa(&mp, palavra) == 1){ //caso incrementa me retoner 1, eu chamo insere_termo.
                                insere_termo(&mp, palavra); //inserindo palavra nova no mapa.
                                ordena_map(&mp); //ordenando o mapa a cada insercao.
                        }
                    }
                }

                fclose(arquivo); //fechando arquivo denovo.

                cache = fopen("cache", "wb"); //abre arquivo cache e escreve o nova opcao nele, para que na prox abertura do progama esteja guardado.
                fwrite(&opcao, sizeof(int), 1,cache); //escreve no arquivo.
                fclose(cache);

                printf("Total de itens dentro do mapa atualizado:%i\nTotal de palavras dentro do arquivo atualizado:%i\n", tamanho_mapa(&mp), tot_palavras(&mp));
                system("pause");
                system("cls");
                ordena_map(&mp);
            break;
            case 6:
                printf("S A I N D O\n\n");
            break;
            default:
                printf("OPÇÃO INVALIDA\nDigite numeros de 1 a 6 e pressione enter para navegar na interface\nREINIE O PROGRAMA.");
                exit(0);
        }
    }while(op != 6);
    libera_mapa(&mp); //saindo e liberando o mapa atual.
    system("pause");
    return 0;
}
