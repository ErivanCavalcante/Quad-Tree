#include "rsQuadTree.h"

rsQuadTree::rsQuadTree() : m_iMaxObjetos(4)
{
    PAI = NORTE = LESTE = SUL = OESTE = 0;
}

rsQuadTree::rsQuadTree( rsSint32 _x, rsSint32 _y, rsUint16 _largura, rsUint16 _altura ) : rsQuadTree()
{
    m_boundingBox.x = _x;
    m_boundingBox.y = _y;
    m_boundingBox.w = _largura;
    m_boundingBox.h = _altura;
}

rsQuadTree::~rsQuadTree()
{
    rsDeletaTudo();
}

rsVoid rsQuadTree::rsDeletaTudo()
{
    //Deleta recursivamente

    m_stlObjetos.clear();

    PAI = NULL;

    if( NORTE )
    {
        NORTE->rsDeletaTudo();

        delete NORTE;
        NORTE = NULL;
    }
    if( SUL )
    {
        SUL->rsDeletaTudo();

        delete SUL;
        SUL = NULL;
    }
    if( LESTE )
    {
        LESTE->rsDeletaTudo();

        delete LESTE;
        LESTE = NULL;
    }
    if( OESTE )
    {
        OESTE->rsDeletaTudo();

        delete OESTE;
        OESTE = NULL;
    }
}

rsVoid rsQuadTree::rsCriaQuadTree( rsSint32 _x, rsSint32 _y, rsUint16 _largura, rsUint16 _altura )
{
    //Deleta tudo o q tinha antes e reconstroi
    rsDeletaTudo();

    m_boundingBox.x = _x;
    m_boundingBox.y = _y;
    m_boundingBox.w = _largura;
    m_boundingBox.h = _altura;
}

rsVoid rsQuadTree::rsSubdivide()
{
    rsSint32 &x = m_boundingBox.x;
    rsSint32 &y = m_boundingBox.y;
    rsUint16 &w = m_boundingBox.w;
    rsUint16 &h = m_boundingBox.h;

    //Cria as quads
    NORTE = new rsQuadTree( x, y, w / 2, h / 2 ); //quad1
	LESTE = new rsQuadTree( x + ( w / 2 ), y, w / 2, h / 2 ); //quad2
	SUL   = new rsQuadTree( x, y + ( h / 2 ), w / 2, h / 2 ); //quad3
	OESTE = new rsQuadTree( x + ( w / 2 ), y + ( h / 2 ), w / 2, h / 2 ); //quad4

	//Seta os pais
	NORTE->PAI = LESTE->PAI = SUL->PAI = OESTE->PAI = this;
}

rsBool rsQuadTree::rsAdicionaObjeto( ObjetoJogo *objeto )
{
    //testa se esta dentro da quad tree
    //se naum esta dento da quad tree naum adiciona
    if( !m_boundingBox.rsEstaDentro( objeto->x, objeto->y ) )
        return false;

    //se tem espaço nesse no add aqui
    if( m_stlObjetos.size() < m_iMaxObjetos )
    {
        m_stlObjetos.push_back( objeto );
        return true;
    }

    //se naum subidivide e add em algum
    if( !NORTE )
        rsSubdivide();

    if( NORTE->rsAdicionaObjeto( objeto ) ) return true;
    if( OESTE->rsAdicionaObjeto( objeto ) ) return true;
    if( SUL->rsAdicionaObjeto( objeto ) )   return true;
    if( LESTE->rsAdicionaObjeto( objeto ) ) return true;

    //Se nao conseguiu colocar em nenhum entao coloca no pai
    if(PAI)
    {
        PAI->m_stlObjetos.push_back( objeto );
        return true;
    }

    //por garantia
    return false;
}

VetorObj rsQuadTree::rsPegaPotencialColisao( rsSint32 x, rsSint32 y, rsUint16 lar, rsUint16 alt )
{
	VetorObj returnObjects, childReturnObjects;

    AABB objeto( x, y, lar, alt );

	//se nao esta dentro da quad tree entao sai
	//Condicao de saida
	if( !m_boundingBox.rsColide( objeto ) )
        return returnObjects;

    //Adiciona os objetos desse no ao retorno
    returnObjects.insert( returnObjects.end(), m_stlObjetos.begin(), m_stlObjetos.end() );

    /*
    //checa os objetos desse no
    for( rsUint16 i = 0; i < m_stlObjetos.size(); ++i )
    {
        if( objeto.rsEstaDentro( m_stlObjetos[i]->x, m_stlObjetos[i]->y ) )
            returnObjects.push_back( m_stlObjetos[i] );
    }
    */

    //se naum tem filhos termina aqui
    if( !NORTE )
        return returnObjects;

    //se naum add os objetos dos filhos
    childReturnObjects = NORTE->rsPegaPotencialColisao( x, y, lar, alt );
    returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );

    childReturnObjects = OESTE->rsPegaPotencialColisao( x, y, lar, alt );
    returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );

    childReturnObjects = SUL->rsPegaPotencialColisao( x, y, lar, alt );
    returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );

    childReturnObjects = LESTE->rsPegaPotencialColisao( x, y, lar, alt );
    returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );

	return returnObjects;
}

rsVoid rsQuadTree::rsDesenha()
{
    al_draw_rectangle( m_boundingBox.x, m_boundingBox.y,
                       m_boundingBox.x + m_boundingBox.w, m_boundingBox.y + m_boundingBox.h,
                       al_map_rgb(0, 0, 0), 4 );

    if( NORTE ) NORTE->rsDesenha();
    if( SUL )   SUL->rsDesenha();
    if( LESTE ) LESTE->rsDesenha();
    if( OESTE ) OESTE->rsDesenha();
}

