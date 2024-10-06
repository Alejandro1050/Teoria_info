#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream archivoOriginal("hola_mundo_cifrado.txt", std::ios::binary);
    std::ofstream archivoCifrado("archivo_cifrado.txt", std::ios::binary);
    std::string contenidoArchivo;
    char clave = ';';

    if (!archivoOriginal.is_open()) {
        std::cerr << "No se pudo abrir el archivo original" << std::endl;
        return 1;
    }

    // Lee todo el contenido del archivo original
    contenidoArchivo.assign((std::istreambuf_iterator<char>(archivoOriginal)),
                            std::istreambuf_iterator<char>());

    archivoOriginal.close();

    if (!archivoCifrado.is_open()) {
        std::cerr << "No se pudo abrir el archivo de cifrado" << std::endl;
        return 1;
    }

    // Cifra el contenido del archivo
    for (int k = 0; k < contenidoArchivo.size(); k++) {
        archivoCifrado << static_cast<char>(contenidoArchivo[k] ^ clave);
    }

    archivoCifrado.close();

    std::cout << "Cifrado realizado con éxito" << std::endl;

    return 0;
}
