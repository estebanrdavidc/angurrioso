#ifndef JUEGO_H
#define JUEGO_H

#include <string>

class Jugador {
public:
    Jugador();
    int obtenerPuntosTotales() const;
    void sumarPuntosTotales(int puntosGanados);
    void resetearPuntosRonda();
    void resetearPuntosTotales();
    void cargarEstado(std::istream& input);
    void guardarEstado(std::ostream& output) const;

private:
    int puntosTotales;
    int puntosRonda;
};

class Juego {
public:
    Juego();
    void jugar();
    void guardarPartida(const std::string& nombreArchivo) const;
    void cargarPartida(const std::string& nombreArchivo);

private:
    void jugarRonda();
    int lanzarDado() const;
    void anunciarGanador() const;
    void continuarOguardar();

    Jugador jugador1, jugador2;
    int ronda;
};

#endif // JUEGO_H

