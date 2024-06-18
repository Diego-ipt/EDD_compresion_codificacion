#include <iostream>
#include <string>
#include "metodos_huffman.h"

using namespace std;

int main() {
    string cadena = "tangananica-tanganana";

    auto codificado = codificar(cadena);

    string mensaje_cod = codificado.first;

    auto decodificado = decodificar(mensaje_cod, codificado.second);

    string mensaje_decod = decodificado;

    cout << "mensaje original: " << cadena << endl;
    cout << "mensaje codificado: " << mensaje_cod << endl;
    cout << "mensaje decodificado: " << mensaje_decod << endl;

    return 0;
}