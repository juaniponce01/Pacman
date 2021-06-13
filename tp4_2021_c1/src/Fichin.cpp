#include "Fichin.h"

Fichin::Fichin(Partida partida, Jugador jugador):
    _partidaActual(partida), _jugador(jugador),
    _alguienJugando(true) //Empieza en true?
{}

Mapa Fichin::mapaAsociado() {
    return _partidaActual.mapa();
}
bool Fichin::alguienJugando() {
    return _alguienJugando;
}

Jugador Fichin::jugadorActual() {
    return _jugador;
}

Partida Fichin::partidaActual() {
    return _partidaActual;
}

Ranking Fichin::ranking() {

}

void Fichin::nuevaPartidaFichin(Jugador) {

}

void Fichin::moverFichin(Direccion) {

}

pair<Jugador, Nat> Fichin::objetivo() {

}

Jugador Fichin::oponente() {

}

set<Jugador> Fichin::oponentes() {

}

set<Jugador> Fichin::mejorQue(Ranking, set<Jugador>, Nat) {

}

set<Jugador> Fichin::peoresJugadores(Ranking, set<Jugador>) {

}

set<Jugador> Fichin::mejjugadoresConPuntaje(Ranking, set<Jugador>, Nat) {

}

Nat Fichin::peorPuntaje(Ranking, set<Jugador>) {

}