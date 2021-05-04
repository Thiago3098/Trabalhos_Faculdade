#include "mapa.h"

 void inicia_mapa(mapa *mp){
    mp->total = 0; //quantidade de palavras no mapa.
    mp->blocos = 1; //quantidade de arrays de 10 ponteiros(bloco).
    mp->lista = malloc(10 * sizeof(item*)); //alocando primeiro bloco.
 }

 int tamanho_mapa(mapa *mp){ //funcao para mostrar tamanho do mapa.
    return mp->total; //se mapa nao for igual a VAZIO retornar a variavel total.
 }

 int tot_palavras(mapa *mp){
    int i, total = 0;
    for(i = 0; i < mp->total; i++){
        total += mp->lista[i]->cont;
    }
    return total;
 }

 void insere_termo(mapa *mp, char *s){ //funcao para colocar as palavras dentro do mapa.

        if((mp->total >= 10) && (mp->total % 10 == 0)){ //laco para testar se ainda ha espaco dentro do bloco.
            mp->lista = realloc(mp->lista, (mp->total + 10) * sizeof(item)); //realoca mais 1 bloco.
            mp->blocos++; //incrementa quantidade de blocos.
        }

        mp->lista[mp->total] = ( item*) malloc(1 * sizeof(item));
        mp->lista[mp->total]->cont = 1;
        mp->lista[mp->total]->termo = malloc(strlen((s) + 1) * sizeof(char)); //alocando o tamanho certo para termo.
        strcpy(mp->lista[mp->total]->termo, s); //copiando palavra analisada para dentro de termo
        mp->total++; //incrementado total de palavras no mapa.
 }

 int incrementa(mapa *mp, char *s){ //funcao para incrementar o contador do termo.
    int i;
    if(mp->total == 0){
        return 1;
    }
    for(i = 0;i < mp->total; i++){
        if(strcmp(mp->lista[i]->termo, s) == 0){ //percorrendo a lista para achar o termo.
            mp->lista[i]->cont++; //incrementa cont.
            return 0; //se achou retornar 0.
        }
    }
    return 1; //se nao achou retornar 1.
 }

 int escreve_cont(mapa *mp, char *s, int c){ //funcao para alterar o contador de uma palavra.
    int i;
    if(mp->total == 0){ //se o mapa estiver vazio retornar 1.
       return 1;
    }
        for(i = 0;i <= mp->total; i++){ //percorrendo o vetor de ponteiros para encontrar a palvra.
            if(strcmp(mp->lista[i]->termo, s) == 0){
                mp->lista[i]->cont = c; //se achou o contador da palavra recebe o numero desejado pelo usuario.
                return mp->lista[i]->cont;
            }
        }
    return 1;
 }

 int le_contador(mapa *mp, char *s){ //funcao responsavel por devolver o contador de uma determinada palavra.
    int i;
    for(i = 0; i < mp->total; i++){ //percorrendo o vetor de ponteiros.
        if(strcmp(mp->lista[i]->termo, s) == 0){
            return mp->lista[i]->cont; //retornar contador da palavra.
        }
    }
    return 0;
 }

 void le_termo(mapa *mp, int i, char *t, int *c){ //funcao para buscar uma palavra, se achar retornar contador e indice onde ela ta.
    t = mp->lista[i]->termo;
    *c = mp->lista[i]->cont; //se achou retornando as suas informacoes.
 }

 void remove_termo(mapa *mp, char *s){ //funcao para "apagar" uma palavra do mapa.
    int i;
    for(i = 0;i < mp->total; i++){ //percorre o vetor para encontrar o termo e remove-lo.
        if(strcmp(mp->lista[i]->termo, s) == 0){
            free(mp->lista[i]->termo); //libera a palavra.
            free(mp->lista[i]); //libera o indice no qual ela se encontra dentro do array de ponteiros.
            mp->lista[i]->cont = 0;
        }
    }
 }

 void libera_mapa(mapa *mp){ //liberando mapa.
    int i;
    for(i = 0; i < mp->total; i++){ //free em cada lista do mapa.
        free(mp->lista[i]); //free na palavra.
    }
    free(mp); // free no mapa.
 }

 void ordena_map(mapa *mp){ //ordenando o mapa.
     int i, j, *aux;
     for(i = 0; i < mp->total; i++){
        for(j = i + 1; j < mp->total; j++){
            if(mp->lista[i]->cont < mp->lista[j]->cont){ //se a posicao i for menor que a j, a variavel aux rece o ponteiro da i.
                aux = mp->lista[i];
                mp->lista[i] = mp->lista[j]; //e muda de posicao.
                mp->lista[j] = aux;
            }
        }
     }
 }

 void minusc(char *s){ //funcao para transformas todos os caracteres de uma palavra em minusculo.
    int i;
        for(i = 0; i < strlen(s); i++){
            s[i] = (char) tolower(s[i]); //fazendo todos ficarem minusculo.
        }
 }

  void remov_pont(char *s){ //funcao para retirar a pontuacao ao fim de uma palavra.
    char pont[] = {'.',',',';',':','!','?'}; //vetor  de pontuacoes.
    int len, i;
    len = strlen(s); //variavel para armazenar o tamanho da palavra.
    for(i = 0; i < strlen(pont); i++){
        if(s[len-1] == pont[i]){ //se essa ultima posicao da palavra for igual a uma pont do vetor.
            s[len-1] = '\0'; //a ultima posicao do veotr passa a ser o /0 pra excluir a pontuacao.
        }
    }
 }
