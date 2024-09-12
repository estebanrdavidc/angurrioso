#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // Para std::srand y std::rand
#include <ctime>    // Para std::time

// Implementación de la clase Jugador

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

void Jugador::cargarEstado(std::istream& input) {
    input >> puntosTotales >> puntosRonda;
}

void Jugador::guardarEstado(std::ostream& output) const {
    output << puntosTotales << " " << puntosRonda << std::endl;
}

// Implementación de la clase Juego

Juego::Juego() : ronda(0) {
    std::srand(static_cast<unsigned int>(std::time(0)));  // Corrección aquí
}

void Juego::jugar() {
    while (jugador1.obtenerPuntosTotales() < 30 && jugador2.obtenerPuntosTotales() < 30) {
        jugarRonda();
        continuarOguardar();
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

void Juego::guardarPartida(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << ronda << std::endl;
        jugador1.guardarEstado(archivo);
        jugador2.guardarEstado(archivo);
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar." << std::endl;
    }
}

void Juego::cargarPartida(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo >> ronda;
        jugador1.cargarEstado(archivo);
        jugador2.cargarEstado(archivo);
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para cargar." << std::endl;
    }
}

void Juego::continuarOguardar() {
    std::cout << "¿Desea continuar o guardar la partida? (1 para continuar, 2 para guardar): ";
    int decision;
    std::cin >> decision;
    if (decision == 2) {
        std::string nombreArchivo;
        std::cout << "Ingrese el nombre del archivo para guardar: ";
        std::cin >> nombreArchivo;
        guardarPartida(nombreArchivo);
        std::cout << "Partida guardada con éxito." << std::endl;
    }
}
