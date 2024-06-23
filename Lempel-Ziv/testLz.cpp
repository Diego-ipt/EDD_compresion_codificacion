#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "metodos_lz.h"
#include <chrono>
#include <cmath>
#include <queue>
#include<vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <tamaño en MB> <nombre del archivo>" << endl;
        return 1;
    }

    size_t MAX_SIZE = stoi(argv[1]) * 1024 * 1024; // Tamaño de texto a comprimir
    string fileName = argv[2]; // TEXTO A PROBAR .txt

    ifstream inputFile(fileName, ios::binary);
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    ostringstream buffer;
    char chunk[4096];
    size_t totalRead = 0;

    while (totalRead < MAX_SIZE && inputFile.read(chunk, min(sizeof(chunk), MAX_SIZE - totalRead))) {
        size_t bytesRead = inputFile.gcount();
        totalRead += bytesRead;
        buffer.write(chunk, bytesRead);
    }

    // Verificar si quedan bytes por leer después de salir del bucle
    if (totalRead < MAX_SIZE && inputFile) {
        inputFile.read(chunk, MAX_SIZE - totalRead);
        buffer.write(chunk, inputFile.gcount());
    }
    vector<double> duraciones;
    string contenido = buffer.str();
    queue<pair<string, int>> mensaje_comp;
    size_t bytes_comprimidos;
    for(int i=0; i < 5; i++){
        auto start = chrono::high_resolution_clock::now();
        mensaje_comp = metodos_lz::comprimir(contenido);
        auto end = chrono::high_resolution_clock::now();
        auto duration_open = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        duraciones.push_back(duration_open);
        if(i == 0) {
            bytes_comprimidos = metodos_lz::sizeBytes_mensaje_comp(mensaje_comp);
        }
    }

    // Calcular el promedio
    double suma = 0;
    for(const auto& duracion : duraciones) {
        suma += duracion;
    }
    double promedio = suma / duraciones.size();
    // Calcular la desviación estándar
    double suma_diferencias_cuadradas = 0;
    for(const auto& duracion : duraciones) {
        suma_diferencias_cuadradas += pow(duracion - promedio, 2);
    }
    double desviacion_estandar = sqrt(suma_diferencias_cuadradas / (duraciones.size() - 1));

    string tamaño_arch = string(argv[1]) + "MB";

    cout << fileName << "," << tamaño_arch << "," << bytes_comprimidos << "," << promedio << ","<< desviacion_estandar << ",";

    // Reiniciar el vector de duraciones para los tiempos de descompresión
    duraciones.clear();

    string mensaje_descomp;
    for(int i=0; i < 30; i++){
        auto start = chrono::high_resolution_clock::now();
        mensaje_descomp = metodos_lz::descomprimir(mensaje_comp);
        auto end = chrono::high_resolution_clock::now();
        auto duration_open = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        duraciones.push_back(duration_open);
    }
    // Calcular el promedio
    suma = 0;
    for(const auto& duracion : duraciones) {
        suma += duracion;
    }
    promedio = suma / duraciones.size();
    // Calcular la desviación estándar
    suma_diferencias_cuadradas = 0;
    for(const auto& duracion : duraciones) {
        suma_diferencias_cuadradas += pow(duracion - promedio, 2);
    }
    desviacion_estandar = sqrt(suma_diferencias_cuadradas / (duraciones.size() - 1));

    cout<< promedio<<","<<desviacion_estandar<<endl;

    inputFile.close();

    return 0;
}
