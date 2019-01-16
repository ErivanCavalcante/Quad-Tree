#ifndef PLAYER_H
#define PLAYER_H

#include "ObjetoJogo.h"

#define MAX_X 640
#define MAX_Y 480

class Player : public ObjetoJogo
{
    public:
    Player();
    virtual ~Player();

    void atualizar();
    void desenhar();

    private:
};

#endif // PLAYER_H
