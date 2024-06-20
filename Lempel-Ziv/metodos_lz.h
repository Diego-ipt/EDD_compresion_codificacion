#ifndef METODOS_LZ_H
#define METODOS_LZ_H


#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <queue>


using namespace std;


queue<pair<string, int>> comprimir(string& mensaje) {
    int size = mensaje.length();
    unordered_map<char, int> diccionario;
    queue<pair<string, int>> mensaje_comp;
    int k, aux_k, j, j_aux;
    char c;
    string sub;
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
                if (mensaje[k] == mensaje[j]) {
                    sub += mensaje[k];
                } else {
                    break;
                }
            }
            mensaje_comp.push(make_pair(to_string(aux_k), j - i));
            i = j - 1;
        }
    }

    return mensaje_comp;
}



#endif