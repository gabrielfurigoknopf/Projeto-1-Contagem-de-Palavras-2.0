#include "p_input.hpp" //arquivo de cabeçalho da classe 'p_input'.
#include <iostream>    //biblioteca padrão para entrada e saída (como std::cout e std::wcout).
#include <map>         //biblioteca de mapas, usada para armazenar pares chave-valor (neste caso, palavras e suas contagens).

int main(int argc, char* argv[]) {
    inp::p_input entrada; // Cria um objeto 'entrada' da classe 'p_input', que será responsável por processar os argumentos e o arquivo de entrada.

    // Processa os argumentos da linha de comando (argc e argv), para obter o nome do arquivo a ser lido.
    entrada.process_arg(argc, argv); 

    // Processa o arquivo cujo nome foi obtido no passo anterior, lendo o conteúdo do arquivo.
    entrada.process_input(entrada.get_nome_do_arquivo()); 

    // Obtém um mapa contendo as palavras (ou caracteres) como chaves e suas frequências como valores.
    std::map<std::wstring, int> map_ref = entrada.get_map();

    // Ordena o mapa (por ordem alfabética ou frequência, dependendo da implementação) e exibe os resultados para o usuário.
    entrada.ordenar_e_exibir(map_ref);

    //Exibe várias estatísticas sobre o arquivo processado:
    //O número total de caracteres lidos no arquivo.
    std::wcout << L"Número de caracteres lidos: " << entrada.get_qtd_de_caracteres() << std::endl

               //O número de palavras distintas (palavras únicas, sem repetição).
               << L"Número de palavras distintas: " << entrada.get_palavras_distintas() << std::endl

               //O número total de palavras (incluindo as repetições).
               << L"Número total de palavras: " << entrada.get_total_de_palavras() << std::endl;

    return 0; //Indica que o programa terminou com sucesso.
}
