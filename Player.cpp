#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::atualizar()
{
    if(x < 0 || x > MAX_X)
        velX *= -1;
    if(y < 0 || y > MAX_Y)
        velY *= -1;

    ObjetoJogo::atualizar();
}

void Player::desenhar()
{
    al_draw_filled_circle(x, y, raio, al_map_rgb(0, 255, 0));
}
