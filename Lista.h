#ifndef LISTA_H
#define LISTA_H

#include <iostream>

#include "ObjetoJogo.h"

using namespace std;

//Representa um no da lista
class ListaNo
{
    public:
    ListaNo()
    {
        noProx = NULL;
    }

    //Objeto associado ao no
    ObjetoJogo *dado;

    //Lista encadeada
    ListaNo *noProx;
};

class Lista
{
    public:
    Lista();
    ~Lista();

    //Retorna o tamanho da lista
    int tamanho();

    //Retorna se a lista esta vazia
    bool estaVazia();

    //Adiciona um objeto na lista
    bool adicionar(ObjetoJogo *obj);

    //Pega o objeto na posicao dada
    ObjetoJogo* pegarElemento(int pos);

    //Pega a posicao do Objeto
    int pegarPosElemento(ObjetoJogo *valor);

    //Pega o no Cabeca
    ListaNo* pegarTopo();

    private:
    ListaNo *noCabeca;

    int tam;
};

#endif // LISTA_H
