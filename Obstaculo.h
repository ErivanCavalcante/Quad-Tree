#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "ObjetoJogo.h"


class Obstaculo : public ObjetoJogo
{
    public:
    Obstaculo();
    virtual ~Obstaculo();

    void atualizar(){}
};

#endif // OBSTACULO_H
