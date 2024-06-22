#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_lz.h"


using namespace std;

using namespace std;
const size_t MAX_SIZE = 20 * 1024 * 1024;
int main() {
    METODOS_LZ lz;
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

    // Ejemplo de uso de compresión y descompresión
    //string mensaje = "abracadabra";
    //cout << "Mensaje original: " << contenido << endl;

    // Comprimir el mensaje
    queue<pair<string, int>> mensaje_comp = lz.comprimir(contenido);
    string mensaje_descomp = lz.descomprimir(mensaje_comp);
    // Mostrar la cola de pares comprimidos
    //cout << "Mensaje comprimido (cola de pares): ";
    //while (!mensaje_comp.empty()) {
    //    auto par = mensaje_comp.front();
    //    cout << "(" << par.first << ", " << par.second << ") ";
    //    mensaje_comp.pop();
    //}
    //cout << endl;
    //cout << "Mensaje descomprimido: " << mensaje_descomp << endl;

    inputFile.close();

    return 0;
}
