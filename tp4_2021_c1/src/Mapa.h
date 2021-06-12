//
// Created by Juan Ponce on 12/06/2021.
//

#ifndef TP4_PACALGO2_MAPA_H
#define TP4_PACALGO2_MAPA_H


class Mapa {
public:
    Mapa(Nat largo,
         Nat alto,
         Coordenada inicio,
         Coordenada llegada,
         set<Coordenada> paredes,
         set<Coordenada> fantasmas,
         set<Coordenada> chocolates)

    Nat largo();
    Nat alto();
    Coordenada inicio();
    Coordenada llegada();
    vector<vector<string>> mapaDinamico();
    set<Coordenada> chocolates();
    set<Coordenada> paredes();
    set<Coordenada> fantasmas();

private:
    Nat _alto;
    Nat _largo;
    Coordenada _inicio;
    Coordenada _llegada;
    vector<vector<string>> _mapaDinamico;
    set<Coordenada> _chocolates;
    set<Coordenada> _paredes;
    set<Coordenada> _fantasmas;

};


#endif //TP4_PACALGO2_MAPA_H
