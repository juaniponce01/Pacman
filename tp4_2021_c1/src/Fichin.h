#ifndef TP4_PACALGO2_FICHIN_H
#define TP4_PACALGO2_FICHIN_H
#include "Tipos.h"
#include "Partida.h" //Aca tambien incluyo mapa, esta bien?
#include "Mapa.h"

class Fichin {
public:
    Fichin(Partida partida, Jugador jugador);
    //~Fichin();

    Mapa mapaAsociado();
    bool alguienJugando();
    Jugador jugadorActual();
    Partida partidaActual();
    Ranking ranking();
    void nuevaPartidaFichin(Jugador);
    void moverFichin(Direccion);
    pair<Jugador, Nat> objetivo();
    Jugador oponente();
    set<Jugador> oponentes();
    set<Jugador> mejorQue(Ranking, set<Jugador>, Nat);
    set<Jugador> peoresJugadores(Ranking, set<Jugador>);
    set<Jugador> mejjugadoresConPuntaje(Ranking, set<Jugador>, Nat);
    Nat peorPuntaje(Ranking, set<Jugador>);

private:
    Partida _partidaActual;
    map<Jugador, Nat> _ranking;
    Jugador _jugador;
    bool _alguienJugando;
};


#endif //TP4_PACALGO2_FICHIN_H
