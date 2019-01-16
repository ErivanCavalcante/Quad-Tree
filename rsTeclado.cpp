#include "rsTeclado.h"

rsTeclado::rsTeclado()
{
    m_bPodeApertar      = true;
    m_iTeclaPressionada = -1;
}

rsVoid rsTeclado::rsAtualizaTeclado()
{
    al_get_keyboard_state( &m_alEstado );
}

rsBool rsTeclado::rsChecaTeclaPressionada( rsSint32 tecla )
{
    if( rsChecaTecla( tecla ) && m_bPodeApertar )
    {
        m_iTeclaPressionada = tecla;
        m_bPodeApertar      = false;
        return true;
    }

    if( m_iTeclaPressionada > -1 )
    {
        if( rsChecaTeclaSolta( m_iTeclaPressionada ) && !m_bPodeApertar )
        {
            m_iTeclaPressionada = -1;
            m_bPodeApertar      = true;
        }
    }

    return false;
}

rsBool rsTeclado::rsChecaTecla( rsSint32 tecla )
{
    assert( tecla >= 0 );

    return ( al_key_down( &m_alEstado, tecla ) );
}

rsBool rsTeclado::rsChecaTeclaSolta( rsSint32 tecla )
{
    assert( tecla >= 0 );

    return ( !al_key_down( &m_alEstado, tecla ) );
}


