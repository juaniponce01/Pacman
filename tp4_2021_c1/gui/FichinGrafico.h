#ifndef FICHINGRAFICO_H
#define FICHINGRAFICO_H

#include "../src/aed2_Fichin.h"

enum TipoPosicion {
    Nada, Llegada, Posicion, Pared, Fantasma, Chocolate, FantasmaPosicion, LlegadaPosicion
};

class FichinGrafico {
public:

    FichinGrafico(aed2_Fichin &f);

    void nuevaPartida(Jugador j);

    TipoPosicion tipoPosicion(int x, int y) const;

    pair<ResultadoMovimiento, Coordenada> mover(Direccion d);

    Direccion orientacion() const;

    Nat cantidadMovimientos() const;

    Nat inmunidad() const;

    Nat largo();

    Nat alto();

    bool alguienJugando() const;

    set<pair<Puntaje, Jugador> > rankingOrdenado() const;

    Jugador jugadorActual() const;

    bool jugadorEnRanking() const;

    pair<Jugador, Puntaje> objetivo() const;

private:

    void actualizarMapaGrafico();

    Coordenada actualizarMovimientoPerdedor(Coordenada posicionAnterior, Direccion d);

    Coordenada actualizarMovimientoGanador(Coordenada posicionAnterior, Direccion d);

    Coordenada posicionSiguiente(Coordenada posicionAnterior, Direccion d) const;

    aed2_Fichin _fichin;
    vector<vector<TipoPosicion> > _mapaGrafico;
    Direccion _orientacion;
};

#endif // FICHINGRAFICO_H
