#include <iostream>
#include <vector>
#include <string>

// Función para calcular la función Z
std::vector<int> calculateZ(const std::string& s) {
    int n = s.length();
    std::vector<int> Z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R] == s[R - L])
                ++R;
            Z[i] = R - L;
            --R;
        } else {
            int k = i - L;
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];
            else {
                L = i;
                while (R < n && s[R] == s[R - L])
                    ++R;
                Z[i] = R - L;
                --R;
            }
        }
    }
    return Z;
}

// Función para buscar la subcadena en la cadena utilizando el algoritmo de la función Z
std::vector<int> ZAlgorithmSearch(const std::string& text, const std::string& pattern) {
    std::string concat = pattern + "$" + text;
    std::vector<int> Z = calculateZ(concat);
    std::vector<int> result;

    int patternLength = pattern.length();
    for (int i = 0; i < Z.size(); ++i) {
        if (Z[i] == patternLength)
            result.push_back(i - patternLength - 1);
    }

    return result;
}

// Función principal para ejecutar las pruebas con la entrada del usuario
int main() {
    std::string text, pattern;
    char continuar;

    do {
        std::cout << "Ingresa la cadena principal: ";
        std::getline(std::cin, text);

        std::cout << "Ingresa la subcadena a buscar: ";
        std::getline(std::cin, pattern);

        std::vector<int> result = ZAlgorithmSearch(text, pattern);

        std::cout << "Resultados para la cadena \"" << text << "\" y subcadena \"" << pattern << "\":\n";
        if (result.empty()) {
            std::cout << "No se encontró la subcadena.\n";
        } else {
            std::cout << "Subcadena encontrada en las siguientes posiciones: ";
            for (int pos : result) {
                std::cout << pos << " ";
            }
            std::cout << "\n";
        }

        std::cout << "-----------------------------------\n";

        // Preguntar al usuario si quiere continuar con otro caso de prueba
        std::cout << "¿Quieres ingresar otro caso de prueba? (s/n): ";
        std::cin >> continuar;
        std::cin.ignore();  // Limpiar el buffer de entrada

    } while (continuar == 's' || continuar == 'S');

    std::cout << "Fin del programa.\n";
    return 0;
}