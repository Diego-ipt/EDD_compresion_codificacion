#ifndef METODOS_HUFFMAN_H
#define METODOS_HUFFMAN_H


#include <iostream>
#include "Node.h"
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
#include "priorityQueueNode.h"

using namespace std;

class metodos_huffman {

    public:
        static pair<string, Node*> codificar(string& mensaje) {

            // PriorityQueue cola_p;
            priority_queue<Node*, vector<Node*>, Node::NodeComparator> cola_p;
            unordered_map<char, int> frecuencia_simbolos;
            unordered_map<char, Node*> hojas;
            unordered_map<char, string> diccionario;

            for(char simbolo : mensaje) {
                frecuencia_simbolos[simbolo]++;
            }

            for(auto& par : frecuencia_simbolos) {
                Node* hoja = new Node(par.first, par.second);
                cola_p.push(hoja);
                hojas[par.first] = hoja;
            }

            //si el mensaje está compuesto de un solo simbolo, se codifica la cadena como puros 0, y retorna  el arbol huffman (cola.top)
            if(cola_p.size() == 1) {
                string bits = string(mensaje.length(), '0');
                return make_pair(bits, cola_p.top());
            }

            while(cola_p.size() > 1) {
                Node* u = cola_p.top();
                cola_p.pop();
                Node* v = cola_p.top();
                cola_p.pop();
                Node* nodo_comb = Node::combine(u, v);
                cola_p.push(nodo_comb);
                // cout << "nodo 1: " << u->getSymbol() << " "<<  u->getFrecuency() << endl;
                // cout << "nodo 2: " <<  v->getSymbol() << " " << v->getFrecuency() << endl;
                // cout << "nodo comb: " <<  nodo_comb->getFrecuency() << endl;


            }

            Node* tree = cola_p.top();
            // cout << "nodo padre: " << tree->getSymbol() << " " <<  tree->getFrecuency() <<endl;

            for(auto& hoja : hojas) {
                string c;
                Node* u = hoja.second;
                //para cada hoja se obtiene su codigo binario
                while (u != tree) {
                    Node* parent = u->getParent();  
                    if(u == parent->getLeft()) {
                        c += '0';
                    } else if (u == parent->getRight()) {
                        c += '1';
                    }
                    u = parent;       
                }

                reverse(c.begin(), c.end());
                diccionario[hoja.first] = c;
                // cout << hoja.first << ": " << c << endl;
            }


            string mensaje_cod;

            for(char c : mensaje) {
                mensaje_cod += diccionario[c];
            }

            //se retorna el mensaje codificado, junto con el puntero a la raiz del arbol
            return make_pair(mensaje_cod, tree); 

        }

        static string decodificar(string& mensaje_cod, Node* tree) {
            string mensaje_decod;
            if(tree->is_leaf()) {
                mensaje_decod = string(mensaje_cod.length(), tree->getSymbol());
                return mensaje_decod;
            }

            Node* v = tree;

            for(char c : mensaje_cod) {
                if(c == '0') {
                    v = v->getLeft();
                } else {
                    v = v->getRight();
                }

                if(v->is_leaf()) {
                    mensaje_decod += v->getSymbol();
                    v = tree;
                }
            }

            return mensaje_decod;
        }

        static size_t sizeBits_mensaje_cod(string& mensaje_comp) {
            return mensaje_comp.size();
        }


};



#endif