#ifndef RSQUADTREE_H
#define RSQUADTREE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <iostream>

#include "ObjetoJogo.h"
#include "rsVariaveis.h"

using namespace std;

class AABB
{
    public:
    rsSint32 x, y;
    rsUint16 w, h;

    AABB()
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }
    AABB( rsSint32 _x, rsSint32 _y, rsUint16 _w, rsUint16 _h )
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    ~AABB(){}

    rsBool rsEstaDentro( rsSint32 _x, rsSint32 _y )
    {
        if( _x > x + w )     return false;
        if( _x < x )         return false;
        if( _y > y + h )     return false;
        if( _y < y )         return false;

        //ESTA COLIDINDO
        return true;
    }

    rsBool rsColide( AABB obj )
    {
        if( obj.x > x + w )            return false;
        if( obj.x + obj.w < x )        return false;
        if( obj.y > y + h )            return false;
        if( obj.y + obj.h < y )        return false;

        //ESTA COLIDINDO
        return true;
    }
};

typedef vector< ObjetoJogo* > VetorObj;

class rsQuadTree
{
    public:
    rsQuadTree();
    rsQuadTree( rsSint32 _x, rsSint32 _y, rsUint16 _largura, rsUint16 _altura );
    ~rsQuadTree();

    rsVoid      rsCriaQuadTree( rsSint32 _x, rsSint32 _y, rsUint16 _largura, rsUint16 _altura );

    rsBool      rsAdicionaObjeto( ObjetoJogo *objeto );
    VetorObj    rsPegaPotencialColisao( rsSint32 x, rsSint32 y, rsUint16 lar, rsUint16 alt );

    rsVoid      rsDesenha();

    rsVoid      rsDeletaTudo(); //LIMPA A QUADTREE

    private:

    AABB        m_boundingBox;

    //qtd max de objetos antes d s dividir
    const rsUint16    m_iMaxObjetos;

    //Usado quando o objeto nao cabe totalmente no no
    rsQuadTree* PAI;

    rsQuadTree* NORTE;
    rsQuadTree* SUL;
    rsQuadTree* LESTE;
    rsQuadTree* OESTE;

    //LISTA DE OBJETOS
    VetorObj    m_stlObjetos;

    //Subdivide o no quando chega a capacidade maxima
    rsVoid      rsSubdivide();
};

#endif // QUADTREE_H
