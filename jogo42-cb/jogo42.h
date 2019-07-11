/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Este arquivo deve ser incluso em todos os arquivos `.c`.
*/

#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"


//[ DEFINICOES DE CONSTANTES UTILIZADAS NAS DEFINICOES DE TIPOS ]==============
/// Tamanho de uma sala, em numero de tiles.
#define TAM_SALA_X 39
/// Tamanho de uma sala, em numero de tiles.
#define TAM_SALA_Y 27


//[ DEFINICOES DE TIPOS ]======================================================

typedef enum {
    /// Vazio (Nao contem nada, nem mesmo chao).
    TILE_vazio = 0,
    /// Mostra grafico de chao e nao colide.
    TILE_chao,
    /// Mostra grafico de parede e colide.
    TILE_parede,
    /// Mostra grafico de chao e colide.
    TILE_paredeInvisivel
}
Tile; ///< Tipos de tile.


typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    int hp;
}
Jog; ///< Estado do jogador.


typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    int hp;
    /// Se estah seguindo o jogador.
    bool seguindo;
    /// Dano
    int dano;
    /// Color
    Color cor;
    /// Contador de frames
    int framesCounter;
}
Inimigo; ///< Estado de um inimigo.


typedef struct {
    //[ JOGADOR ]--------------------------------------------------------------
    Jog jog;
    Camera2D cam;

    //[ INIMIGOS ]-------------------------------------------------------------
    // So tem um por enquanto, depois vai ter uma lista
    /// O inimigo.
    Inimigo inim;

    //[ LEVEL ]----------------------------------------------------------------
    Tile sala[TAM_SALA_Y][TAM_SALA_X];

    //[ OBSTACULOS ]-----------------------------------------------------------
    /// Obstaculo retangular.
    Rectangle obstRet;
    /// Posicao do centro do obstaculo circular.
    Vector2 obstCircCentro;
    /// Raio do obstaculo circular.
    float obstCircRaio;
    /// Se o obstaculo circular ta andando.
    bool obstCircTaAndando;
}
GameState; ///< Struct de estado do jogo.



//[ DEFINICOES DE CONSTANTES ]=================================================

//[ JOGADOR ]------------------------------------------------------------------
/// Velocidade do jogador (por segundo).
#define VEL_JOG (150.0f)
/// Raio do jogador.
#define RAIO_JOG (20.0f)

//[ INIMIGO ]------------------------------------------------------------------
/// Raio do inimigo.
#define RAIO_INIM (15.0f)

/** Distancia maxima na qual o inimigo vai seguir o jogador, do centro do
    inimigo ah borda do jogador. */
#define INIM_MAX_DIST (160.0f)

/** Distancia minima na qual o inimigo vai seguir o jogador, do centro do
    inimigo ah borda do jogador. */
#define INIM_MIN_DIST (40.0f)

/// Alcance de ataque do inimigo, do centro do inimigo ah borda do jogador.
#define INIM_ATQ_DIST (40.0f)

//[ OUTROS ]-------------------------------------------------------------------
/// Velocidade do obstaculo circular (por segundo).
#define VEL_CIRC (100.0f)

/// Tamanho de uma tile.
#define TAM_TILE (35)



//[ DECLARACOES DE FUNCOES DEFINIDAS EM OUTROS ARQUIVOS ]======================

// helpers.c ------------------------------------------------------------------
/** Retorna o retangulo correspondente ah tile nas dimensoes fornecidas. */
Rectangle RectDaTile(int x, int y);

/** Retorna a posicao do cursor em coordenadas world. */
Vector2 PosWorldDoCursor(const GameState* gs);

// desenhar.c -----------------------------------------------------------------
/** Desenha tudo. */
void Desenhar(const GameState* gs, const Texture2D* spriteJog);

// jogador.c ------------------------------------------------------------------
/** Move o jogador. */
void MoverJog(GameState* gs);

// inimigo.c ------------------------------------------------------------------
/** Move o inimigo. */
void MoverInimigo(GameState* gs);

/** Checa se o inimigo estah em range e se nao estah em cooldown de ataque,
    e caso sim, ataca. */
void AtaqueDoInimigo(GameState* gs);

// level.c --------------------------------------------------------------------
/** Move os obstaculos. */
void MoverObst(GameState* gs);

/** Inicializa o level de acordo com a string na definicao desta funcao. */
void InicializarLevel(Tile lvl[TAM_SALA_Y][TAM_SALA_X]);


#endif // JOGO42_H_INCLUDED





