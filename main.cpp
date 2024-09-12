#include <iostream>
#include "Juego.h"
#include "Juego.cpp"

int main() {
    Juego juego;
    int opcion;
    std::cout << "¿Desea iniciar un nuevo juego (1) o cargar una partida existente (2)? ";
    std::cin >> opcion;
    
    if (opcion == 2) {
        std::string nombreArchivo;
        std::cout << "Ingrese el nombre del archivo para cargar: ";
        std::cin >> nombreArchivo;
        juego.cargarPartida(nombreArchivo);
    }
    
    juego.jugar();
    
    return 0;
}
