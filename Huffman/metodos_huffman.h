#ifndef METODOS_HUFFMAN_H
#define METODOS_HUFFMAN_H


#include <iostream>
#include "Node.h"
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
    Clase que contiene los métodos de huffman codificar y decodificar, junto con un método que calcula el tamaño aproximado en bytes del mensaje codificado 
*/
class metodos_huffman {

public:
    /**
     * Codifica un mensaje utilizando el algoritmo de Huffman.
     * 
     * @param mensaje El mensaje a codificar.
     * @return Un par que contiene la cadena codificada y un puntero a la raíz del árbol de Huffman.
     */
    static pair<string, Node*> codificar(string& mensaje) {
        //se ocupa la priority_queue de la STL
        priority_queue<Node*, vector<Node*>, Node::NodeComparator> cola_p;
        //se ocupa la tabla hash de la STL
        unordered_map<char, int> frecuencia_simbolos;
        unordered_map<char, Node*> hojas;
        unordered_map<char, string> diccionario;

        // Contar y almacenar la frecuencia de cada símbolo en el mensaje.
        for (char simbolo : mensaje) {
            frecuencia_simbolos[simbolo]++;
        }

        // Crear una hoja para cada símbolo y añadirla a la cola de prioridad.
        for (auto& par : frecuencia_simbolos) {
            Node* hoja = new Node(par.first, par.second);
            cola_p.push(hoja);
            hojas[par.first] = hoja;
        }

        // Si el mensaje está compuesto de un solo símbolo, se codifica la cadena como puros 0s y se retorna el árbol de Huffman.
        if (cola_p.size() == 1) {
            string bits = string(mensaje.length(), '0');
            return make_pair(bits, cola_p.top());
        }

        // Construir el árbol de Huffman combinando nodos.
        while (cola_p.size() > 1) {
            Node* u = cola_p.top();
            cola_p.pop();
            Node* v = cola_p.top();
            cola_p.pop();
            Node* nodo_comb = Node::combine(u, v);
            cola_p.push(nodo_comb);
        }

        Node* tree = cola_p.top();

        // Generar el diccionario de códigos binarios para cada hoja.
        for (auto& hoja : hojas) {
            string c;
            Node* u = hoja.second;
            while (u != tree) {
                Node* parent = u->getParent();
                if (u == parent->getLeft()) {
                    c += '0';
                } else if (u == parent->getRight()) {
                    c += '1';
                }
                u = parent;
            }

            //se invierte para devolver el valor recorriendo el árbol desde la raíz
            reverse(c.begin(), c.end());
            diccionario[hoja.first] = c;
        }

        // Codificar el mensaje utilizando el diccionario.
        string mensaje_cod;
        for (char c : mensaje) {
            mensaje_cod += diccionario[c];
        }

        // Retornar el mensaje codificado y el puntero a la raíz del árbol.
        return make_pair(mensaje_cod, tree);
    }

    /**
     * Decodifica un mensaje codificado utilizando el algoritmo de Huffman.
     * 
     * @param mensaje_cod El mensaje codificado.
     * @param tree El puntero a la raíz del árbol de Huffman.
     * @return El mensaje decodificado.
     */
    static string decodificar(string& mensaje_cod, Node* tree) {
        string mensaje_decod;
        if (tree->is_leaf()) {
            mensaje_decod = string(mensaje_cod.length(), tree->getSymbol());
            return mensaje_decod;
        }

        Node* v = tree;

        // Decodificar el mensaje bit a bit recorriendo el árbol de Huffman.
        for (char c : mensaje_cod) {
            if (c == '0') {
                v = v->getLeft();
            } else {
                v = v->getRight();
            }

            if (v->is_leaf()) {
                mensaje_decod += v->getSymbol();
                v = tree;
            }
        }

        return mensaje_decod;
    }

    /**
     * Calcula el tamaño en bytes del mensaje codificado.
     * 
     * @param mensaje_comp El mensaje codificado.
     * @return El tamaño en bytes del mensaje codificado.
     */
    static size_t sizeBytes_mensaje_cod(string& mensaje_comp) {
        return mensaje_comp.size() / 8;
    }

};




#endif