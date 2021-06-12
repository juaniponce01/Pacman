/*
    FORMATO:
    ---------------------
    -----C---------L-----
    -P-------I---------P-
    ---------------------
    ----P----------C-----
    --------F--------F---

    - -> Nada
    I -> Inicio
    L -> Llegada
    P -> Pared
    F -> Fantasma
    C -> Chocolate
*/

#ifndef LECTORDEFICHIN_H
#define LECTORDEFICHIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "../src/aed2_Fichin.h"

using namespace std;

aed2_Fichin crearFichin();

#endif // LECTORDEFICHIN_H
