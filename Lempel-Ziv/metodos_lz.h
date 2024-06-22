#ifndef METODOS_LZ_H
#define METODOS_LZ_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class metodos_lz{
    public:
    /* Método de Compresión
    * Comprime un mensaje utilizando un algoritmo LZ
    * mensaje: Cadena de texto a comprimir
    * return: Una cola de pares que representa el mensaje comprimido
    */
        static queue<pair<string, int>> comprimir(string& mensaje) {
            int size = mensaje.length();
            unordered_map<char, int> diccionario;
            queue<pair<string, int>> mensaje_comp;
            int k, aux_k, j, j_aux;
            char c;
            for (int i = 0; i < size; i++) {
                c = mensaje[i];
                if(diccionario.find(c) == diccionario.end()) {
                    diccionario[c] = i;
                    mensaje_comp.push(make_pair(string(1,c), 0));
                } else {
                    k = diccionario[c];
                    aux_k = k;
                    j = i;
                    j_aux = i;
                    for (j; j < size && k < j_aux; j++, k++) {
                        if (mensaje[k] != mensaje[j]) {
                            break;
                        }
                    }
                    mensaje_comp.push(make_pair(to_string(aux_k), j - i));
                    i = j - 1;
                }
            }

            return mensaje_comp;
        }
    /* Método de Descompresión
    * Descomprime un mensaje comprimido utilizando el formato de cola de pares
    * mensaje_comp: Cola de pares que representa el mensaje comprimido
    * return: Cadena de texto descomprimida
    */
        static string descomprimir(queue<pair<string, int>> mensaje_comp) {
            string mensaje_descomp;
            while(!mensaje_comp.empty()) {
                auto par = mensaje_comp.front();
                if(par.second == 0) {
                    mensaje_descomp += par.first;
                } else {
                    mensaje_descomp += mensaje_descomp.substr(stoi(par.first), par.second);
                }
                mensaje_comp.pop();
            }
            return mensaje_descomp;
        }
    /* Método para Calcular el Tamaño en Bytes del Mensaje Comprimido
    * Calcula el tamaño en bytes del mensaje comprimido
    * mensaje_comp: Cola de pares que representa el mensaje comprimido
    * return: Tamaño en bytes del mensaje comprimido
    */
        static size_t sizeBytes_mensaje_comp(queue<pair<string, int>> mensaje_comp) {
            return mensaje_comp.size() * sizeof(pair<char, int>);
        }

};

#endif
