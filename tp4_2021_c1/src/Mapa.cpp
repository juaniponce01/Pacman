//
// Created by Juan Ponce on 12/06/2021.
//

#include "Mapa.h"
Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
           set<Coordenada> fantasmas, set<Coordenada> chocolates) :
            _largo(largo), _alto(alto),
            _inicio(inicio), _llegada(llegada),
            _paredes(paredes), _fantasmas(fantasmas), _chocolates(chocolates) { }

Nat Mapa::largo(){
    return _largo;
};

Nat Mapa::alto(){
    return _alto;
};

Coordenada Mapa::inicio(){
    return _inicio;
};

Coordenada Mapa::llegada(){
    return _llegada;
};

const vector<vector<string>>& Mapa::mapaDinamico(){
    return _mapaDinamico;
};

const set<Coordenada>& Mapa::chocolates(){
    return _chocolates;
};

const set<Coordenada>& Mapa::paredes(){
    return _paredes;
};

const set<Coordenada>& Mapa::fantasmas(){
    return _fantasmas;
};

void Mapa::agregarChocolate(Coordenada chocoCoordenada) {
    _chocolates.insert(chocoCoordenada);
}

void Mapa::quitarChocolate(Coordenada chocoCoordenada) {
    _chocolates.erase(chocoCoordenada);
}

Nat Mapa::distancia(Coordenada coordenadaUno, Coordenada coordenadaDos) {

}

bool Mapa::hayFantasmaAMenosde3(Coordenada coordenada) {

}