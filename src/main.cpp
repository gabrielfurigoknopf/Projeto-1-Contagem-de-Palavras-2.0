#include "p_input.hpp"  // Inclui o cabeçalho que contém a definição da classe 'p_input'.
#include <iostream>     // Inclui a biblioteca para entrada e saída padrão.
#include <map>         // Inclui a biblioteca para utilizar mapas (ou dicionários) que relacionam chaves a valores.

int main(int argc, char* argv[]) {
    inp::p_input entrada;  // Cria uma instância da classe 'p_input' para lidar com a entrada de dados.

    entrada.process_arg(argc, argv);  // Processa os argumentos da linha de comando fornecidos ao programa.
    entrada.process_input(entrada.get_nome_do_arquivo());  // Lê e processa o conteúdo do arquivo cujo nome foi obtido anteriormente.

    std::map<std::wstring, int> map_ref = entrada.get_map();  // Obtém um mapa que relaciona palavras (como chaves) à sua contagem (como valores).

    // Ordena e exibe os resultados armazenados no mapa.
    entrada.ordenar_e_exibir(map_ref);

    // Exibe no console o número de caracteres lidos, palavras distintas e total de palavras.
    std::wcout << L"Número de caracteres lidos: " << entrada.get_qtd_de_caracteres() << std::endl
               << L"Número de palavras distintas: " << entrada.get_palavras_distintas() << std::endl
               << L"Número total de palavras: " << entrada.get_total_de_palavras() << std::endl;

    return 0;  
}
