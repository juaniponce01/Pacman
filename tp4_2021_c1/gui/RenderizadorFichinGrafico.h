#ifndef RENDERIZADORFICHINGRAFICO_H
#define RENDERIZADORFICHINGRAFICO_H

#include <SDL2/SDL.h>
#include "FichinGrafico.h"
#include "Textura.h"

const int COMIENZO_MAPA_X = 188;
const int COMIENZO_MAPA_Y = 596;

// Renderizador de la ventana
extern SDL_Renderer *renderizador;

extern SDL_Rect sprites[54];
extern SDL_Rect numerosGrandes[10];
extern SDL_Rect numerosChicos[10];
extern SDL_Rect letrasGrandes[27];
extern SDL_Rect letrasChicas[27];
extern SDL_Rect marco;
extern SDL_Rect fondoIniciar;
extern SDL_Rect fondoJugando;
extern SDL_Rect fondoGano;
extern SDL_Rect fondoPerdio;
extern Textura texturaSprites;
extern Textura texturaNumerosGrandes;
extern Textura texturaNumerosChicos;
extern Textura texturaLetrasGrandes;
extern Textura texturaLetrasChicas;
extern Textura texturaMarco;
extern Textura texturaFondoIniciar;
extern Textura texturaFondoJugando;
extern Textura texturaFondoGano;
extern Textura texturaFondoPerdio;

class RenderizadorFichinGrafico {
public:

    RenderizadorFichinGrafico(FichinGrafico &fg);

    void renderizarFondoIniciar();

    void renderizarLetraNuevoJugador(int i, Nat pos);

    void nuevaPartida(Jugador j);

    void mover(Direccion d);

    bool alguienJugando() const;

private:

    void renderizarRanking();

    void renderizarPosicionRanking(int indice, Jugador jugador, Puntaje puntaje);

    void renderizarObjetivo();

    void renderizarJugadorActual();

    void renderizarCantidadMovimientos();

    void renderizarInmunidad();

    void renderizarMapaCompleto();

    void renderizarPosicion(int x, int y, TipoPosicion tp);

    void renderizarAnimacionPerdio(Coordenada posicionPerdio);

    FichinGrafico _fichinGrafico;
};

#endif // RENDERIZADORFICHINGRAFICO_H
