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

// Función principal para ejecutar las pruebas
int main() {
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"aaabcaabccaabcabcabcabc", "abc"},
        {"mimamamemima", "mima"},
        {"eseososeaseaasiasiseaseaeseoso", "sea"}
    };

    for (const auto& testCase : testCases) {
        std::vector<int> result = ZAlgorithmSearch(testCase.first, testCase.second);
        std::cout << "Resultados para la cadena \"" << testCase.first << "\" y subcadena \"" << testCase.second << "\":\n";
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
    }

    return 0;
}
