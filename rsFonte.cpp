/*
 * rsFonte.cpp
 *
 *  Created on: 10 de set de 2016
 *      Author: Erivan
 */

#include "rsFonte.h"

string rsFonte::nomeDiretorio = "";

rsFonte::rsFonte( rsConstChar *nome, rsUint16 tam )
{
	m_iTamanho = tam;
	//zera a fonte
	mFonte = NULL;

	assert(nome);

	try
	{
		rsCarregaFonteTTF( nome );
	}
	catch( rsExcecao &ex )
	{
		throw ex;
	}
}

/*
rsFonte::rsFonte( rsImagem *img, rsUint8 ranMin, rsUint8 ranMax, rsUint16 tam )
{
	m_iTamanho = tam;
	//zera a fonte
	mFonte = NULL;

	assert(img);

	try
	{
		rsCarregaFonteIMG( img, ranMin, ranMax );
	}
	catch( rsExcecao &ex )
	{
		throw ex;
	}
}
*/

rsFonte::~rsFonte()
{
	rsDeletaTudo();
}

rsVoid rsFonte::rsDeletaTudo()
{
	if(!mFonte)
		return;

	///LIBERA A MEMORIA
	al_destroy_font( mFonte );
	mFonte = NULL;
}

rsBool rsFonte::rsCarregaFonteTTF( rsConstChar *nome )
{
    stringstream realNome;
    realNome << rsFonte::nomeDiretorio << nome;

    mFonte = al_load_font( realNome.str().c_str(), m_iTamanho, 0 );
    if( !mFonte )
    {
        throw rsExcecao( "Nao foi possivel carregar a fonte." );
        return false;
    }

    return true;
}

/*
rsBool rsFonte::rsCarregaFonteIMG( rsImagem *img, rsUint8 ranMin, rsUint8 ranMax )
{
    ///intervalo q importa { 32, 126 }
    rsSint32 ranges[] = { ranMin, ranMax };

    mFonte = al_grab_font_from_bitmap( img->rsPegaBitmap(), 1, ranges );
    if( !mFonte )
    {
        ///ERRO
        throw rsExcecao( "Nao foi possivel carregar a fonte." );
        return false;
    }

    return true;
}
*/

ALLEGRO_FONT* rsFonte::rsPegaFonte() const
{
	return mFonte;
}
