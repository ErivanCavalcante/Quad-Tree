#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Lista.h"
#include "Obstaculo.h"
#include "Player.h"
#include "rsExcecao.h"
#include "rsQuadTree.h"
#include "rsFonte.h"
#include "rsTeclado.h"

using namespace std;

//Variaveis Global

//Variaveis da janela e dos eventos
ALLEGRO_DISPLAY *janela = 0;
ALLEGRO_EVENT_QUEUE *eventos = 0;

//Variavel que controla o teclado
rsTeclado teclado;

//Cria o player
Player *player = 0;

//Cria a lista de obstaculos
Lista obstaculos;

//Cria a quadtree
rsQuadTree quadTree;

//Vetor de retorno das potenciais colisoes
VetorObj potColisoes;

//Controla o loop do jogo
bool sair = false;

//Inicia os recursos da biblioteca grafica
void iniciarAllegro()
{
    //Inicializa a allegro
    if( !al_init() )
        throw rsExcecao( "Erro ao Iniciar Allegro." );

    if( !al_install_keyboard() )
		throw rsExcecao( "Erro ao Iniciar Allegro." );

    if( !al_init_primitives_addon() )
        throw rsExcecao( "Erro ao Iniciar as Primitivas." );

    al_init_font_addon();

    if( !al_init_ttf_addon() )
        throw rsExcecao( "Erro ao Iniciar as Fontes TTF." );
}

//Cria a janela
void criarJanela()
{
    janela = al_create_display(850, 480);
    eventos = al_create_event_queue();

    al_register_event_source(eventos, al_get_display_event_source(janela));
}

//Cria todos os objetos e os coloca na quadtree
void criarObjetos()
{
    //Cria o player
    player = new Player();

    //Loop para criacao dos 200 obstaculos
    for(int i = 0; i < 200; ++i)
    {
        //Cria o obstaculo
        Obstaculo *obj = new Obstaculo;

        //Falta de meoriia
        if(!obj)
            continue;

        //Adiciona na lista
        obstaculos.adicionar(obj);

        //Adiciona na Quadtree
        quadTree.rsAdicionaObjeto(obj);
    }
}

//Desenha as informaçoes na tela
void desenharInformacoes(rsFonte &fonte)
{
    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 0), 650, 10
                         , ALLEGRO_ALIGN_LEFT, "INFO");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 35
                 , ALLEGRO_ALIGN_LEFT, "Num de Obstaculos:");

    al_draw_textf(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 50
                 , ALLEGRO_ALIGN_LEFT, "%d", obstaculos.tamanho());

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 75
                 , ALLEGRO_ALIGN_LEFT, "Num de Testes sem Quadtree:");

    al_draw_textf(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 90
                 , ALLEGRO_ALIGN_LEFT, "%d", obstaculos.tamanho());

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 115
                         , ALLEGRO_ALIGN_LEFT, "Num de Testes com Quadtree:");

    al_draw_textf(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 130
                 , ALLEGRO_ALIGN_LEFT, "%d", potColisoes.size());

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 155
                         , ALLEGRO_ALIGN_LEFT, "% da Reducao de Testes:");

    al_draw_textf(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 170
                 , ALLEGRO_ALIGN_LEFT, "%.2f %%", ((float)potColisoes.size() / (float)obstaculos.tamanho() * 100.00f) - 100.00f);

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 0), 650, 300
                         , ALLEGRO_ALIGN_LEFT, "LEGENDA");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 325
                         , ALLEGRO_ALIGN_LEFT, "Bola Verde:  Player");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 345
                         , ALLEGRO_ALIGN_LEFT, "Bola Vermelha:  Obstaculos");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 365
                         , ALLEGRO_ALIGN_LEFT, "Bola Amarela:  Potenciais Colisoes");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 255), 650, 385
                         , ALLEGRO_ALIGN_LEFT, "Bola Azul:  Colisao");

    al_draw_text(fonte.rsPegaFonte(), al_map_rgb(0, 0, 0), 665, 460
                         , ALLEGRO_ALIGN_LEFT, "Pressione  ESC  Para Sair");
}

//Trata o evento de fechar da janela
void tratarEventos()
{
    ALLEGRO_EVENT ev;

    while ( !al_is_event_queue_empty( eventos ) )
    {
        al_wait_for_event( eventos, &ev );

        //Procesa todos os eventos aqui
        if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
            sair = true;
        }
    }

}

//Libera a memoria alocada
void finalizar()
{
    //Deleta o player
    delete player;

    //Loop em toda a lista para deletar os obstaculos
    ListaNo *aux = obstaculos.pegarTopo();

    while(aux != NULL)
    {
        ObjetoJogo *obj = aux->dado;

        //Deleta o obstaculo
        delete obj;
        obj = 0;

        aux = aux->noProx;
    }

    //Deleta a janela e a lista de eventos
    al_destroy_event_queue(eventos);
    al_destroy_display(janela);
}

//Funcao Principal
int main()
{
    try
    {
        //Seta a semente do random
        srand(time(NULL));

        //Inicia a Biblioteca Grafica
        iniciarAllegro();

        //Cria a janela
        criarJanela();

        //Cria a fonte
        rsFonte fonte("C:/Windows/Fonts/Arial.ttf", 12);

        //Seta o tamanho da QuadTree
        quadTree.rsCriaQuadTree(0, 0, 640, 480);

        //Cria todos os objetos
        criarObjetos();

        //Loop do jogo
        while(!sair)
        {
            //Atualiza as entradas do teclado
            teclado.rsAtualizaTeclado();

            //Checa se foi pressionado o ESC
            if(teclado.rsChecaTeclaPressionada(ALLEGRO_KEY_ESCAPE))
            {
                //Sai do loop e acaba o jogo
                sair = true;
                continue;
            }

            //Limpa a tela para branco
            al_clear_to_color(al_map_rgb(255, 255, 255));


            //Desenha os obstaculos na lista
            ListaNo *aux = obstaculos.pegarTopo();

            //Loop na lista de obstaculos
            while(aux != NULL)
            {
                ObjetoJogo *obj = aux->dado;

                //Desenha o obstaculo
                obj->desenhar();

                aux = aux->noProx;
            }

            //Desenha e atualiza o player
            player->atualizar();
            player->desenhar();

            //Desenha a Quadtree
            quadTree.rsDesenha();

            //Pega as potenciais colisoes da posicao atual do player
            potColisoes = quadTree.rsPegaPotencialColisao(player->pegarX(), player->pegarY(), 20, 20);

            //Loop em todas as potenciais colisoes
            for(unsigned int i = 0; i < potColisoes.size(); ++i)
            {
                //Desenha as potenciais colisoes de amarelo
                al_draw_filled_circle(potColisoes[i]->pegarX(), potColisoes[i]->pegarY(), 10, al_map_rgb(255, 255, 0));

                //Testa se esta colidindo com o player e se estiver pinta de azul
                if(player->testarColisao(potColisoes[i]))
                    al_draw_filled_circle(potColisoes[i]->pegarX(), potColisoes[i]->pegarY(), 8, al_map_rgb(0, 0, 255));
            }

            //Desenha as informacoes da simulacao
            desenharInformacoes(fonte);

            //Desenha tudo na tela
            al_flip_display();

            //Trata os eventos
            tratarEventos();

            //Da o controle d volta para o sistema operacional
            al_rest(0.16f);
        }

        //Finaliza o jogo e libera toda a memoria
        finalizar();
    }
    catch(rsExcecao &ex)
    {
        ex.rsMostraErro();
    }

    return 0;
}
