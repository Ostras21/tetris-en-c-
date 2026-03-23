#include "board.h"
#include <QTextStream>

Tablero::Tablero(int w, int h) {
    ancho = w;
    alto = h;
    bytesPorFila = ancho / 8; //construtor

    filas = new uint8_t*[alto];
    for (int i = 0; i < alto; i++) { //se inicia en 0 porqie el tablero esta vacio, de esta forma se evitan colisiones falsas por basura almacenada
        filas[i] = new uint8_t[bytesPorFila];
        for (int j = 0; j < bytesPorFila; j++) {
            filas[i][j] = 0;
        }
    }
}

Tablero::~Tablero() {    //destructor
    for (int i = 0; i < alto; i++) {
        delete[] filas[i];
    }
    delete[] filas;
}

bool Tablero::celdaOcupada(int x, int y) const {
    int indiceByte = x / 8;
    int indiceBit  = 7 - (x % 8);
    return (filas[y][indiceByte] >> indiceBit) & 1;
}

bool Tablero::filaCompleta(int fila) const {
    for (int i = 0; i < bytesPorFila; i++) {
        if (filas[fila][i] != 0xFF) {
            return false;
        }
    }
    return true;
}

bool Tablero::hayColision(uint16_t pieza, int posX, int posY) const {
    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            int bitIndex = 15 - (fila * 4 + col);
            if ((pieza >> bitIndex) & 1) {
                int x = posX + col;
                int y = posY + fila;
                if (x < 0 || x >= ancho || y < 0 || y >= alto) {
                    return true;
                }
                if (celdaOcupada(x, y)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Tablero::fijarPieza(uint16_t pieza, int posX, int posY) {
    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            int bitIndex = 15 - (fila * 4 + col);
            if ((pieza >> bitIndex) & 1) {
                int x = posX + col;
                int y = posY + fila;
                int indiceByte = x / 8;
                int indiceBit  = 7 - (x % 8);
                filas[y][indiceByte] |= (1 << indiceBit);
            }
        }
    }
}

int Tablero::limpiarFilasCompletas() {
    int filasEliminadas = 0;

    for (int i = alto - 1; i >= 0; i--) {  //se garantiza analizar de abajo hacia arriba las filas que ya estan completas
        if (filaCompleta(i)) {
            delete[] filas[i];
            filasEliminadas++;

            for (int j = i; j > 0; j--) {
                filas[j] = filas[j - 1]; //no se copian los bytes de cada fila, solo se reasignan los punteros
            }

            filas[0] = new uint8_t[bytesPorFila];
            for (int k = 0; k < bytesPorFila; k++) {
                filas[0][k] = 0;
            }
            i++;
        }
    }
    return filasEliminadas;
}

void Tablero::imprimir() const {
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            if (celdaOcupada(x, y)) {
                QTextStream(stdout) << "# ";
            } else {
                QTextStream(stdout) << ". ";
            }
        }
        QTextStream(stdout) << "\n";
    }
}

int Tablero::getAncho() const { return ancho; }
int Tablero::getAlto()  const { return alto;  }
