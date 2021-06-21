#ifndef TP4_PACALGO2_MAPA_H
#define TP4_PACALGO2_MAPA_H

#include "Tipos.h"

class Mapa {
public:
    Mapa(Nat largo,
         Nat alto,
         Coordenada inicio,
         Coordenada llegada,
         set<Coordenada> paredes,
         set<Coordenada> fantasmas,
         set<Coordenada> chocolates);

    Nat largo();
    Nat alto();
    Coordenada inicio();
    Coordenada llegada();
    const vector<vector<char>>& mapaDinamico();
    const set<Coordenada>& chocolates();
    const set<Coordenada>& paredes();
    const set<Coordenada>& fantasmas();
    void agregarChocolate(Coordenada);
    void quitarChocolate(Coordenada);
    Nat distancia(Coordenada, Coordenada);
    bool hayFantasmaAMenosde3(Coordenada);

private:
    Nat _alto;
    Nat _largo;
    Coordenada _inicio;
    Coordenada _llegada;
    vector<vector<char>> _mapaDinamico;
    set<Coordenada> _chocolates;
    set<Coordenada> _paredes;
    set<Coordenada> _fantasmas;
};

#endif //TP4_PACALGO2_MAPA_H