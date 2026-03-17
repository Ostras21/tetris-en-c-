#include "game.h"

int main() {
    Juego juego;
    juego.iniciar();

    while (!juego.estaTerminado()) {
        juego.procesarTurno();
    }

    return 0;
}
