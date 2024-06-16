#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    char caracter;
    Node(int k, char c) : key(k), caracter(c), left(nullptr), right(nullptr), height(1) {}
};

// Función para obtener la altura de un nodo
int height(Node* N) {
    return N == nullptr ? 0 : N->height;
}

// Función para obtener el factor de balance de un nodo
int getBalanceFactor(Node* N) {
    return N == nullptr ? 0 : height(N->left) - height(N->right);
}

// Rotación a la derecha
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Devolver nueva raíz
    return x;
}

// Rotación a la izquierda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realizar la rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Devolver nueva raíz
    return y;
}

// Función para insertar un nodo y balancear el árbol AVL
Node* insert(Node* node, int key, char caracter) {
    // 1. Realizar la inserción normal en el árbol binario de búsqueda
    if (node == nullptr)
        return new Node(key, caracter);

    if (key < node->key)
        node->left = insert(node->left, key, caracter);
    else if (key > node->key)
        node->right = insert(node->right, key, caracter);
    else
        return node; // Claves duplicadas no permitidas

    // 2. Actualizar la altura del ancestro nodo
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance de este nodo ancestro para verificar si se desbalanceó
    int balanceFactor = getBalanceFactor(node);

    // Si el nodo se desbalancea, hay 4 casos

    // Caso Izquierda-Izquierda (LL)
    if (balanceFactor > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Derecha-Derecha (RR)
    if (balanceFactor < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Izquierda-Derecha (LR)
    if (balanceFactor > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Derecha-Izquierda (RL)
    if (balanceFactor < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Devolver el puntero al nodo (sin cambios)
    return node;
}

// Función para imprimir el árbol (en orden)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " " << root->caracter << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Insertar nodos en el árbol
    root = insert(root, 7, 't');
    root = insert(root, 6, 'a');
    root = insert(root, 3, 'k');

    // Imprimir el árbol en orden
    cout << "Inorder traversal of the AVL tree is: ";
    inorder(root);

    return 0;
}
