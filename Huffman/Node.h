#ifndef NODE_H
#define NODE_H

class Node {

    private:
        char symbol;
        int frecuency; 
        Node* right;
        Node* left;
        Node* parent;

    public:
        Node(char symbol = '\0', int frecuency = 0, Node* right = nullptr, Node* left = nullptr){
            this->symbol = symbol;
            this->frecuency = frecuency;
            this->right = right;
            this->left = left;
            this->parent = nullptr;
        }

        static Node* combine(Node* u, Node* v) {
            Node* nodo = new Node('\0', u->frecuency + v->frecuency, u, v);
            u->parent = nodo;
            v->parent = nodo;
            return nodo;
        }

        bool is_leaf() {
            return left == nullptr && right == nullptr;
        }

        Node* getParent() {
            return parent;
        }

        Node* getLeft() {
            return left;
        }

        Node* getRight() {
            return right;
        }

        char getSymbol() {
            return symbol;
        }

        int getFrecuency() {
            return frecuency;
        }

        //Comparador personalizado
        struct NodeComparator {
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