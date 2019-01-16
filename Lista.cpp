#include "Lista.h"

Lista::Lista()
{
    tam = 0;
    noCabeca = 0;
}

Lista::~Lista()
{
    ListaNo *atual, *prox;

    atual = noCabeca;

    while(atual != NULL)
    {
        prox = atual->noProx;

        delete atual;
        atual = NULL;
        //cout << "Deletou objeto" << endl;
        atual = prox;
    }

    tam = 0;
}

int Lista::tamanho()
{
    return tam;
}

bool Lista::estaVazia()
{
    return (noCabeca == 0);
}

bool Lista::adicionar(ObjetoJogo* obj)
{
    ListaNo *novo = new ListaNo;

    if(!novo)
        return false;

    novo->dado = obj;

    //Insere na lista vazia
    if(estaVazia())
    {
        noCabeca = novo;
    }
    else
    {
        ListaNo *aux = noCabeca;

        while(aux->noProx != NULL)
            aux = aux->noProx;

        aux->noProx = novo;
    }

    tam++;
    return true;
}

ListaNo* Lista::pegarTopo()
{
    return noCabeca;
}

ObjetoJogo* Lista::pegarElemento(int pos)
{
    ListaNo *no = noCabeca;
    int n = 1;

    if(noCabeca == NULL)
        return NULL;

    while((no != NULL) && (n < pos))
    {
        no = no->noProx;
        n++;
    }

    if(no == NULL)
        return NULL;

    return no->dado;
}

int Lista::pegarPosElemento(ObjetoJogo *valor)
{
    if(noCabeca != NULL)
    {
        ListaNo *no = noCabeca;
        int n = 0;

        while(no != NULL)
        {
            if(no->dado == valor)
                return n;

            no = no->noProx;
            n++;
        }
    }

    return -1;
}
