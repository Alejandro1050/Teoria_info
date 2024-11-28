#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

struct nodo {
    float probabilidad;
    char letra;
    nodo* izquierdo;
    nodo* derecho;
};

// Funciones del árbol de Huffman
nodo* solicitarInfo();
void mostrarvec(vector<nodo*>& aux);
void ordenarPorProbabilidad(vector<nodo*>& vec);
void reducirVector(vector<nodo*>& vec);
void generarCodigos(nodo* raiz, const string& codigo, map<char, string>& codigos);

// Funciones para compresión y descompresión
map<char, int> generarFrecuencias(const string& archivo);
void comprimirArchivo(const string& archivo, const string& archivoComprimido, const map<char, string>& codigos);
void descomprimirArchivo(const string& archivoComprimido, const string& archivoDescomprimido, nodo* raiz);

// Métricas y utilidades
size_t obtenerTamanioArchivo(const string& archivo);
float calcularFactorCompresion(size_t original, size_t comprimido);
string cambiarExtension(const string& archivo, const string& nuevaExtension);

int main() {
    string archivoEntrada, archivoComprimido, archivoSalida;
    cout << "Introduce el nombre del archivo a comprimir: ";
    cin >> archivoEntrada;

    archivoComprimido = cambiarExtension(archivoEntrada, ".huf");
    archivoSalida = cambiarExtension(archivoEntrada, "_recuperado" + archivoEntrada.substr(archivoEntrada.find_last_of('.')));

    // Paso 1: Generar frecuencias
    map<char, int> frecuencias = generarFrecuencias(archivoEntrada);

    // Crear nodos para el árbol de Huffman
    vector<nodo*> vec;
    for (auto& par : frecuencias) {
        nodo* nuevo = new nodo();
        nuevo->probabilidad = par.second;
        nuevo->letra = par.first;
        nuevo->izquierdo = nuevo->derecho = nullptr;
        vec.push_back(nuevo);
    }

    // Paso 2: Construir el árbol de Huffman
    reducirVector(vec);
    nodo* raiz = vec[0];

    // Paso 3: Generar los códigos de Huffman
    map<char, string> codigos;
    generarCodigos(raiz, "", codigos);

    // Paso 4: Comprimir el archivo
    comprimirArchivo(archivoEntrada, archivoComprimido, codigos);

    // Paso 5: Descomprimir el archivo
    descomprimirArchivo(archivoComprimido, archivoSalida, raiz);

    // Paso 6: Calcular métricas
    size_t original = obtenerTamanioArchivo(archivoEntrada);
    size_t comprimido = obtenerTamanioArchivo(archivoComprimido);
    float factor = calcularFactorCompresion(original, comprimido);

    cout << "Tamanio original: " << original << " bytes\n";
    cout << "Tamanio comprimido: " << comprimido << " bytes\n";
    cout << "Factor de compresion: " << factor << "\n";

    return 0;
}

// Cambiar extensión del archivo
string cambiarExtension(const string& archivo, const string& nuevaExtension) {
    size_t pos = archivo.find_last_of('.');
    return archivo.substr(0, pos) + nuevaExtension;
}

// Generar frecuencias de los caracteres en el archivo
map<char, int> generarFrecuencias(const string& archivo) {
    map<char, int> frecuencias;
    ifstream file(archivo, ios::binary);
    char byte;

    while (file.get(byte)) {
        frecuencias[byte]++;
    }

    file.close();
    return frecuencias;
}

// Generar códigos de Huffman
void generarCodigos(nodo* raiz, const string& codigo, map<char, string>& codigos) {
    if (!raiz) return;

    if (!raiz->izquierdo && !raiz->derecho) {
        codigos[raiz->letra] = codigo;
    }

    generarCodigos(raiz->izquierdo, codigo + "0", codigos);
    generarCodigos(raiz->derecho, codigo + "1", codigos);
}

// Comprimir el archivo
void comprimirArchivo(const string& archivo, const string& archivoComprimido, const map<char, string>& codigos) {
    ifstream file(archivo, ios::binary);
    ofstream outFile(archivoComprimido, ios::binary);
    string buffer;
    char byte;

    while (file.get(byte)) {
        buffer += codigos.at(byte);

        while (buffer.size() >= 8) {
            bitset<8> bits(buffer.substr(0, 8));
            outFile.put(static_cast<unsigned char>(bits.to_ulong()));
            buffer = buffer.substr(8);
        }
    }

    if (!buffer.empty()) {
        while (buffer.size() < 8) buffer += "0";
        bitset<8> bits(buffer);
        outFile.put(static_cast<unsigned char>(bits.to_ulong()));
    }

    file.close();
    outFile.close();
}

// Descomprimir el archivo
void descomprimirArchivo(const string& archivoComprimido, const string& archivoDescomprimido, nodo* raiz) {
    ifstream file(archivoComprimido, ios::binary);
    ofstream outFile(archivoDescomprimido, ios::binary);
    nodo* actual = raiz;
    char byte;
    string bits;

    while (file.get(byte)) {
        bits += bitset<8>(static_cast<unsigned char>(byte)).to_string();

        for (char bit : bits) {
            actual = (bit == '0') ? actual->izquierdo : actual->derecho;

            if (!actual->izquierdo && !actual->derecho) {
                outFile.put(actual->letra);
                actual = raiz;
            }
        }
        bits.clear();
    }

    file.close();
    outFile.close();
}

// Obtener tamaño de un archivo
size_t obtenerTamanioArchivo(const string& archivo) {
    ifstream file(archivo, ios::binary | ios::ate);
    return file.tellg();
}

// Calcular el factor de compresión
float calcularFactorCompresion(size_t original, size_t comprimido) {
    return static_cast<float>(original) / comprimido;
}

// Reducir vector usando el árbol de Huffman
void reducirVector(vector<nodo*>& vec) {
    while (vec.size() > 1) {
        ordenarPorProbabilidad(vec);

        nodo* izq = vec[0];
        nodo* der = vec[1];

        nodo* nuevo = new nodo();
        nuevo->probabilidad = izq->probabilidad + der->probabilidad;
        nuevo->letra = '-';
        nuevo->izquierdo = izq;
        nuevo->derecho = der;

        vec.erase(vec.begin());
        vec.erase(vec.begin());
        vec.push_back(nuevo);
    }
}

// Ordenar el vector por probabilidad
void ordenarPorProbabilidad(vector<nodo*>& vec) {
    sort(vec.begin(), vec.end(), [](nodo* a, nodo* b) {
        return a->probabilidad < b->probabilidad;
    });
}
