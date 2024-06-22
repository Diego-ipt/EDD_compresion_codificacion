#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_huffman.h"
#include <chrono>

using namespace std;
const size_t MAX_SIZE = 20 * 1024 * 1024;
int main() {
    ifstream inputFile("entrada.txt", ios::binary);
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    ostringstream buffer;
    char chunk[4096];
    size_t totalRead = 0;

    while (inputFile.read(chunk, sizeof(chunk))) {
        size_t bytesRead = inputFile.gcount();
        totalRead += bytesRead;
        buffer.write(chunk, bytesRead);
        if (totalRead >= MAX_SIZE) {
            break;
        }
    }
    if (totalRead < MAX_SIZE) {
        inputFile.read(chunk, MAX_SIZE - totalRead);
        buffer.write(chunk, inputFile.gcount());
    }
    string contenido = buffer.str();

    //string cadena = "tangananica-tanganana";
    auto start = std::chrono::high_resolution_clock::now();

    auto codificado = metodos_huffman::codificar(contenido);
    string mensaje_cod = codificado.first;
    auto decodificado = metodos_huffman::decodificar(mensaje_cod, codificado.second);
    string mensaje_decod = decodificado;
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    //cout << "Tiempo de ejecución: " << elapsed.count() << " ms" << endl;

    //cout << "mensaje original: " << contenido << endl;
    //cout << "mensaje codificado: " << mensaje_cod << endl;
    //cout << "mensaje decodificado: " << mensaje_decod << endl;
    cout << "size bits mensaje cod: " << contenido.size() * 8 << endl;
    cout << "size bits mensaje_decod: " << metodos_huffman::sizeBits_mensaje_comp(mensaje_cod) << endl;
    inputFile.close(); 

    return 0;
}
