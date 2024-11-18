#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Nodo del árbol de Huffman
struct HuffmanNode {
    char character;
    double probability;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, double prob) 
        : character(ch), probability(prob), left(nullptr), right(nullptr) {}
};

// Comparador para la cola de prioridad
struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->probability > b->probability;
    }
};

// Función para calcular las frecuencias de los caracteres
unordered_map<char, int> calculateFrequencies(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }
    return freq;
}

// Función para construir el árbol de Huffman
HuffmanNode* buildHuffmanTree(const unordered_map<char, double>& probabilities) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;

    for (const auto& pair : probabilities) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->probability + right->probability);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();
}

// Función para generar los códigos de Huffman
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->character != '\0') {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Función principal
int main() {
    string filename = "RUR.txt";
    

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    if (text.empty()) {
        cerr << "El archivo está vacío." << endl;
        return 1;
    }

    // Calcular frecuencias
    unordered_map<char, int> frequencies = calculateFrequencies(text);
    int totalCharacters = text.size();

    // Calcular probabilidades
    unordered_map<char, double> probabilities;
    for (const auto& pair : frequencies) {
        probabilities[pair.first] = static_cast<double>(pair.second) / totalCharacters;
    }

    // Construir el árbol de Huffman
    HuffmanNode* root = buildHuffmanTree(probabilities);

    // Generar códigos de Huffman
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Mostrar resultados
    cout << fixed << setprecision(4);
    cout << "\nProbabilidades y códigos de Huffman:\n";
    for (const auto& pair : probabilities) {
        cout << "Caracter: '" << (pair.first == '\n' ? "\\n" : string(1, pair.first))
             << "', Probabilidad: " << pair.second
             << ", Código de Huffman: " << huffmanCodes[pair.first] << endl;
    }

    return 0;
}
