#include "FichinGrafico.h"

using namespace std;

FichinGrafico::FichinGrafico(aed2_Fichin &f) : _fichin(f), _orientacion(DERECHA) {
    _mapaGrafico = vector<vector<TipoPosicion> >(f.largo() + 1, vector<TipoPosicion>(f.alto() + 1));
}

void FichinGrafico::nuevaPartida(Jugador j) {
    _fichin.nuevaPartida(j);
    actualizarMapaGrafico();
}

TipoPosicion FichinGrafico::tipoPosicion(int x, int y) const {
    return _mapaGrafico[x][y];
}

pair<ResultadoMovimiento, Coordenada> FichinGrafico::mover(Direccion d) {
    _orientacion = d;
    Coordenada posicion = _fichin.jugador();
    ResultadoMovimiento resultado = _fichin.mover(d);
    if (resultado == SIGUE) {
        actualizarMapaGrafico();
    } else if (resultado == PERDIO) {
        posicion = actualizarMovimientoPerdedor(posicion, d);
    } else if (resultado == GANO) {
        posicion = actualizarMovimientoGanador(posicion, d);
    }
    return {resultado, posicion};
}

Direccion FichinGrafico::orientacion() const {
    return _orientacion;
}

Nat FichinGrafico::cantidadMovimientos() const {
    return _fichin.cantidadMovimientos();
}

Nat FichinGrafico::inmunidad() const {
    if (_fichin.alguienJugando()) {
        return _fichin.inmunidad();
    } else {
        return 0;
    }
}

Nat FichinGrafico::largo() {
    return _fichin.largo();
}

Nat FichinGrafico::alto() {
    return _fichin.alto();
}

bool FichinGrafico::alguienJugando() const {
    return _fichin.alguienJugando();
}

set<pair<Puntaje, Jugador> > FichinGrafico::rankingOrdenado() const {
    map<Jugador, Puntaje> ranking = _fichin.ranking();
    set<pair<Puntaje, Jugador> > rankingOrdenado;
    for (const auto &par : ranking) {
        rankingOrdenado.insert({par.second, par.first});
    }
    return rankingOrdenado;
}

Jugador FichinGrafico::jugadorActual() const {
    return _fichin.jugadorActual();
}

bool FichinGrafico::jugadorEnRanking() const {
    return _fichin.ranking().count(_fichin.jugadorActual());
}

pair<Jugador, Puntaje> FichinGrafico::objetivo() const {
    return _fichin.objetivo();
}

void FichinGrafico::actualizarMapaGrafico() {
    for (int i = 1; i <= _fichin.largo(); ++i) {
        for (int j = 1; j <= _fichin.alto(); ++j) {
            _mapaGrafico[i][j] = Nada;
        }
    }
    for (Coordenada p : _fichin.paredes()) {
        _mapaGrafico[p.first][p.second] = Pared;
    }
    for (Coordenada p : _fichin.fantasmas()) {
        _mapaGrafico[p.first][p.second] = Fantasma;
    }
    for (Coordenada p : _fichin.chocolatesActuales()) {
        _mapaGrafico[p.first][p.second] = Chocolate;
    }
    _mapaGrafico[_fichin.llegada().first][_fichin.llegada().second] = Llegada;
    if (_mapaGrafico[_fichin.jugador().first][_fichin.jugador().second] == Fantasma) {
        _mapaGrafico[_fichin.jugador().first][_fichin.jugador().second] = FantasmaPosicion;
    } else {
        _mapaGrafico[_fichin.jugador().first][_fichin.jugador().second] = Posicion;
    }
}

Coordenada FichinGrafico::actualizarMovimientoPerdedor(Coordenada posicionAnterior, Direccion d) {
    if (_mapaGrafico[posicionAnterior.first][posicionAnterior.second] == Posicion) {
        _mapaGrafico[posicionAnterior.first][posicionAnterior.second] = Nada;
    } else if (_mapaGrafico[posicionAnterior.first][posicionAnterior.second] == FantasmaPosicion) {
        _mapaGrafico[posicionAnterior.first][posicionAnterior.second] = Fantasma;
    }
    Coordenada nuevaPosicion = posicionSiguiente(posicionAnterior, d);
    if (_mapaGrafico[nuevaPosicion.first][nuevaPosicion.second] == Nada) {
        _mapaGrafico[nuevaPosicion.first][nuevaPosicion.second] = Posicion;
    } else if (_mapaGrafico[nuevaPosicion.first][nuevaPosicion.second] == Fantasma) {
        _mapaGrafico[nuevaPosicion.first][nuevaPosicion.second] = FantasmaPosicion;
    }
    return nuevaPosicion;
}

Coordenada FichinGrafico::actualizarMovimientoGanador(Coordenada posicionAnterior, Direccion d) {
    if (_mapaGrafico[posicionAnterior.first][posicionAnterior.second] == Posicion) {
        _mapaGrafico[posicionAnterior.first][posicionAnterior.second] = Nada;
    } else if (_mapaGrafico[posicionAnterior.first][posicionAnterior.second] == FantasmaPosicion) {
        _mapaGrafico[posicionAnterior.first][posicionAnterior.second] = Fantasma;
    }
    Coordenada nuevaPosicion = posicionSiguiente(posicionAnterior, d);
    _mapaGrafico[nuevaPosicion.first][nuevaPosicion.second] = LlegadaPosicion;
    return nuevaPosicion;
}

Coordenada FichinGrafico::posicionSiguiente(Coordenada posicionAnterior, Direccion d) const {
    if (d == ARRIBA) {
        return {posicionAnterior.first, posicionAnterior.second + 1};
    } else if (d == ABAJO) {
        return {posicionAnterior.first, posicionAnterior.second - 1};
    } else if (d == IZQUIERDA) {
        return {posicionAnterior.first - 1, posicionAnterior.second};
    } else if (d == DERECHA) {
        return {posicionAnterior.first + 1, posicionAnterior.second};
    }
    assert(false);
}
