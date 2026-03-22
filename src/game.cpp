#include "game.h"
#include "display.h"
#include <QTextStream>
#include <ctime>

Juego::Juego() {
    srand(static_cast<unsigned int>(time(0)));

    int ancho = 0;
    int alto  = 0;

    QTextStream salida(stdout);
    QTextStream entrada(stdin);

    salida << "Ingrese el ancho del tablero (multiplo de 8, minimo 8): ";
    salida.flush();
    entrada >> ancho;

    while (ancho < 8 || ancho % 8 != 0) {
        salida << "Ancho invalido. Ingrese un multiplo de 8 mayor o igual a 8: ";
        salida.flush();
        entrada >> ancho;
    }

    salida << "Ingrese el alto del tablero (minimo 8): ";
    salida.flush();
    entrada >> alto;

    while (alto < 8) {
        salida << "Alto invalido. Ingrese un valor mayor o igual a 8: ";
        salida.flush();
        entrada >> alto;
    }

    tablero     = new Tablero(ancho, alto);
    piezaActual = new Pieza(ancho);
    gameOver    = false;
}

Juego::~Juego() {
    delete tablero;
    delete piezaActual;
}

bool Juego::estaTerminado() const {
    return gameOver;
}

void Juego::iniciar() {
    Display display;
    display.imprimirTablero(*tablero, *piezaActual);
}

char Juego::leerEntrada() const {
    char accion;
    QTextStream entrada(stdin);
    QTextStream salida(stdout);
    salida << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
    salida.flush();
    entrada >> accion;
    return accion;
}

void Juego::generarNuevaPieza() {
    delete piezaActual;
    piezaActual = new Pieza(tablero->getAncho());
}

void Juego::verificarGameOver() {
    if (tablero->hayColision(piezaActual->getForma(),
                             piezaActual->getPosX(),
                             piezaActual->getPosY())) {
        gameOver = true;
    }
}

void Juego::procesarTurno() {
    Display display;
    char accion = leerEntrada();

    if      (accion == 'a' || accion == 'A') piezaActual->moverIzquierda(*tablero);
    else if (accion == 'd' || accion == 'D') piezaActual->moverDerecha(*tablero);
    else if (accion == 's' || accion == 'S') piezaActual->bajar(*tablero);
    else if (accion == 'w' || accion == 'W') piezaActual->rotar(*tablero);
    else if (accion == 'q' || accion == 'Q') { gameOver = true; return; }

    if (tablero->hayColision(piezaActual->getForma(),
                             piezaActual->getPosX(),
                             piezaActual->getPosY() + 1)) {
        tablero->fijarPieza(piezaActual->getForma(),
                            piezaActual->getPosX(),
                            piezaActual->getPosY());
        tablero->limpiarFilasCompletas();
        generarNuevaPieza();
        verificarGameOver();
    }
    display.imprimirTablero(*tablero, *piezaActual);

    if (gameOver) display.imprimirGameOver();
}
