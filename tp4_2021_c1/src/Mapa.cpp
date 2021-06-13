//
// Created by Juan Ponce on 12/06/2021.
//

#include "Mapa.h"
Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
           set<Coordenada> fantasmas, set<Coordenada> chocolates) : _alto(alto), _largo(largo), _inicio(inicio), _llegada(llegada),
           _paredes(paredes), _fantasmas(fantasmas), _chocolates(chocolates) { }

Nat Mapa::largo(){

};

Nat Mapa::alto(){

};

Coordenada Mapa::inicio(){

};

Coordenada Mapa::llegada(){

};

vector<vector<string>> Mapa::mapaDinamico(){

};

set<Coordenada> Mapa::chocolates(){

};

set<Coordenada> Mapa::paredes(){

};

set<Coordenada> Mapa::fantasmas(){

};