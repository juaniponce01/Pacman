#include "ManejadorDeEventos.h"

bool manejarEventosNuevaPartida(SDL_Event &e, RenderizadorFichinGrafico &rfg, Jugador &jugadorActual) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // El usuario cierra el programa
            return true;
        } else if (e.type == SDL_KEYDOWN) {
            // El usuario apreta una letra

            if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z) {
                jugadorActual.push_back(e.key.keysym.sym);
                rfg.renderizarLetraNuevoJugador(e.key.keysym.sym - SDLK_a, jugadorActual.size() - 1);
            }
        }
    }
    return false;
}

bool manejarEventosJuego(SDL_Event &e, RenderizadorFichinGrafico &rfg) {
    // Manejo de eventos en la cola
    if (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // El usuario cierra el programa
            return true;
        } else if (e.type == SDL_KEYDOWN) {
            // El usuario apreta una tecla

            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    rfg.mover(ARRIBA);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    rfg.mover(ABAJO);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    rfg.mover(IZQUIERDA);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    rfg.mover(DERECHA);
                    break;

                default:
                    break;
            }
        }
    }
    return false;
}
