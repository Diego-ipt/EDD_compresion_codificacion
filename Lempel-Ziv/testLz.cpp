#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_lz.h"


using namespace std;

int main() {
    METODOS_LZ lz;
    ifstream archivo("entrada.txt");
    if(!archivo.is_open()){
        cerr << "No se pudo abrir el archivo. " << endl;
        return 1;
    }
    stringstream buffer;
    buffer << archivo.rdbuf();
    string contenido = buffer.str();

    // Ejemplo de uso de compresión y descompresión
    //string mensaje = "abracadabra";
    //cout << "Mensaje original: " << contenido << endl;

    // Comprimir el mensaje
    queue<pair<string, int>> mensaje_comp = lz.comprimir(contenido);
    string mensaje_descomp = lz.descomprimir(mensaje_comp);
    // Mostrar la cola de pares comprimidos
    cout << "Mensaje comprimido (cola de pares): ";
    while (!mensaje_comp.empty()) {
        auto par = mensaje_comp.front();
        cout << "(" << par.first << ", " << par.second << ") ";
        mensaje_comp.pop();
    }
    cout << endl;
    //cout << "Mensaje descomprimido: " << mensaje_descomp << endl;

    return 0;
}
}
