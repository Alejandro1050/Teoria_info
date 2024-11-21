#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

struct nodo {
    float probabilidad;
    char letra;

    nodo *izquierdo;
    nodo *derecho;
};

nodo *solicitarInfo();
void mostrarvec(vector<nodo*> &aux);
int mostrarMenu();
void ordenarPorProbabilidad(vector<nodo*> &vec);
void reducirVector(vector<nodo*> &vec);

int main() {
    nodo *aux;
    int n;
    vector<nodo*> vec;

    do {
        n = mostrarMenu();
        switch (n) {
            case 1:
                aux = solicitarInfo();
                vec.push_back(aux);
                break;
            case 2:
                mostrarvec(vec);
                break;
            case 3:
                ordenarPorProbabilidad(vec);
                cout << "Vector ordenado por probabilidad.\n";
                mostrarvec(vec);
                break;
            case 4:
                reducirVector(vec);
                cout << "Reduccion del vector completada.\n";
                mostrarvec(vec);
                break;
        }
    } while (n != 0);

    // Liberar memoria
    for (auto nodo : vec) {
        delete nodo;
    }

    return 0;
}

nodo *solicitarInfo() {
    nodo *crear = new nodo();

    cout << "Introduce la probabilidad: ";
    cin >> crear->probabilidad;

    cout << "Introduce la letra: ";
    cin >> crear->letra;

    crear->izquierdo = NULL;
    crear->derecho = NULL;

    return crear;
}

int mostrarMenu() {
    int opc;
    cout << "Menu" << endl;
    cout << "Elige una opcion:" << endl;
    cout << "1. Crear Nodo" << endl;
    cout << "2. Mostrar Nodo" << endl;
    cout << "3. Ordenar por Probabilidad" << endl;
    cout << "4. Reducir Vector (Huffman)" << endl;
    cout << "0. Salir" << endl;

    cin >> opc;
    return opc;
}

void mostrarvec(vector<nodo*> &aux) {
    for (size_t i = 0; i < aux.size(); i++) {
        cout << "[" << i << "] Dir: " << aux[i] << endl;
        cout << "  Probabilidad: " << aux[i]->probabilidad << endl;
        cout << "  Letra: " << aux[i]->letra << endl;
    }
    cout << endl;
}

void ordenarPorProbabilidad(vector<nodo*> &vec) {
    sort(vec.begin(), vec.end(), [](nodo *a, nodo *b) {
        return a->probabilidad < b->probabilidad; // Orden ascendente
    });
}

void reducirVector(vector<nodo*> &vec) {
    while (vec.size() > 1) {
        // Ordenar el vector
        ordenarPorProbabilidad(vec);

        // Tomar los dos nodos con menor probabilidad
        nodo *izq = vec[0];
        nodo *der = vec[1];

        // Crear un nuevo nodo combinando las probabilidades
        nodo *nuevo = new nodo();
        nuevo->probabilidad = izq->probabilidad + der->probabilidad;
        nuevo->letra = '-'; // Nodo intermedio, sin letra
        nuevo->izquierdo = izq;
        nuevo->derecho = der;

        // Eliminar los dos nodos del vector
        vec.erase(vec.begin());
        vec.erase(vec.begin());

        // Insertar el nuevo nodo
        vec.push_back(nuevo);
    }
}
