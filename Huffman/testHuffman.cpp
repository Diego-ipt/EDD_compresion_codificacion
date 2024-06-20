#include <iostream>
#include <string>
#include "metodos_huffman.h"

using namespace std;

int main() {
    string cadena = "tangananica-tanganana";

    auto codificado = metodos_huffman::codificar(cadena);

    string mensaje_cod = codificado.first;

    auto decodificado = metodos_huffman::decodificar(mensaje_cod, codificado.second);

    string mensaje_decod = decodificado;

    cout << "mensaje original: " << cadena << endl;
    cout << "mensaje codificado: " << mensaje_cod << endl;
    cout << "mensaje decodificado: " << mensaje_decod << endl;
    cout << "size bits mensaje cod: " << cadena.size() * 8 << endl;
    cout << "size bits mensaje_decod: " << metodos_huffman::sizeBits_mensaje_comp(mensaje_cod) << endl;

    return 0;
}