/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem o codigo do inimigo.
*/

#include "jogo42.h"


void MoverInimigo(struct Inimigo* inimigo, const GameState* gs)
{
    // Distancias entre o inimigo e o jogador
    // De centro a centro
    const float DIST_CENTROS = Vector2Distance(inimigo->pos, gs->jog.pos);
    // De borda a borda
    const float DIST_BORDAS = DIST_CENTROS - INIM_RAIO - JOG_RAIO;

    // Se o jogador estiver na distancia certa
    if (DIST_CENTROS < INIM_MAX_DIST && DIST_BORDAS > INIM_MIN_DIST)
    {
        // Posicao para a qual moveremos
        Vector2 posFutura = Vector2AndarDist(inimigo->pos, gs->jog.pos,
                                            INIM_VEL * GetFrameTime());

        inimigo->pos = posFutura;

        // Rotacionar
        inimigo->rot = Vector2Angle(inimigo->pos, gs->jog.pos);
    }
}


void AtaqueInimigo(struct Inimigo* inimigo, GameState* gs)
{
    // Distancia entre o inimigo e o jogador, de borda a borda
    const float DIST_BORDAS =
        Vector2Distance(inimigo->pos, gs->jog.pos) - INIM_RAIO - JOG_RAIO;

    // Se o tempo do warmup ja passou
    if (inimigo->timerAtq >= INIM_WARMUP)
    {
        // Causar dano
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            gs->jog.hp -= INIM_DANO;
        }

        // Encerrar o ataque
        inimigo->timerAtq = -1;
    }

    // Se ainda estamos no warmup
    else if (inimigo->timerAtq >= 0)
    {
        // Incrementar timer
        inimigo->timerAtq += GetFrameTime();
    }

    // Se nao estamos atacando
    else if (inimigo->timerAtq < 0)
    {
        // Se o player estiver sob alcance
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            // Comecar a atacar
            inimigo->timerAtq = 0;
        }
    }
}

bool SpawnarInimigo(Vector2 pos, GameState* gs)
{
    for (int i = 0; i<INIM_QTD_MAX; i++)
    {
        if (!gs->inimigos[i].existe)
        {
            gs->inimigos[i].pos = pos;
            gs->inimigos[i].rot = 0;
            gs->inimigos[i].hp = 60;
            gs->inimigos[i].timerAtq = -1;
            gs->inimigos[i].existe = true;
            return true;

        }
    }
    return false;
}






