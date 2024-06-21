#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_huffman.h"

using namespace std;

int main() {
    ifstream archivo("entrada.txt");
    if(!archivo.is_open()){
        cerr << "No se pudo abrir el archivo. " << endl;
        return 1;
    }
    stringstream buffer;
    buffer << archivo.rdbuf();
    string contenido = buffer.str();

    //string cadena = "tangananica-tanganana";

    auto codificado = metodos_huffman::codificar(contenido);

    string mensaje_cod = codificado.first;

    auto decodificado = metodos_huffman::decodificar(mensaje_cod, codificado.second);

    string mensaje_decod = decodificado;

    //cout << "mensaje original: " << contenido << endl;
    cout << "mensaje codificado: " << mensaje_cod << endl;
    //cout << "mensaje decodificado: " << mensaje_decod << endl;
    cout << "size bits mensaje cod: " << contenido.size() * 8 << endl;
    cout << "size bits mensaje_decod: " << metodos_huffman::sizeBits_mensaje_comp(mensaje_cod) << endl;

    return 0;
}
