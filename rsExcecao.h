#ifndef RSEXCECAO_H
#define RSEXCECAO_H

#include <string>
#include <iostream>
#include "rsVariaveis.h"

using namespace std;

///Classe ustilizada no tratamento de erros.
class rsExcecao
{
    public:
    /// @param erro string que deve ser mostrada no erro.
    explicit rsExcecao( string erro );
    ~rsExcecao();

    ///Mostra o erro no console.
    rsVoid rsMostraErro();

    ///Retorna a mensagem do erro.
    string rsPegaMensagem();

    private:
    string m_erro;
};

#endif // RSEXCECAO_H
