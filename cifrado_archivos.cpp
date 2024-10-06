#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::string mensaje = "mensaje original";
    std::string cifrado;

    char clave = ';';

    for (int k = 0; k < mensaje.length(); k++) {
        int val1 = static_cast<int>(clave);
        int val2 = static_cast<int>(mensaje[k]);

        cifrado += static_cast<char>(val1 ^ val2);
    }

    std::cout << "Mensaje original: " << mensaje << std::endl;
    std::cout << "Mensaje cifrado: " << cifrado << std::endl;

    return 0;
}

