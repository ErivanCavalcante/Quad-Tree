#ifndef RSTECLADO_H
#define RSTECLADO_H

#include "AllegroIncludes.hpp"
#include <iostream>
#include "rsClasseSingleton.h"
#include "rsVariaveis.h"
#include "rsExcecao.h"

using namespace std;

///CLASSE SINGLETON
class rsTeclado : public rsClasseSingleton<rsTeclado>
{
    public:
    rsTeclado();
    virtual ~rsTeclado(){}

    ///Checa se a tecla passada esta pressionada.
    ///A função so retorna true uma vez ate que a tecla seja solta novamente.
    rsBool      rsChecaTeclaPressionada(rsSint32 tecla);

    ///Checa se a tecla passada esta pressionada.
    rsBool      rsChecaTecla(rsSint32 tecla);

    ///Checa se a tecla passada esta solta.
    rsBool      rsChecaTeclaSolta(rsSint32 tecla);

    ///Atualiza as entraadas do teclado.
    rsVoid      rsAtualizaTeclado();

    private:
    rsBool      m_bPodeApertar;
    rsSint32    m_iTeclaPressionada;

    ALLEGRO_KEYBOARD_STATE m_alEstado;
};

#define Teclado rsTeclado::rsPegaInstanciaPtr()

#endif // IMPUT_H
