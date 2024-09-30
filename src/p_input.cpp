#include "p_input.hpp"
#include <iostream>
#include <cstring>
#include <locale>
#include <map>
#include <string>
#include <fstream>
#include <cwctype>

namespace inp {
    p_input::p_input()
        : modo_de_ordenacao{"-ac"}, formato_de_saida{"-csv"}, caracteres{0}, total_de_palavras{0}, palavras_distintas{0} {}

    void p_input::process_arg(int argc, char* argv[]) {
        if (argc == 1) {
            std::cout << "Informe um arquivo de texto para ser processado!\n";
            std::cout << "Opções permitidas:\n";
            std::cout << "1. Arquivo de entrada\n";
            std::cout << "2. Critério para exibir os dados na saída:\n";
            std::cout << "-ac: Ordenar palavras em ordem alfabética crescente\n";
            std::cout << "-ad: Ordenar palavras em ordem alfabética decrescente\n";
            std::cout << "-nc: Ordenar pelo número de ocorrências de forma crescente\n";
            std::cout << "-nd: Ordenar pelo número de ocorrências de forma decrescente\n";
            std::cout << "3. Formatos de exportação:\n";
            std::cout << "-csv\n";
            std::cout << "-html\n";
        } else {
            for (int i = 1; i < argc; ++i) {
                if (strcmp(argv[i], "-ac") == 0 || strcmp(argv[i], "-ad") == 0 || strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "-nd") == 0) {
                    modo_de_ordenacao = argv[i];
                } else if (strcmp(argv[i], "-html") == 0) {
                    formato_de_saida = "-html";
                } else {
                    nome_do_arquivo = argv[i];
                }
            }
        }
    }

    void p_input::process_input(const std::string& arquivo) {
        std::wifstream wif(arquivo);
        if (!wif.is_open()) {
            std::cout << "Não foi possível abrir o arquivo de entrada." << std::endl;
            return;
        }

        // Definindo a localização de acordo com o ambiente do sistema
        auto loc = std::locale("");
        wif.imbue(loc);

        wchar_t ch;
        std::wstring palavra;

        while (wif.get(ch)) {
            if (iswalpha(ch)) {
                caracteres++;
                palavra += std::towlower(ch);
            } else if (!palavra.empty()) {
                ocorrencias[palavra]++;
                total_de_palavras++;
                palavra.clear();
            }
        }

        // Processando a última palavra no final do arquivo
        if (!palavra.empty()) {
            ocorrencias[palavra]++;
            total_de_palavras++;
        }

        palavras_distintas = ocorrencias.size();
        wif.close();
    }
}
