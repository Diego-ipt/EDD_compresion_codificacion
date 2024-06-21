#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_lz.h"


using namespace std;

int main() {
    // Ejemplo de uso de compresión y descompresión
    ifstream file("english50mb.txt"); // Abrir el archivo
    if (!file) {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    ostringstream ss;
    ss << file.rdbuf(); // Leer el archivo completo en el stringstream

    string mensaje = ss.str(); // Convertir el contenido a string

    //cout << "Mensaje original: " << mensaje << endl;

    // Comprimir el mensaje
    queue<pair<string, int>> mensaje_comp = metodos_lz::comprimir(mensaje);
    string mensaje_descomp = metodos_lz::descomprimir(mensaje_comp);
    size_t tam_mensaje_comp = metodos_lz::sizeBytes_mensaje_comp(mensaje_comp);
    // Mostrar la cola de pares comprimidos
    cout << "Mensaje comprimido (cola de pares): ";
    while (!mensaje_comp.empty()) {
        auto par = mensaje_comp.front();
        cout << "(" << par.first << ", " << par.second << ") ";
        mensaje_comp.pop();
    }
    cout << endl;
    cout << "Mensaje descomprimido: " << mensaje_descomp << endl;


    cout << "size bytes mensaje original: " << mensaje.size() << endl;
    cout << "size bytes mensaje comprimido: " << tam_mensaje_comp;

    return 0;
}