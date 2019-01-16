#ifndef OBJETOJOGO_H
#define OBJETOJOGO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>

//Todo objeto eh formado por um circulo
//Cria o objeto em posicoes aleatorias
class ObjetoJogo
{
    friend class rsQuadTree;

    public:
    ObjetoJogo();
    virtual ~ObjetoJogo();

    void criarPosAleatorias();

    bool testarColisao(ObjetoJogo *outro);

    virtual void atualizar();
    virtual void desenhar();

    int pegarX();
    int pegarY();

    int pegarRaio();

    protected:
    //Posicao do objeto no mapa
    int x;
    int y;

    //Raio do objeto
    int raio;

    //Velocidade do objeto
    int velX;
    int velY;
};

#endif // OBJETOJOGO_H
