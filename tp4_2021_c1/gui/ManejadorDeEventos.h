#ifndef MANEJADORDEEVENTOS_H
#define MANEJADORDEEVENTOS_H

#include <SDL2/SDL.h>
#include "InterfazGrafica.h"

bool manejarEventosNuevaPartida(SDL_Event &e, RenderizadorFichinGrafico &rfg, Jugador &jugadorActual);

bool manejarEventosJuego(SDL_Event &e, RenderizadorFichinGrafico &rfg);

#endif // MANEJADORDEEVENTOS_H
