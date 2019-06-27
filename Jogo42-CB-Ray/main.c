#include <raylib.h>
#include <raymath.h>

// Responsavel pela movimenta��o do player
int playerMovement (Rectangle* playerTransform, Rectangle* playerPosition)
{
    if(IsKeyDown(KEY_W)) (*playerTransform).y -= 3.0f;
    if(IsKeyDown(KEY_A)) (*playerTransform).x -= 3.0f;
    if(IsKeyDown(KEY_S)) (*playerTransform).y += 3.0f;
    if(IsKeyDown(KEY_D)) (*playerTransform).x += 3.0f;

    (*playerPosition).x = (*playerTransform).x;
    (*playerPosition).y = (*playerTransform).y;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;        // Largura da tela
    const int screenHeight = 450;       // Altura da tela

    InitWindow(screenWidth, screenHeight, "Jogo 42");       // Inicializar tela

    Image playerImage = LoadImage("Textures/protag.png");  // Encontra a imagem do player nos arquivos do jogo
    Texture2D sprite = LoadTextureFromImage(playerImage);   // Carrega o sprite

    int frameWidth = sprite.width;      // Largura do sprite
    int frameHeight = sprite.height;    // Altura do sprite

    // Seleciona o sprite do player
    Rectangle sourceRec = {0.0f, 0.0f, frameWidth, frameHeight};

    // Determina o local onde o player ser� desenhado e a escala do mesmo
    Rectangle playerTransform = {screenWidth/2, screenHeight/2, frameWidth/2, frameHeight/2};

    // Guarda a posi��o x e y do player
    Vector2 playerPosition = {playerTransform.x, playerTransform.y};

    // Determina o ponto do sprite que � usado de refer�ncia para movimenta��o e rota��o
    Vector2 origin = {frameWidth/4, frameHeight/4};

    float rotation = 0.0f;          // Rota��o do sprite

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        playerMovement(&playerTransform, &playerPosition);

        rotation = Vector2Angle(playerPosition, GetMousePosition());    // Adquire o angulo do player em rela��o a c�mera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Desenha o sprite do player j� com a escala e rota��o certas.
            DrawTexturePro(sprite, sourceRec, playerTransform, origin, rotation, RAYWHITE);
            DrawText("Move the ball with W/A/S/D", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(sprite);  // Descarregar a textura

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
