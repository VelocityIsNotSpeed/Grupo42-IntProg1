/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Arquivo principal, contem o ponto de entrada (funcao main).
*/

#include "jogo42.h"
#include "stdio.h" // Para mandar mensagens de erro no console
#include "stdlib.h" // Pelo malloc


int main(void)
{
    // [[[[[ INICIALIZACAO ]]]]]

    //[ JANELA ]===============================================================
    InitWindow(1024, 576, "Jogo42");
    SetTargetFPS(60);

    //[ STRUCT DE ESTADO DO JOGO ]=============================================
    GameState* gs = malloc(sizeof(GameState));

    //[ JOGADOR ]==============================================================
    // Posicao
    gs->jog.pos.x = RectDaTile(35, 5).x;
    gs->jog.pos.y = RectDaTile(35, 5).y;
    // Rotacao
    gs->jog.rot = 0;
    /// Sprite do jogador.
    const Texture2D SPRITE_JOG = LoadTexture("tex/protag.png");

    //[ LEVEL ]================================================================
    InicializarLevel(gs->sala);

    //[ OBSTACULOS ]===========================================================
    InicializarObst(gs);

    //[ INIMIGO ]==============================================================
    gs->inim.pos = (Vector2){1000, 200};
    gs->inim.rot = 0;
    gs->inim.hp = 120;
    gs->inim.hpos.x = gs->inim.pos.x - 12;
    gs->inim.hpos.y = gs->inim.pos.y + 22;
    itoa(gs->inim.hp, gs->inim.vida, 10);


    //[ CAMERA ]===============================================================
    gs->cam.rotation = 0;
    gs->cam.zoom = 1;

    // [[[ FIM INICIALIZACAO ]]]


    // Loop principal
    while (!WindowShouldClose())
    {


        // [[[[[ UPDATE ]]]]]

        // Mover jogador
        MoverJog(gs);

        // Rotacao do jogador
        gs->jog.rot = Vector2Angle(gs->jog.pos, PosWorldDoCursor(gs));

        // Mover inimigo
        // TODO

        // Mover obstaculos
        MoverObst(gs);

        // Atualizar camera
        gs->cam.offset = Vector2Negate(gs->jog.pos);
        gs->cam.offset.x += GetScreenWidth() / 2;
        gs->cam.offset.y += GetScreenHeight() / 2;
        gs->cam.target = gs->jog.pos;

        // Ataque do jogador
        AtaqueJogador(gs);


        // [[[ FIM UPDATE ]]]


        // [[[[[ DESENHAR ]]]]]
        BeginDrawing();
        Desenhar(gs, &SPRITE_JOG);
        EndDrawing();
        // [[[ FIM DESENHAR ]]]
    }


    // Desinicializacao
    CloseWindow(); // Close window and OpenGL context
    return 0;
}




