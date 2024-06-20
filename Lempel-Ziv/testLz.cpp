#include <iostream>
#include <string>
#include "metodos_lz.h"


using namespace std;

int main() {

    string cadena = "bbbbbbbbbbbbbbbbbbbbbbbbabbbbbaaaaaaaa";

    auto value = comprimir(cadena);

    while(!value.empty()) {
        auto par = value.front();
        value.pop();

        cout << "(" << par.first << "," << par.second << ") ";
    }


    return 0;

}