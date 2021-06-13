#include "Partida.h"

Partida::Partida(Mapa mapa):
        _mapaAsociado(mapa), _jugador(mapa.inicio()),
        _cantMov(0), _inmunidad(0),
        _gano(false), _perdio(false)
{}

Mapa Partida::mapa() {
    return _mapaAsociado;
}
Coordenada Partida::jugador() {
    return _jugador;
}
set<Coordenada> Partida::chocolates() {
    return _mapaAsociado.chocolates();
}
Nat Partida::cantMov() {
    return _cantMov;
}
Nat Partida::inmunidad() {
    return _inmunidad;
}
void Partida::nuevaPartida(Mapa map) {

}
void Partida::mover(Direccion direccion) {

}
bool Partida::gano() {
    return _gano;
}
bool Partida::perdio() {
    return _perdio;
}
Coordenada Partida::siguienteMovimiento(Direccion) {

}
Coordenada Partida::posMovimiento(Direccion) {

}
Coordenada Partida::restringirMovimiento(Direccion) {

}