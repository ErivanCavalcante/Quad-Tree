#include "rsExcecao.h"

rsExcecao::rsExcecao( string erro )
{
    m_erro = erro;
}

rsExcecao::~rsExcecao()
{
}

rsVoid rsExcecao::rsMostraErro()
{
    cout << m_erro << endl << endl;
}

string rsExcecao::rsPegaMensagem()
{
    return m_erro;
}
