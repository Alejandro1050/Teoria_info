#include <iostream>
using namespace std;

struct Nodo {
    int id;
    string nombre;
    Nodo *izq;
    Nodo *der;
};

// Prototipos
void insertar(int, string, Nodo *);
void recorrerIn(Nodo *);
void recorrerPre(Nodo *);
void recorrerPos(Nodo *);
Nodo* buscar(Nodo *, int);
Nodo* eliminar(Nodo *, int);
Nodo* encontrarMinimo(Nodo *);

Nodo *raiz = NULL;

int main() {
    int id, op = 0;
    string na;

    do {
        cout << "1. Insertar" << endl;
        cout << "2. Mostrar (Inorden)" << endl;
        cout << "3. Mostrar (Preorden)" << endl;
        cout << "4. Mostrar (Postorden)" << endl;
        cout << "5. Buscar" << endl;
        cout << "6. Eliminar" << endl;
        cout << "0. Salir" << endl;
        cin >> op;

        switch (op) {
            case 1:
                cout << "Id: ";
                cin >> id;
                cout << "Nombre: ";
                cin >> na;
                insertar(id, na, raiz);
                break;
            case 2:
                recorrerIn(raiz);
                break;
            case 3:
                recorrerPre(raiz);
                break;
            case 4:
                recorrerPos(raiz);
                break;
            case 5:
                cout << "Id a buscar?: ";
                cin >> id;
                if (buscar(raiz, id) != NULL)
                    cout << "El Id " << id << " existe en el arbol." << endl;
                else
                    cout << "El Id " << id << " no se encontro." << endl;
                break;
            case 6:
                cout << "Id a eliminar: ";
                cin >> id;
                raiz = eliminar(raiz, id);
                break;
            default:
                break;
        }
    } while (op != 0);

    return 0;
}

// Función para insertar un nodo en el árbol
void insertar(int d, string n, Nodo *aux) {
    Nodo *nuevo = new Nodo();
    nuevo->id = d;
    nuevo->nombre = n;
    nuevo->izq = nuevo->der = NULL;

    if (raiz == NULL) {
        raiz = nuevo;
        return;
    }

    while (aux != NULL) {
        if (nuevo->id > aux->id) {
            if (aux->der == NULL) {
                aux->der = nuevo;
                return;
            } else {
                aux = aux->der;
            }
        } else if (nuevo->id < aux->id) {
            if (aux->izq == NULL) {
                aux->izq = nuevo;
                return;
            } else {
                aux = aux->izq;
            }
        } else if (nuevo->id == aux->id) {
            cout << "El Id " << nuevo->id << " ya está en el árbol." << endl;
            return;
        }
    }
}

// Función para recorrer el árbol en inorden
void recorrerIn(Nodo *aux) {
    if (aux == NULL) return;
    recorrerIn(aux->izq);
    cout << "Id: " << aux->id << " Nombre: " << aux->nombre << endl;
    recorrerIn(aux->der);
}

// Función para recorrer el árbol en preorden
void recorrerPre(Nodo *aux) {
    if (aux == NULL) return;
    cout << "Id: " << aux->id << " Nombre: " << aux->nombre << endl;
    recorrerPre(aux->izq);
    recorrerPre(aux->der);
}

// Función para recorrer el árbol en postorden
void recorrerPos(Nodo *aux) {
    if (aux == NULL) return;
    recorrerPos(aux->izq);
    recorrerPos(aux->der);
    cout << "Id: " << aux->id << " Nombre: " << aux->nombre << endl;
}

// Función para buscar un nodo en el árbol
Nodo* buscar(Nodo *aux, int id) {
    if (aux == NULL || aux->id == id) return aux;
    if (id < aux->id) return buscar(aux->izq, id);
    return buscar(aux->der, id);
}

// Función para eliminar un nodo del árbol
Nodo* eliminar(Nodo *aux, int id) {
    if (aux == NULL) return aux;

    if (id < aux->id) {
        aux->izq = eliminar(aux->izq, id);
    } else if (id > aux->id) {
        aux->der = eliminar(aux->der, id);
    } else {
        if (aux->izq == NULL) {
            Nodo *temp = aux->der;
            delete aux;
            return temp;
        } else if (aux->der == NULL) {
            Nodo *temp = aux->izq;
            delete aux;
            return temp;
        }

        Nodo *temp = encontrarMinimo(aux->der);
        aux->id = temp->id;
        aux->nombre = temp->nombre;
        aux->der = eliminar(aux->der, temp->id);
    }

    return aux;
}

// Función para encontrar el nodo con el valor mínimo
Nodo* encontrarMinimo(Nodo *aux) {
    while (aux && aux->izq != NULL) aux = aux->izq;
    return aux;
}
