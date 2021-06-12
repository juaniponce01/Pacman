#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Fichin.h"

class FichinTest : public testing::Test {
protected:
    Coordenada posI, posIA, posIB, posII, posID, posL, posLA, posLB, posLI, posLD;
    Coordenada pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    set<Coordenada> posicionesI, posiciones12, posiciones123, posiciones3456, posiciones456, posiciones789, posiciones89, posiciones9;
    Jugador jugador1, jugador2, jugador3;
    map<Jugador, Puntaje> ranking1, ranking2, ranking3, ranking4, ranking5, ranking6;
    pair<Jugador, Puntaje> objetivo1, objetivo2;

    /*
     * ID Posiciones
     * ############ 
     * #         9#8  
     * # I 7      #7
     * #8 1       #6
     * #          #5
     * #    6     #4
     * #       2  #3
     * #5       L #2
     * #34        #1
     * ############ 
     *  1234567890
     *
     * Referencias mapas (ver en tests):
     *  * I: Inicio
     *  * L: Llegada
     *  * #: Pared/Borde
     *  * C: Chocolate 
     *  * F: Fantasma
     *  * .: Recorrido jugador
     *  * X: Choque con pared/borde
     *  * D: Muerte por fantasma
     *  * c: Comer chocolate
     *  * f: Atravesar fantasma
     */

    void SetUp() {
        posI = {2, 7};
        posIA = {2, 8};
        posIB = {2, 6};
        posII = {1, 7};
        posID = {3, 7};
        posL = {9, 2};
        posLA = {9, 3};
        posLB = {9, 1};
        posLI = {8, 2};
        posLD = {10, 2};
        pos0 = {4, 6};
        pos1 = {3, 6};
        pos2 = {8, 3};
        pos3 = {1, 1};
        pos4 = {2, 1};
        pos5 = {1, 2};
        pos6 = {5, 4};
        pos7 = {4, 7};
        pos8 = {1, 6};
        pos9 = {10, 8};
        posicionesI = {posI};
        posiciones12 = {pos1, pos2};
        posiciones123 = {pos1, pos2, pos3};
        posiciones3456 = {pos3, pos4, pos5, pos6};
        posiciones456 = {pos4, pos5, pos6};
        posiciones789 = {pos7, pos8, pos9};
        posiciones89 = {pos8, pos9};
        posiciones9 = {pos9};
        jugador1 = "jugador1";
        jugador2 = "jugador2";
        jugador3 = "jugador3";
        objetivo1 = {jugador1, 12};
        objetivo2 = {jugador2, 14};
        ranking1 = {{jugador1, 16}};
        ranking2 = {{jugador1, 12}};
        ranking3 = {{jugador1, 14}};
        ranking4 = {{jugador1, 12},
                    {jugador2, 14}};
        ranking5 = {{jugador1, 12},
                    {jugador2, 14},
                    {jugador3, 16}};
        ranking6 = {{jugador1, 14},
                    {jugador2, 14},
                    {jugador3, 16}};
    }
};

/*
 * ############ 
 * #         F#8  
 * # I F      #7
 * #F #       #6
 * #          #5
 * #    C     #4
 * #       #  #3
 * #C       L #2
 * ##C        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, nuevo_fichin) {
    aed2_Fichin f(10, 8, posI, posL, posiciones123, posiciones789, posiciones456);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones123);
    EXPECT_EQ(f.fantasmas(), posiciones789);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones456);
}

/*
 * ############ 
 * #         ##8  
 * # I #      #7
 * ## C       #6
 * #          #5
 * #    F     #4
 * #       C  #3
 * #F       L #2
 * #CF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, nueva_partida) {
    aed2_Fichin f(10, 8, posI, posL, posiciones789, posiciones456, posiciones123);
    f.nuevaPartida(jugador1);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones789);
    EXPECT_EQ(f.fantasmas(), posiciones456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones123);
    EXPECT_EQ(f.chocolatesActuales(), posiciones123);
}

/*
 * ############ 
 * # .       C#8  
 * # I C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, mover_arriba) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ARRIBA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posIA);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I C      #7
 * #C.#       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, mover_abajo) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posIB);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * #.I C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, mover_izquierda) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posII);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I.C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, mover_derecha) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posID);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * # ..      C#8  
 * # I.C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, varios_movimientos) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 4);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I C      #7
 * #C.X       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, pared_bloquea_derecha) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posIB);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I.C      #7
 * #C X       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, pared_bloquea_abajo) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posID);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       X  #3
 * #F      .I #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, pared_bloquea_arriba) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posLI);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       X. #3
 * #F       I #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, pared_bloquea_izquierda) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posLA);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ##X######### 
 * # .       C#8  
 * # I C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, borde_bloquea_arriba) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posIA);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * X.I C      #7
 * #C#       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, borde_bloquea_izquierda) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posII);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       I #2
 * #FF      . #1
 * #########X## 
 *  1234567890
 */
TEST_F(FichinTest, borde_bloquea_abajo) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posLB);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       I.X2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, borde_bloquea_derecha) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posLD);
    EXPECT_EQ(f.cantidadMovimientos(), 1);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I C      #7
 * #C.#       #6
 * # .D       #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, perder_derecha) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), PERDIO);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I C      #7
 * #C.#       #6
 * # .        #5
 * # D  F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, perder_abajo) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), PERDIO);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F    D .I #2
 * #FF   ...  #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, perder_arriba) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), PERDIO);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # L C      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F      .I #2
 * #FF  D...  #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, perder_izquierda) {
    aed2_Fichin f(10, 8, posL, posI, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), PERDIO);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posL);
    EXPECT_EQ(f.llegada(), posI);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

/*
 * ############ 
 * #         C#8  
 * # I.c      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos7);
    EXPECT_EQ(f.cantidadMovimientos(), 2);
    EXPECT_EQ(f.inmunidad(), 10);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones89);
}

/*
 * ############ 
 * #         C#8  
 * # I.c      #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate_y_moverse) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posID);
    EXPECT_EQ(f.cantidadMovimientos(), 3);
    EXPECT_EQ(f.inmunidad(), 9);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones89);
}

/*
 * ############ 
 * #         C#8  
 * # I.c.     #7
 * #C #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, no_comer_chocolate_dos_veces) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos7);
    EXPECT_EQ(f.cantidadMovimientos(), 4);
    EXPECT_EQ(f.inmunidad(), 8);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones89);
}

/*
 * ############ 
 * #          #8  
 * # c        #7
 * #  #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate_inicio) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posicionesI);
    f.nuevaPartida(jugador1);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 10);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posicionesI);
    EXPECT_TRUE(f.chocolatesActuales().empty());
}

/*
 * ############ 
 * #         C#8  
 * # I..      #7
 * #C #.      #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate_y_acercarse_a_fantasma) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos0);
    EXPECT_EQ(f.cantidadMovimientos(), 3);
    EXPECT_EQ(f.inmunidad(), 9);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones89);
}

/*
 * ############ 
 * #         C#8  
 * # I.c      #7
 * #C #.      #6
 * #   .      #5
 * #   .f     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate_y_atravesar_fantasma) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos6);
    EXPECT_EQ(f.cantidadMovimientos(), 6);
    EXPECT_EQ(f.inmunidad(), 6);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones89);
}

/*
 * ############ 
 * #         C#8  
 * # I.c      #7
 * #C #D      #6
 * #   .      #5
 * #   .F     #4
 * #   .   #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, comer_chocolate_y_agotar_inmunidad) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), PERDIO);

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

/*
 * ############ 
 * #......   C#8  
 * #.I.c .    #7
 * #c #...    #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, recuperar_inmunidad) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(ARRIBA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos8);
    EXPECT_EQ(f.cantidadMovimientos(), 14);
    EXPECT_EQ(f.inmunidad(), 10);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones9);
}

/*
 * ############ 
 * #         C#8  
 * #.I.c      #7
 * #c #       #6
 * #          #5
 * #    F     #4
 * #       #  #3
 * #F       L #2
 * #FF        #1
 * ############ 
 *  1234567890
 */
TEST_F(FichinTest, renovar_inmunidad) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);

    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(DERECHA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.mover(IZQUIERDA), SIGUE);
    EXPECT_EQ(f.inmunidad(), 7);
    EXPECT_EQ(f.mover(ABAJO), SIGUE);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), pos8);
    EXPECT_EQ(f.cantidadMovimientos(), 6);
    EXPECT_EQ(f.inmunidad(), 10);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones9);
}

void realizarMovimientos(aed2_Fichin &f, const string &movs) {
    for (const char &m : movs) {
        if (m == 'A') {
            f.mover(ARRIBA);
        } else if (m == 'B') {
            f.mover(ABAJO);
        } else if (m == 'I') {
            f.mover(IZQUIERDA);
        } else if (m == 'D') {
            f.mover(DERECHA);
        }
    }
}

TEST_F(FichinTest, ganar_partida_sin_chocolate) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDDDDBBBBBB");

    EXPECT_EQ(f.mover(IZQUIERDA), GANO);
    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking1);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, ganar_partida_con_chocolate) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDBDBDBDDDB");

    EXPECT_EQ(f.mover(ABAJO), GANO);
    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking2);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, perder_una_partida_y_arrancar_otra) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "BBB");
    f.nuevaPartida(jugador1);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_TRUE(f.ranking().empty());
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

TEST_F(FichinTest, ganar_una_partida_y_arrancar_otra) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDBDDBBDDDBB");
    f.nuevaPartida(jugador1);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_EQ(f.ranking(), ranking2);
    EXPECT_EQ(f.objetivo(), objetivo1);
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

TEST_F(FichinTest, segunda_partida_mejora_puntaje) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDBBDDBBBB");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDBDBDDBDDBB");

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking2);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, segunda_partida_no_mejora_puntaje) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDDBBDBDDDBB");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDDBDBBBBB");

    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking2);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, ganar_perder_y_volver_a_ganar) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDBDDDBBBBBI");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "BBI");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDBBBBBBDDDDD");

    EXPECT_EQ(f.mover(ARRIBA), GANO);
    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking3);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, ganar_ganar_y_volver_a_ganar) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDBDBDBBBB");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "ADDDDDDDBDBBBBBI");
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDBDBDBBBDD");

    EXPECT_EQ(f.mover(DERECHA), GANO);
    EXPECT_FALSE(f.alguienJugando());
    EXPECT_EQ(f.ranking(), ranking2);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
}

TEST_F(FichinTest, dos_jugadores_y_objetivo) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDDDDDDBBBBB");
    f.nuevaPartida(jugador2);
    realizarMovimientos(f, "ADDDDBDBDBDBBB");
    f.nuevaPartida(jugador2);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador2);
    EXPECT_EQ(f.ranking(), ranking4);
    EXPECT_EQ(f.objetivo(), objetivo1);
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

TEST_F(FichinTest, tres_jugadores_y_objetivo_de_ultimo) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDDDDDBDBBBB");
    f.nuevaPartida(jugador2);
    realizarMovimientos(f, "IBDBDBDDDDDDBB");
    f.nuevaPartida(jugador3);
    realizarMovimientos(f, "IADDDDDDDDBBBBBB");
    f.nuevaPartida(jugador3);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador3);
    EXPECT_EQ(f.ranking(), ranking5);
    EXPECT_EQ(f.objetivo(), objetivo2);
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

TEST_F(FichinTest, tres_jugadores_y_objetivo_de_primero) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "DDDDDBBBBBDD");
    f.nuevaPartida(jugador2);
    realizarMovimientos(f, "IBBDDDDDDDDBBB");
    f.nuevaPartida(jugador3);
    realizarMovimientos(f, "IABBBDDDDDDDDBBB");
    f.nuevaPartida(jugador1);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador1);
    EXPECT_EQ(f.ranking(), ranking5);
    EXPECT_EQ(f.objetivo(), objetivo1);
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}

TEST_F(FichinTest, tres_jugadores_y_objetivo_con_empate) {
    aed2_Fichin f(10, 8, posI, posL, posiciones12, posiciones3456, posiciones789);
    f.nuevaPartida(jugador1);
    realizarMovimientos(f, "IBBBBBDDDDDDDD");
    f.nuevaPartida(jugador2);
    realizarMovimientos(f, "IBBBBDBDDDDDDD");
    f.nuevaPartida(jugador3);
    realizarMovimientos(f, "IADDDDDDDBDBBBBB");
    f.nuevaPartida(jugador3);

    EXPECT_TRUE(f.alguienJugando());
    EXPECT_EQ(f.jugadorActual(), jugador3);
    EXPECT_EQ(f.ranking(), ranking6);
    EXPECT_EQ(f.objetivo().second, 14);
    EXPECT_EQ(f.jugador(), posI);
    EXPECT_EQ(f.cantidadMovimientos(), 0);
    EXPECT_EQ(f.inmunidad(), 0);
    EXPECT_EQ(f.largo(), 10);
    EXPECT_EQ(f.alto(), 8);
    EXPECT_EQ(f.inicio(), posI);
    EXPECT_EQ(f.llegada(), posL);
    EXPECT_EQ(f.paredes(), posiciones12);
    EXPECT_EQ(f.fantasmas(), posiciones3456);
    EXPECT_EQ(f.chocolatesIniciales(), posiciones789);
    EXPECT_EQ(f.chocolatesActuales(), posiciones789);
}
