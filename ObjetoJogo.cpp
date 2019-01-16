#include "ObjetoJogo.h"

ObjetoJogo::ObjetoJogo()
{
    criarPosAleatorias();
}

ObjetoJogo::~ObjetoJogo()
{
    //dtor
}

void ObjetoJogo::criarPosAleatorias()
{
    x = rand() % 640;
    y = rand() % 480;

    velX = 4 * (rand() % 2 == 0)?1 : -1;
    velY = 4 * (rand() % 2 == 0)?1 : -1;

    raio = 10;
}

void ObjetoJogo::atualizar()
{
    //Atualiza a posicao
    x += velX;
    y += velY;
}

void ObjetoJogo::desenhar()
{
    al_draw_filled_circle(x, y, raio, al_map_rgb(255, 0, 0));
}

bool ObjetoJogo::testarColisao(ObjetoJogo* outro)
{
    if( outro->x + outro->raio < x - raio ) return false;
    if( outro->y + outro->raio < y - raio ) return false;
    if( outro->x - outro->raio > x + raio ) return false;
    if( outro->y - outro->raio > y + raio ) return false;

    /*
    int dx = outro->x - x;
    int dy = outro->y - y;
    int dist = outro->raio - raio;

    if( (dx * dx) + (dy + dy) < (dist * dist) )
        return true;
    else
        return false;
    */

    return true;
}

int ObjetoJogo::pegarX()
{
    return x;
}

int ObjetoJogo::pegarY()
{
    return y;
}

int ObjetoJogo::pegarRaio()
{
    return raio;
}
