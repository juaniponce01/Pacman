#include <SDL2/SDL.h>
#include "LectorDeFichin.h"
#include "ManejadorDeEventos.h"

int main(int argc, char *args[]) {
    // Inicializar SDL y crear la ventana
    if (!iniciar()) {
        printf("Fallo al inicializar\n");
    } else {
        // Cargar las imagenes
        if (!cargarArchivos()) {
            printf("Fallo al cargar las imagenes\n");
        } else {
            bool quit = false;

            // Manejador de eventos
            SDL_Event e;

            // Limpiar la pantalla
            SDL_SetRenderDrawColor(renderizador, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderizador);

            // Inicializar variables para mostrar el mapa
            aed2_Fichin f = crearFichin();
            FichinGrafico fg(f);
            RenderizadorFichinGrafico rfg(fg);
            Jugador jugadorActual;

            // Mientras el programa esta corriendo
            while (!quit) {

                // Pedirle al usuario que ingrese su nombre
                rfg.renderizarFondoIniciar();
                jugadorActual = "";
                while (!quit && jugadorActual.size() < 3) {
                    quit = manejarEventosNuevaPartida(e, rfg, jugadorActual);
                }

                // Crear la partida
                if (!quit) {
                    SDL_Delay(1000);
                    rfg.nuevaPartida(jugadorActual);
                }

                // Jugar la partida hasta terminarla
                while (!quit && rfg.alguienJugando()) {
                    quit = manejarEventosJuego(e, rfg);
                }
            }
        }
    }

    // Liberar los recursos y cerrar SDL
    cerrar();

    return 0;
}
