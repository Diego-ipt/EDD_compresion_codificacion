#ifndef NODE_H
#define NODE_H

/*
    Clase que representa los nodos del árbol de huffman
*/
class Node {
private:
    char symbol;       // Símbolo que contiene el nodo
    int frecuency;     // Frecuencia del símbolo
    Node* right;       // Puntero al hijo derecho
    Node* left;        // Puntero al hijo izquierdo
    Node* parent;      // Puntero al nodo padre

public:
    /**
     * Constructor de la clase Node.
     * 
     * @param symbol El símbolo que este nodo representa.
     * @param frecuency La frecuencia del símbolo.
     * @param right Puntero al hijo derecho.
     * @param left Puntero al hijo izquierdo.
     */
    Node(char symbol = '\0', int frecuency = 0, Node* right = nullptr, Node* left = nullptr) {
        this->symbol = symbol;
        this->frecuency = frecuency;
        this->right = right;
        this->left = left;
        this->parent = nullptr;
    }

    /**
     * Combina dos nodos en un solo nodo.
     * 
     * @param u Puntero al primer nodo.
     * @param v Puntero al segundo nodo.
     * @return Un nuevo nodo que combina la frecuencia del símbolo de los nodos u y v.
     */
    static Node* combine(Node* u, Node* v) {
        Node* nodo = new Node('\0', u->frecuency + v->frecuency, u, v);
        u->parent = nodo;
        v->parent = nodo;
        return nodo;
    }

    /**
     * Verifica si el nodo es una hoja.
     * 
     * @return true si el nodo es una hoja, false en caso contrario.
     */
    bool is_leaf() {
        return left == nullptr && right == nullptr;
    }

    /**
     * Obtiene el nodo padre.
     * 
     * @return Puntero al nodo padre.
     */
    Node* getParent() {
        return parent;
    }

    /**
     * Obtiene el hijo izquierdo.
     * 
     * @return Puntero al hijo izquierdo.
     */
    Node* getLeft() {
        return left;
    }

    /**
     * Obtiene el hijo derecho.
     * 
     * @return Puntero al hijo derecho.
     */
    Node* getRight() {
        return right;
    }

    /**
     * Obtiene el símbolo del nodo.
     * 
     * @return El símbolo del nodo.
     */
    char getSymbol() {
        return symbol;
    }

    /**
     * Obtiene la frecuencia del nodo.
     * 
     * @return La frecuencia del nodo.
     */
    int getFrecuency() {
        return frecuency;
    }

    /**
     * Estructura NodeComparator para comparar dos nodos.
     */
    struct NodeComparator {
        /**
         * Operador de comparación para los nodos.
         * 
         * @param lhs Puntero al primer nodo.
         * @param rhs Puntero al segundo nodo.
         * @return true si la frecuencia del primer nodo es mayor que la del segundo nodo, o si las frecuencias son iguales y el símbolo del primer nodo es mayor que el del segundo.
         */
        bool operator()(Node* lhs, Node* rhs) const {
            if (lhs->getFrecuency() != rhs->getFrecuency()) {
                return lhs->getFrecuency() > rhs->getFrecuency();
            } else {
                return lhs->getSymbol() > rhs->getSymbol();
            }
        }
    };

    // bool operator<(const Node& other) const {
    // if (frecuency != other.frecuency)
    //     return frecuency < other.frecuency;  // menor a mayor gravedad
    // else
    //     return symbol < other.symbol;
    // }
};


#endif