#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Jugador::Jugador() : puntosTotales(0), puntosRonda(0) {}

int Jugador::obtenerPuntosTotales() const {
    return puntosTotales;
}

void Jugador::sumarPuntosTotales(int puntosGanados) {
    puntosTotales += puntosGanados;
}

void Jugador::resetearPuntosRonda() {
    puntosRonda = 0;
}

void Jugador::resetearPuntosTotales() {
    puntosTotales = 0;
}

Juego::Juego() : ronda(0) {
    std::srand(std::time(0));
}

void Juego::jugar() {
    while (jugador1.obtenerPuntosTotales() < 30 && jugador2.obtenerPuntosTotales() < 30) {
        jugarRonda();
        ronda++;
    }
    anunciarGanador();
}

void Juego::jugarRonda() {
    for (int turno = 1; turno <= 2; ++turno) {
        std::cout << "Turno del jugador " << turno << std::endl;
        Jugador& jugadorActual = (turno == 1) ? jugador1 : jugador2;
        jugadorActual.resetearPuntosRonda();
        bool continuar = true;
        while (continuar) {
            std::cout << "Lanzar dado (1) o Retirarse (2): ";
            int decision;
            std::cin >> decision;
            if (decision == 1) {
                int dado = lanzarDado();
                if (dado == 6) {
                    std::cout << "¡Sacaste un 6! Perdiste todos los puntos de esta ronda." << std::endl;
                    jugadorActual.resetearPuntosRonda();
                    continuar = false;
                } else {
                    std::cout << "Sacaste un " << dado << std::endl;
                    jugadorActual.sumarPuntosTotales(dado);
                }
            } else {
                continuar = false;
            }
        }
        std::cout << "Puntos totales del jugador " << turno << " después de esta ronda: " << jugadorActual.obtenerPuntosTotales() << std::endl;
    }
}

int Juego::lanzarDado() const {
    return std::rand() % 6 + 1;
}

void Juego::anunciarGanador() const {
    if (jugador1.obtenerPuntosTotales() >= 30) {
        std::cout << "¡El Jugador 1 ha ganado!" << std::endl;
    } else if (jugador2.obtenerPuntosTotales() >= 30) {
        std::cout << "¡El Jugador 2 ha ganado!" << std::endl;
    }
}

