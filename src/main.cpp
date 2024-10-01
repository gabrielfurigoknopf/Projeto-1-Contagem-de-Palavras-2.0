#include "p_input.hpp"
#include <iostream>
#include <map>

int main(int argc, char* argv[]) {
    inp::p_input entrada;

    entrada.process_arg(argc, argv);
    entrada.process_input(entrada.get_nome_do_arquivo());

    std::map<std::wstring, int> map_ref = entrada.get_map();

    for (const auto& [palavra, contagem] : map_ref) {
        std::wcout << L"Palavra: " << palavra << L" | Ocorrências: " << contagem << std::endl;
    }

    std::wcout << L"Número de caracteres lidos: " << entrada.get_qtd_caracteres() << std::endl
               << L"Número de palavras distintas: " << entrada.get_palavras_distintas() << std::endl
               << L"Número total de palavras: " << entrada.get_total_de_palavras() << std::endl;

    return 0;
}
