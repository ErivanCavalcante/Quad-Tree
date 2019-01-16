/*
 * rsFonte.h
 *
 *  Created on: 10 de set de 2016
 *      Author: Erivan
 */

#ifndef RAISESPACE_NUCLEO_RSFONTE_H_
#define RAISESPACE_NUCLEO_RSFONTE_H_

#include <string>
#include <sstream>
#include "AllegroIncludes.hpp"
#include "rsVariaveis.h"
//#include "rsImagem.h"
#include "rsExcecao.h"

using namespace std;

///Classe que representa uma fonte no jogo.
class rsFonte
{
	public:
	//diretorio de onde se quer carregar p ficar mais facil
	/// \var caminho da pasta que contem todas as fontes.
	static string 	nomeDiretorio;


	//Fonte ttf
	/// @param nome caminho do arquivo em disco.
	/// @param tam tamanho da fonte.
	explicit rsFonte( rsConstChar *nome, rsUint16 tam = 12 );

	/// @param img ponteiro para uma imagem ja carregada.
	/// @param ranMin caracter minimo da tablea ascii.
	/// @param ranMax caracter maximo da tabela ascii.
	/// @param tam tamanho da fonte.
	//explicit rsFonte( rsImagem *img, rsUint8 ranMin = 32, rsUint8 ranMax = 126, rsUint16 tam = 12 );
	virtual ~rsFonte();

	///Retorna uma fonte com o apelido dado.
	ALLEGRO_FONT*   rsPegaFonte() const;

	///Deleta todos os dados alocados pela classe.
	rsVoid          rsDeletaTudo();

	private:
	rsUint16        m_iTamanho;
	ALLEGRO_FONT*   mFonte;

	//Carrega fonte do disco.
	rsBool          rsCarregaFonteTTF( rsConstChar *nome );
	//Carrega fonte do disco.
	//rsBool          rsCarregaFonteIMG( rsImagem *img, rsUint8 ranMin, rsUint8 ranMax );
};

#endif /* RAISESPACE_NUCLEO_RSFONTE_H_ */
