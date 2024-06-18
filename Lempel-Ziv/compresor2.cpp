#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

queue<pair<char, int>> comprimir2(string& mensaje) {
    int size = mensaje.length();
    unordered_map<char, int> diccionario;
    queue<pair<char, int>> mensaje_comp;
    int k, aux_k, j, j2;
    char c, c_aux;
    string sub;
    for (int i = 0; i < size; i++) {
        c = mensaje[i];
        if(diccionario.find(c) == diccionario.end()) {
            diccionario[c] = i;
            mensaje_comp.push(make_pair(c, 0));
        } else {
            k = diccionario[c];
            aux_k = k;
            j = i;
            j2=i;
            sub="";
            for (j; j <= size && k<j2; j++, k++) {
                if (mensaje[k] == mensaje[j]) {
                    sub += mensaje[k];
                } else {
                    break;
                }
            }
            c_aux = aux_k + '0';
            mensaje_comp.push(make_pair(c_aux, j - i));
            i = j - 1;
        }
    }
    return mensaje_comp;
}

int main() {
    string cadena = "aaaa";
    auto value = comprimir2(cadena);
    //cout<<"escribe: \n";
    //cin>>cadena;
    while (!value.empty()) {
        auto par = value.front();
        value.pop();
        cout << "(" << par.first << "," << par.second << ")" << "   ";
    }

    return 0;
}