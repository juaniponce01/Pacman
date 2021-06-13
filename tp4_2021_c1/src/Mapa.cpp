//
// Created by Juan Ponce on 12/06/2021.
//

#include "Mapa.h"
Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
           set<Coordenada> fantasmas, set<Coordenada> chocolates) :
            _largo(largo), _alto(alto),
            _inicio(inicio), _llegada(llegada),
            _paredes(paredes), _fantasmas(fantasmas), _chocolates(chocolates) {

    vector<char> columnasVacias(_alto, ' ');
    vector<vector<char>> filasYcolumnas(_largo, columnasVacias);
    _mapaDinamico = filasYcolumnas;

    for (Coordenada c: _paredes) {
        _mapaDinamico[c.first][c.second] = 'p';
    }

    for (Coordenada c: _fantasmas) {
        _mapaDinamico[c.first][c.second] = 'f';
    }

    for (Coordenada c: _chocolates) {
        _mapaDinamico[c.first][c.second] = 'c';
    }

}

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

const vector<vector<char>>& Mapa::mapaDinamico(){
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

void Mapa::agregarChocolate(Coordenada chocolate) {
    _mapaDinamico[chocolate.first][chocolate.second] = 'c';
}

void Mapa::quitarChocolate(Coordenada chocolate) {
    _mapaDinamico[chocolate.first][chocolate.second] = ' ';
}

Nat Mapa::distancia(Coordenada c1, Coordenada c2) {
    abs((int)c1.first - (int)c2.first) + abs((int)c1.second - (int)c2.second);
}

bool Mapa::hayFantasmaAMenosde3(Coordenada c) {
    bool res = false;
    for (int i = -3; i < 3; ++i) {
        for (int j = -3; j < 3; ++j) {
            if (abs(i) + abs(j) <= 3 && 0 <= c.first + i <= _mapaDinamico.size() &&
            0 <= c.second + j <= _mapaDinamico[0].size() && _mapaDinamico[i + c.first][j + c.second] == 'f'){
                res = true;
            }
        }
    }
    return res;
}