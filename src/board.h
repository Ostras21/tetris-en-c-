#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
// modulo Tablero - Manejo del tablero con operaciones a nivel de bits
class Tablero {
private:
    uint8_t** filas;  //puntero a punteros
    int ancho;
    int alto;
    int bytesPorFila;

public:
    Tablero(int ancho, int alto);
    ~Tablero();

    bool hayColision(uint16_t pieza, int posX, int posY) const; //compara bits dee la pieza con los del tablero usando AND
    void fijarPieza(uint16_t pieza, int posX, int posY); //fiha la pieza al tablero usando or
    int limpiarFilasCompletas(); //elimina filas completas y reorganiza los punteros
    bool celdaOcupada(int x, int y) const; //consulta un bit específico con mascara
    bool filaCompleta(int fila) const; //verifica si todos los bits de una fila estan en 1 para luego elimianr
    void imprimir() const;

    int getAncho() const;
    int getAlto()  const;
};

#endif // BOARD_H
