// Dados de um estagio
struct Estagio
{
    // String que define como vai ser o level
    const char stringDeLevel[STR_LVL_TAM_MAX];
    /*

     '.'     =   TILE_chao
     '#'     =   TILE_parede
     'I'     =   TILE_paredeInvisivel
     'E'     =   TILE_chao com inimigo inicialmente
    Resto    =   TILE_vazio

    */


    // Posicao na qual o jogador comeca
    Vector2 spawnPos;
};



/* Define qual level vai ser carregado. Isso eh temporario, ate ter o codigo
       de troca de level. */
    #define ESTAGIO estagio1



//[ ESTAGIO 1 ]================================================================
struct Estagio estagio1 = {

.stringDeLevel =

//        10        20        30        40        50        60        70        80
//        |         |         |         |         |         |         |         |
//23456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
"#######################################\n" // 1
"........#.......#.....#.....#.....#####\n" // 2
".  ..  .#............................##\n" // 3
".  ..  .#............................##\n" // 4
"...  ...#...###...###...###..........##\n" // 5
"..    ..#...###...###...###..........##\n" // 6
"..    ..#................E...........##\n" // 7
".. .. ..#...............E..EEE.......##\n" // 8
"........#.......#.....#.....#.....#####\n" // 9
"#..#######...######.###################\n" //10
"#.......I......##.....#################\n" //11
"#.......I.......#......##........#....#\n" //12
"###########.....##......##.......#....#\n" //13
"#........###....##.......##...........#\n" //14
"#.........###....##.......###.........#\n" //15
"#..........#......##.......#####..##..#\n" //16
"#......#...#.......##.........#....#..#\n" //17
"#......#............#.................#\n" //18
".......#...#..........................#\n" //19
"......................##......#....#..#\n" //20
".#...#...#...#...#.....#########..##..#\n" //21
"...#...#...#...#...#..........#....#..#\n" //22
"......................................#\n" //23
".#...#...#...#...#....................#\n" //24
"......................................#\n" //25
"...#...#...#...#......................#\n" //26
"................#######################\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(35, 5)

};






