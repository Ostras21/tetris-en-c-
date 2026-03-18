#ifndef PIECE_H
#define PIECE_H

#include <stdint.h>
#include "board.h"

class Pieza {
private:
    uint16_t forma;
    int posX;
    int posY;
    int tipoPieza;
    int rotacionActual;

    uint16_t calcularForma(int tipo, int rotacion) const;

public:
    Pieza(int ancho);
    ~Pieza();

    void rotar(Tablero& tablero);
    void moverIzquierda(Tablero& tablero);
    void moverDerecha(Tablero& tablero);
    void bajar(Tablero& tablero);

    uint16_t getForma()    const;
    int      getPosX()     const;
    int      getPosY()     const;
    int      getTipo()     const;
    int      getRotacion() const;
};

#endif // PIECE_H
