#include <iostream>
#include <fstream> // Para ler os arquivos e operações de entrada e saída.
#include <cctype> // Biblioteca para funções de manipulação de caracteres.
#include <map>
#include <string> // Para manipulação de strings.

int main() {
    std::ifstream arq("gpl.txt"); // ifstream --> input file stream
    std::ofstream csv("palavras.csv");

    // Verifica se os arquivos foram abertos corretamente.
    if (!arq.is_open() || !csv.is_open()) {
        std::cerr << "Erro ao abrir arquivos." << std::endl;
        return 1; // Retorna um código de erro apropriado.
    }

    char ch; // Armazena cada caractere lido do arquivo.
    std::string palavra; // Armazena a palavra acumulada.
    std::map<std::string, int> ocorrencias; // Armazena palavras e a quantidade de vezes que aparecem.

    while (arq.get(ch)) { // Lê caractere por caractere do arquivo "gpl.txt".
        if (std::isalpha(ch)) { // isalpha verifica se o caractere é uma letra.
            palavra += std::tolower(ch); // Converte o caractere para minúsculo e acumula na string.
        } else if (palavra.size() > 0) { // Verifica se tem alguma palavra acumulada.
            ocorrencias[palavra]++; // Incrementa o contador dessa palavra no mapa.
            palavra.clear(); // Limpa a variável "palavra" para começar a próxima.
        }
    }

    // Para a última palavra, se o arquivo não terminar com um delimitador.
    if (!palavra.empty()) {
        ocorrencias[palavra]++;
    }

    csv << "\"Palavra\";\"N\"\n"; // Coloca o cabeçalho do arquivo CSV (as colunas "Palavra" e "N" para contagem).
    for (const auto& [k, v] : ocorrencias) { 
        csv << '"' << k << '"' << ";" << v << std::endl; // Escrevemos a palavra e sua contagem de ocorrências.
    }

    return 0; // Finaliza o programa com sucesso.
}
