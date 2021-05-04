#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

    typedef struct _item
    {
        int cont; //contador de cada palavra
        char *termo; //palavra
    } item;

    typedef struct _mapa
    {
        int total; //numero de itens no mapa
        int blocos; //blocos alocados
        item **lista; //array de ponteiros
    } mapa;

    void inicia_mapa(mapa *mp);
    void insere_termo(mapa *mp, char *s);
    int incrementa(mapa *mp, char *s);
    int escreve_cont(mapa *mp, char *s, int c);
    int le_contador(mapa *mp, char *s);
    void remove_termo(mapa *mp, char *s);
    void libera_mapa(mapa *mp);
    int tamanho_mapa(mapa *mp);
    void le_termo(mapa *mp, int i, char *t, int *c);
    void ordena_map(mapa *mp);
    int tot_palavras(mapa *mp);
    void minusc(char *s);
    void remov_pont(char *s);
