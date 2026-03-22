#include "display.h"
#include <QTextStream>

Display::Display()  {}
Display::~Display() {}

void Display::imprimirTablero(const Tablero& tablero, const Pieza& pieza) const {
    QTextStream salida(stdout);
    uint16_t forma = pieza.getForma();
    int posX = pieza.getPosX();
    int posY = pieza.getPosY();

    for (int y = 0; y < tablero.getAlto(); y++) {
        for (int x = 0; x < tablero.getAncho(); x++) {
            bool enTablero = tablero.celdaOcupada(x, y);
            bool enPieza   = false;

            int filaPieza = y - posY;
            int colPieza  = x - posX;

            if (filaPieza >= 0 && filaPieza < 4 && colPieza >= 0 && colPieza < 4) {
                int bitIndex = 15 - (filaPieza * 4 + colPieza);
                enPieza = (forma >> bitIndex) & 1;
            }

            if (enTablero || enPieza) {
                salida << "# ";
            } else {
                salida << ". ";
            }
        }
        salida << "\n";
    }
    salida.flush();
}

void Display::imprimirMenu() const {
    QTextStream salida(stdout);
    salida << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
    salida.flush();
}


void Display::imprimirGameOver() const {
    QTextStream salida(stdout);
    salida << "\n--- GAME OVER ---\n";
    salida.flush();
}
