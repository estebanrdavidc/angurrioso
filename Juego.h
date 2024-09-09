#ifndef JUEGO_H
#define JUEGO_H

class Jugador {
public:
    Jugador();
    int obtenerPuntosTotales() const;
    void sumarPuntosTotales(int puntosGanados);
    void resetearPuntosRonda();
    void resetearPuntosTotales();

private:
    int puntosTotales;
    int puntosRonda;
};

class Juego {
public:
    Juego();
    void jugar();

private:
    void jugarRonda();
    int lanzarDado() const;
    void anunciarGanador() const;

    Jugador jugador1, jugador2;
    int ronda;
};

#endif // JUEGO_H
