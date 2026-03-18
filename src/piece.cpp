#include "piece.h"
#include <QTextStream>
#include <cstdlib>

Pieza::Pieza(int ancho) {
    tipoPieza      = rand() % 7;
    rotacionActual = 0;
    posX           = (ancho / 2) - 2;
    posY           = 0;
    forma          = calcularForma(tipoPieza, rotacionActual);
}

Pieza::~Pieza() {}

uint16_t Pieza::getForma()    const { return forma;          }
int      Pieza::getPosX()     const { return posX;           }
int      Pieza::getPosY()     const { return posY;           }
int      Pieza::getTipo()     const { return tipoPieza;      }
int      Pieza::getRotacion() const { return rotacionActual; }

uint16_t Pieza::calcularForma(int tipo, int rotacion) const {
    uint16_t base;
    if      (tipo == 0) base = 0x0F00; // I
    else if (tipo == 1) base = 0x6600; // O
    else if (tipo == 2) base = 0x0E40; // T
    else if (tipo == 3) base = 0x06C0; // S
    else if (tipo == 4) base = 0x0C60; // Z
    else if (tipo == 5) base = 0x44C0; // J
    else                base = 0x4460; // L

    uint16_t resultado = base;
    for (int r = 0; r < rotacion; r++) {
        uint16_t temporal = 0;
        for (int fila = 0; fila < 4; fila++) {
            for (int col = 0; col < 4; col++) {
                int bitEntrada = 15 - (fila * 4 + col);
                if ((resultado >> bitEntrada) & 1) {
                    int bitSalida = 15 - (col * 4 + (3 - fila));
                    temporal |= (1 << bitSalida);
                }
            }
        }
        resultado = temporal;
    }
    return resultado;
}

void Pieza::rotar(Tablero& tablero) {
    int nuevaRotacion = (rotacionActual + 1) % 4;
    uint16_t nuevaForma = calcularForma(tipoPieza, nuevaRotacion);
    if (!tablero.hayColision(nuevaForma, posX, posY)) {
        rotacionActual = nuevaRotacion;
        forma = nuevaForma;
    }
}

void Pieza::moverIzquierda(Tablero& tablero) {
    if (!tablero.hayColision(forma, posX - 1, posY)) {
        posX--;
    }
}

void Pieza::moverDerecha(Tablero& tablero) {
    if (!tablero.hayColision(forma, posX + 1, posY)) {
        posX++;
    }
}

void Pieza::bajar(Tablero& tablero) {
    if (!tablero.hayColision(forma, posX, posY + 1)) {
        posY++;
    }
}
