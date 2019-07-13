/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem coisas relacionadas ao level.
*/

#include "jogo42.h"


void InicializarLevel(enum Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    /*
    Esta string determina como vai ser o level. Isso eh provisorio, so
    enquanto nao tivermos um editor de mapa.
     '.'  = TILE_chao
     '#'  = TILE_parede
     'I'  = TILE_paredeInvisivel
    Resto = TILE_vazio
    */
    const char STRING_DO_LEVEL[] =
//   123456789|123456789|123456789|123456789|
    "#######################################" // 1
    "........#.......#.....#.....#.....#####" // 2
    ".  ..  .#............................##" // 3
    ".  ..  .#............................##" // 4
    "...  ...#...###...###...###..........##" // 5
    "..    ..#...###...###...###..........##" // 6
    "..    ..#............................##" // 7
    ".. .. ..#............................##" // 8
    "........#.......#.....#.....#.....#####" // 9
    "#..#######...######.###################" //10
    "#.......I......##.....#################" //11
    "#.......I.......#......##........#....#" //12
    "###########.....##......##.......#....#" //13
    "#........###....##.......##...........#" //14
    "#.........###....##.......###.........#" //15
    "#..........#......##.......#####..##..#" //16
    "#......#...#.......##.........#....#..#" //17
    "#......#............#.................#" //18
    ".......#...#..........................#" //19
    "......................##......#....#..#" //20
    ".#...#...#...#...#.....#########..##..#" //21
    "...#...#...#...#...#..........#....#..#" //22
    "......................................#" //23
    ".#...#...#...#...#....................#" //24
    "......................................#" //25
    "...#...#...#...#......................#" //26
    "................#######################";//27

    /* Iterar sobre cada elemento de lvl, setando-os de acordo com os
       caracteres correspondentes em STRING_DO_LEVEL. */
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            // Indice em STRING_DO_LEVEL correspondente ahs lin e col atuais
            const int INDICE_STR = lin * TAM_SALA_X + col;

            // Valor Tile que vai ser definido
            enum Tile tile;
            // Definir `tile` de acordo com o caractere
            switch (STRING_DO_LEVEL[INDICE_STR])
            {
                case '.':
                    tile = TILE_chao; break;
                case '#':
                    tile = TILE_parede; break;
                case 'I':
                    tile = TILE_paredeInvisivel; break;
                case ' ': default:
                    tile = TILE_vazio;
            }

            lvl[lin][col] = tile;
        }
    }
}


void InicializarObst(GameState* gs)
{
    // Obstaculo retangular
    gs->obst.ret = (Rectangle){100, 100, 150, 100};
    // Obstaculo circular
    gs->obst.circCentro = (Vector2){1500, 350};
    gs->obst.circRaio = 150;
    gs->obst.circTaAndando = false;
}


bool ColisaoComLevel(Vector2 pos, float raio, const GameState* gs)
{
    //[ OBSTACULO RETANGULAR ]-------------------------------------------------
    if (CheckCollisionCircleRec(pos, raio, gs->obst.ret))
    {
        return true;
    }

    //[ OBSTACULO CIRCULAR ]---------------------------------------------------
    // A funcao de checar colisao buga se for fornecida raio menor que 0
    const float OBST_RAIO = (gs->obst.circRaio < 0) ? 0 : gs->obst.circRaio;

    if (CheckCollisionCircles(pos, raio, gs->obst.circCentro, OBST_RAIO))
    {
        return true;
    }

    //[ TILES ]----------------------------------------------------------------
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            const enum Tile* AQUI = &gs->sala[lin][col];

            if ((*AQUI == TILE_parede || *AQUI == TILE_paredeInvisivel)
                && CheckCollisionCircleRec(pos, raio,
                                           RectDaTile(col, lin)))
            {
                return true;
            }
        }
    }

    // Se chegou ate aqui entao n ta colidindo com nada
    return false;
}


void MoverObst(GameState* gs)
{
    //[ OBSTACULO RETANGULAR ]=================================================
    if (IsKeyPressed(KEY_SPACE))
    {
        gs->obst.ret.x += 35;
        gs->obst.ret.height += 35;
    }

    //[ OBSTACULO CIRCULAR ]===================================================
    if (IsKeyDown(KEY_SPACE))
    {
        gs->obst.circTaAndando = true;
        gs->obst.circCentro.x -= VEL_CIRC * GetFrameTime();
        gs->obst.circRaio -= VEL_CIRC / 20.0f * GetFrameTime();
    }
    else
    {
        gs->obst.circTaAndando = false;
    }
}
