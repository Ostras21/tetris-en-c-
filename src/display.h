#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"
#include "piece.h"

class Display {
public:
    Display();
    ~Display();

    void imprimirTablero(const Tablero& tablero, const Pieza& piezaActual) const;
    void imprimirMenu() const;
    void imprimirGameOver() const;
};

#endif // DISPLAY_H
