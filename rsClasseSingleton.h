#ifndef RSCLASSESINGLETON_H
#define RSCLASSESINGLETON_H

#include <cassert>

template< class T >
///Classe base para todas as classes singletons.
class rsClasseSingleton
{
    protected:
    static T* m_pInstancia;

    public:
    rsClasseSingleton()
    {
        assert( !m_pInstancia );
        int offset = ( int )( T* )1 - ( int )( rsClasseSingleton < T >* )( T* )1;
        m_pInstancia = ( T* )( ( int )this + offset );
    }
    virtual ~rsClasseSingleton()
    {
        assert( m_pInstancia );
        m_pInstancia = 0;
    }

    ///Retorna uma referencia para instancia da classe singleton.
    static T& rsPegaInstancia()
    {
        assert( m_pInstancia );
        return ( *m_pInstancia );
    }

    ///Retorna um ponteiro para instancia da classe singleton.
    static T* rsPegaInstanciaPtr()
    {
        assert( m_pInstancia );
        return ( m_pInstancia );
    }
};

template< class T >
T* rsClasseSingleton < T >::m_pInstancia = 0;

#endif // CLASSESINGLETON_H
