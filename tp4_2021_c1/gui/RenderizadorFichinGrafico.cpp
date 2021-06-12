#include "RenderizadorFichinGrafico.h"

//The window renderer
SDL_Renderer *renderizador = nullptr;

//Scene sprites
SDL_Rect sprites[54];
SDL_Rect numerosGrandes[10];
SDL_Rect numerosChicos[10];
SDL_Rect letrasGrandes[27];
SDL_Rect letrasChicas[27];
SDL_Rect marco;
SDL_Rect fondoIniciar;
SDL_Rect fondoJugando;
SDL_Rect fondoGano;
SDL_Rect fondoPerdio;
Textura texturaSprites;
Textura texturaNumerosGrandes;
Textura texturaNumerosChicos;
Textura texturaLetrasGrandes;
Textura texturaLetrasChicas;
Textura texturaMarco;
Textura texturaFondoIniciar;
Textura texturaFondoJugando;
Textura texturaFondoGano;
Textura texturaFondoPerdio;

RenderizadorFichinGrafico::RenderizadorFichinGrafico(FichinGrafico &fg) : _fichinGrafico(fg) {}

void RenderizadorFichinGrafico::renderizarFondoIniciar() {
    texturaMarco.renderizar(0, 0, renderizador, &marco);
    renderizarRanking();
    texturaFondoIniciar.renderizar(200, 0, renderizador, &fondoIniciar);
    SDL_RenderPresent(renderizador);
}

void RenderizadorFichinGrafico::renderizarLetraNuevoJugador(int i, Nat pos) {
    texturaLetrasGrandes.renderizar(446 + 36 * pos, 282, renderizador, &letrasGrandes[i]);
    SDL_RenderPresent(renderizador);
}

void RenderizadorFichinGrafico::nuevaPartida(Jugador j) {
    _fichinGrafico.nuevaPartida(j);
    texturaFondoJugando.renderizar(200, 0, renderizador, &fondoJugando);
    renderizarObjetivo();
    renderizarJugadorActual();
    renderizarMapaCompleto();
}

void RenderizadorFichinGrafico::mover(Direccion d) {
    pair<ResultadoMovimiento, Coordenada> resultado = _fichinGrafico.mover(d);
    renderizarMapaCompleto();
    if (resultado.first == PERDIO) {
        SDL_Delay(500);
        renderizarAnimacionPerdio(resultado.second);
        texturaFondoPerdio.renderizar(200, 0, renderizador, &fondoPerdio);
        SDL_RenderPresent(renderizador);
        SDL_Delay(2500);
    } else if (resultado.first == GANO) {
        SDL_Delay(500);
        texturaFondoGano.renderizar(200, 0, renderizador, &fondoGano);
        SDL_RenderPresent(renderizador);
        SDL_Delay(2500);
    }
}

bool RenderizadorFichinGrafico::alguienJugando() const {
    return _fichinGrafico.alguienJugando();
}

void RenderizadorFichinGrafico::renderizarRanking() {
    set<pair<Puntaje, Jugador> > rankingOrdenado = _fichinGrafico.rankingOrdenado();
    int indice = 0;
    for (const pair<Puntaje, Jugador> &par : rankingOrdenado) {
        if (indice < 5) {
            renderizarPosicionRanking(indice, par.second, par.first);
        } else {
            break;
        }
        ++indice;
    }
}

void RenderizadorFichinGrafico::renderizarPosicionRanking(int indice, Jugador jugador, Puntaje puntaje) {
    for (int i = 0; i < 3; ++i) {
        texturaLetrasChicas.renderizar(73 + 18 * i, 211 + 26 * indice, renderizador, &letrasChicas[jugador[i] - 'a']);
    }
    texturaNumerosChicos.renderizar(135, 211 + 26 * indice, renderizador, &numerosChicos[puntaje / 100 % 10]);
    texturaNumerosChicos.renderizar(153, 211 + 26 * indice, renderizador, &numerosChicos[puntaje / 10 % 10]);
    texturaNumerosChicos.renderizar(171, 211 + 26 * indice, renderizador, &numerosChicos[puntaje % 10]);
}

void RenderizadorFichinGrafico::renderizarObjetivo() {
    if (_fichinGrafico.jugadorEnRanking()) {
        pair<Jugador, Puntaje> objetivo = _fichinGrafico.objetivo();
        for (int i = 0; i < 3; ++i) {
            texturaLetrasGrandes.renderizar(82 + 36 * i, 354, renderizador, &letrasGrandes[objetivo.first[i] - 'a']);
        }
        texturaNumerosGrandes.renderizar(82, 392, renderizador, &numerosGrandes[objetivo.second / 100 % 10]);
        texturaNumerosGrandes.renderizar(118, 392, renderizador, &numerosGrandes[objetivo.second / 10 % 10]);
        texturaNumerosGrandes.renderizar(154, 392, renderizador, &numerosGrandes[objetivo.second % 10]);
    }
}

void RenderizadorFichinGrafico::renderizarJugadorActual() {
    Jugador jugadorActual = _fichinGrafico.jugadorActual();
    for (int i = 0; i < 3; ++i) {
        texturaLetrasGrandes.renderizar(82 + 36 * i, 446, renderizador, &letrasGrandes[jugadorActual[i] - 'a']);
    }
}

void RenderizadorFichinGrafico::renderizarCantidadMovimientos() {
    Puntaje cantidadMovimientos = _fichinGrafico.cantidadMovimientos();
    texturaNumerosGrandes.renderizar(82, 500, renderizador, &numerosGrandes[cantidadMovimientos / 100 % 10]);
    texturaNumerosGrandes.renderizar(118, 500, renderizador, &numerosGrandes[cantidadMovimientos / 10 % 10]);
    texturaNumerosGrandes.renderizar(154, 500, renderizador, &numerosGrandes[cantidadMovimientos % 10]);
}

void RenderizadorFichinGrafico::renderizarInmunidad() {
    Nat inmunidad = _fichinGrafico.inmunidad();
    texturaNumerosGrandes.renderizar(118, 554, renderizador, &numerosGrandes[inmunidad / 10 % 10]);
    texturaNumerosGrandes.renderizar(154, 554, renderizador, &numerosGrandes[inmunidad % 10]);
}

void RenderizadorFichinGrafico::renderizarMapaCompleto() {
    for (int y = 1; y <= _fichinGrafico.alto(); ++y) {
        for (int x = 1; x <= _fichinGrafico.largo(); ++x) {
            renderizarPosicion(x, y, _fichinGrafico.tipoPosicion(x, y));
        }
    }
    renderizarCantidadMovimientos();
    renderizarInmunidad();
    SDL_RenderPresent(renderizador);
}

void RenderizadorFichinGrafico::renderizarPosicion(int x, int y, TipoPosicion tp) {
    Nat indice;
    if (tp == Nada) {
        indice = 47;
    } else if (tp == Posicion) {
        indice = 30 + _fichinGrafico.orientacion();
    } else if (tp == Llegada) {
        indice = 48;
    } else if (tp == Pared) {
        indice = 34;
    } else if (tp == Fantasma) {
        if (_fichinGrafico.inmunidad() == 0) {
            indice = 0 + (x + y) % 4;
        } else if (_fichinGrafico.inmunidad() == 1 or _fichinGrafico.inmunidad() == 3) {
            indice = 5;
        } else {
            indice = 4;
        }
    } else if (tp == Chocolate) {
        indice = 35;
    } else if (tp == FantasmaPosicion) {
        if (_fichinGrafico.inmunidad() == 0) {
            indice = 6 + _fichinGrafico.orientacion() * 6 + (x + y) % 4;
        } else if (_fichinGrafico.inmunidad() == 1 or _fichinGrafico.inmunidad() == 3) {
            indice = 11 + _fichinGrafico.orientacion() * 6;
        } else {
            indice = 10 + _fichinGrafico.orientacion() * 6;
        }
    } else if (tp == LlegadaPosicion) {
        indice = 49 + _fichinGrafico.orientacion();
    }
    texturaSprites.renderizar(COMIENZO_MAPA_X + 16 * x, COMIENZO_MAPA_Y - 16 * y, renderizador, &sprites[indice]);
}

void RenderizadorFichinGrafico::renderizarAnimacionPerdio(Coordenada posicionPerdio) {
    Nat x = posicionPerdio.first;
    Nat y = posicionPerdio.second;
    for (int i = 36; i <= 47; ++i) {
        texturaSprites.renderizar(COMIENZO_MAPA_X + 16 * x, COMIENZO_MAPA_Y - 16 * y, renderizador, &sprites[i]);
        SDL_RenderPresent(renderizador);
        SDL_Delay(100);
    }
}
