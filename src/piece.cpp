#ifndef PIECE_H
#define PIECE_H

#include <stdint.h>

class Pieza {
private:
    uint16_t forma; //unit16 la pieza se representa en una cuadrícula lógica de 4x4 bits, exactamente 16 bits
    int posX;
    int posY;
    int tipoPieza; //no almacenamos las piezas pero necesitamss saber en cual estamos para
    int rotacionActual; //calcular la siguiente

public:
    Pieza(int ancho);
    ~Pieza();

    void rotar(uint8_t** filasTablero, int ancho, int alto);
    void moverIzquierda(uint8_t** filasTablero, int ancho, int alto);
    void moverDerecha(uint8_t** filasTablero, int ancho, int alto);
    void bajar(uint8_t** filasTablero, int ancho, int alto);

    uint16_t getForma()        const;
    int      getPosX()         const;
    int      getPosY()         const;
    int      getTipo()         const;
    int      getRotacion()     const;
};

#endif // PIECE_H
