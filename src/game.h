#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "piece.h"

class Juego {
private:
    Tablero* tablero;
    Pieza*   piezaActual;
    bool     gameOver; //es bool porque es mas eficiente para representar un binario

public:
    Juego();
    ~Juego();

    void iniciar();
    void procesarTurno();
    bool estaTerminado() const;

private:
    void generarNuevaPieza();
    void verificarGameOver();
    char leerEntrada() const; 
};

#endif // GAME_H
