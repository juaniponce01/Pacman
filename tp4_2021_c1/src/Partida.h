#ifndef TP4_PACALGO2_PARTIDA_H
#define TP4_PACALGO2_PARTIDA_H
#include "Tipos.h"
#include "Mapa.h"

class Partida {
public:
    Partida(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
            set<Coordenada> fantasmas, set<Coordenada> chocolates);
    //~Partida();
    Mapa mapa();
    Coordenada jugador();
    set<Coordenada> chocolates();
    Nat cantMov();
    Nat inmunidad();
    void nuevaPartida(Mapa);
    void mover(Direccion);
    bool gano();
    bool perdio();
    Coordenada siguienteMovimiento(Direccion);
    Coordenada posMovimiento(Direccion);
    Coordenada restringirMovimiento(Direccion);

private:
    Mapa _mapaAsociado;
    Coordenada _jugador;
    Nat _cantMov;
    Nat _inmunidad;
    bool _gano;
    bool _perdio;
};


#endif //TP4_PACALGO2_PARTIDA_H
