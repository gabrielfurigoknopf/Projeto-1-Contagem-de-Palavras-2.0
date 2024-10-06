#include "p_input.hpp"  // Inclui o cabeçalho que define a classe 'p_input', onde estão as funções e atributos relacionados à entrada de dados.
#include <iostream>     // Inclui a biblioteca para operações de entrada e saída.
#include <cstring>      // Inclui a biblioteca para manipulação de strings C-style.
#include <locale>       // Inclui a biblioteca para suporte a diferentes locais de idiomas.
#include <map>         // Inclui a biblioteca para usar mapas (estrutura de dados que associa chaves a valores).
#include <string>      // Inclui a biblioteca para usar strings da classe std::string.
#include <fstream>     // Inclui a biblioteca para operações com arquivos.
#include <cwctype>     // Inclui a biblioteca para funções de manipulação de caracteres wide (largos).
#include <codecvt>     // Inclui a biblioteca para conversões entre diferentes tipos de codificação de texto.
#include <vector>      // Inclui a biblioteca para usar vetores, que são listas dinâmicas.
#include <algorithm>   // Inclui a biblioteca que fornece algoritmos como sort().

namespace inp { // Inicia um espaço de nomes para evitar conflitos de nomes.

    // Construtor da classe p_input, inicializa as variáveis com valores padrão.
    p_input::p_input()
        : modo_de_ordenacao{"-ac"}, formato_de_saida{"-csv"}, caracteres{0}, total_de_palavras{0}, palavras_distintas{0} {}

    // Método para processar os argumentos da linha de comando.
    void p_input::process_arg(int argc, char* argv[]) {
        if (argc == 1) { // Se não houver argumentos além do nome do programa
            std::cout << "Informe um arquivo de texto para ser processado!\n";
            std::cout << "Opções permitidas:\n";
            std::cout << "-ac: Ordem alfabética crescente\n";
            std::cout << "-ad: Ordem alfabética decrescente\n";
            std::cout << "-nc: Ordem por número de ocorrências crescente\n";
            std::cout << "-nd: Ordem por número de ocorrências decrescente\n";
            std::cout << "-csv ou -html para definir o formato de saída.\n";
        } else {
            // Processa cada argumento passado pelo usuário.
            for (int i = 1; i < argc; ++i) {
                // Verifica se o argumento é um modo de ordenação
                if (strcmp(argv[i], "-ac") == 0 || strcmp(argv[i], "-ad") == 0 ||
                    strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "-nd") == 0) {
                    modo_de_ordenacao = argv[i]; // Define o modo de ordenação baseado no argumento
                } 
                // Verifica se o argumento é um formato de saída
                else if (strcmp(argv[i], "-html") == 0 || strcmp(argv[i], "-csv") == 0) {
                    formato_de_saida = argv[i]; // Define o formato de saída baseado no argumento
                } 
                // Assume que o argumento restante é o nome do arquivo
                else {
                    nome_do_arquivo = argv[i];
                }
            }
        }
    }

    // Método para processar o conteúdo do arquivo fornecido.
    void p_input::process_input(const std::string& arquivo) {
        std::wifstream wif(arquivo); // Cria um fluxo de entrada para ler o arquivo no formato wide.
        if (!wif.is_open()) { // Verifica se o arquivo foi aberto com sucesso
            std::cout << "Não foi possível abrir o arquivo de entrada." << std::endl;
            return; // Se não abrir, encerra a função
        }

        auto Locale = std::locale(""); // Define o local para suportar a leitura de caracteres especiais
        wif.imbue(Locale); // Aplica o local ao fluxo de entrada

        wchar_t ch; // Variável para armazenar cada caractere lido
        std::wstring palavra; // Variável para construir palavras

        // Lê o arquivo caractere por caractere
        while (wif.get(ch)) {
            if (iswalpha(ch)) { // Se o caractere for uma letra
                caracteres++; // Incrementa o contador de caracteres
                palavra += std::towlower(ch); // Converte o caractere para minúsculo e adiciona à palavra
            } else if (!palavra.empty()) { // Se encontrar um caractere que não é uma letra e a palavra não estiver vazia
                ocorrencias[palavra]++; // Incrementa a contagem da palavra no mapa de ocorrências
                total_de_palavras++; // Incrementa o total de palavras
                palavra.clear(); // Limpa a palavra para construir uma nova
            }
        }

        // Caso a última palavra tenha sido lida, incrementa sua contagem
        if (!palavra.empty()) {
            ocorrencias[palavra]++;
            total_de_palavras++;
        }

        palavras_distintas = ocorrencias.size(); // Armazena o número de palavras distintas
        wif.close(); // Fecha o arquivo

        std::string nome_saida = "saida"; // Nome base do arquivo de saída
        // Exporta os dados no formato escolhido pelo usuário
        if (formato_de_saida == "-csv") {
            exportar_csv(nome_saida + ".csv");
        } else if (formato_de_saida == "-html") {
            exportar_html(nome_saida + ".html");
        }
    }

    // Método para ordenar e exibir as palavras e suas ocorrências.
    void p_input::ordenar_e_exibir(const std::map<std::wstring, int>& map_ref) {
        // Cria um vetor de pares a partir do mapa para facilitar a ordenação
        std::vector<std::pair<std::wstring, int>> vec(map_ref.begin(), map_ref.end());

        // Aplica a ordenação com base no modo de ordenação definido
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first; // Ordem alfabética crescente
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first; // Ordem alfabética decrescente
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second; // Ordem por número de ocorrências crescente
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second; // Ordem por número de ocorrências decrescente
            });
        }

        // Exibe as palavras e suas contagens no console
        for (const auto& [palavra, contagem] : vec) {
            std::wcout << L"Palavra: " << palavra << L" | Ocorrências: " << contagem << std::endl;
        }
    }

    // Método para exportar os resultados em formato CSV.
    void p_input::exportar_csv(const std::string& arquivo_saida) const {
        std::ofstream ofs(arquivo_saida); // Cria um fluxo de saída para escrever no arquivo CSV
        if (!ofs.is_open()) { // Verifica se o arquivo foi aberto com sucesso
            std::cout << "Erro ao criar o arquivo CSV." << std::endl;
            return; // Se não abrir, encerra a função
        }

        ofs << "Palavra,Ocorrências\n"; // Escreve o cabeçalho do CSV

        // Cria um vetor de pares e ordena conforme o modo de ordenação
        std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
        
        // Aplica a ordenação conforme o modo de ordenação selecionado
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first; // Ordem alfabética crescente
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first; // Ordem alfabética decrescente
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second; // Ordem por número de ocorrências crescente
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second; // Ordem por número de ocorrências decrescente
            });
        }

        // Escreve as palavras e suas contagens no arquivo CSV
        for (const auto& [palavra, contagem] : vec) {
            ofs << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "," << contagem << "\n";
        }

        ofs.close(); // Fecha o arquivo
        std::cout << "Exportação para CSV concluída: " << arquivo_saida << std::endl; // Informa que a exportação foi concluída
    }

    // Método para exportar os resultados em formato HTML.
    void p_input::exportar_html(const std::string& arquivo_saida) const {
        std::ofstream ofs(arquivo_saida); // Cria um fluxo de saída para escrever no arquivo HTML
        if (!ofs.is_open()) { // Verifica se o arquivo foi aberto com sucesso
            std::cout << "Erro ao criar o arquivo HTML." << std::endl;
            return; // Se não abrir, encerra a função
        }

        // Escreve o cabeçalho HTML
        ofs << "<html>\n<head>\n<title>Resultados da Contagem de Palavras</title>\n</head>\n<body>\n";
        ofs << "<h1>Resultados da Contagem de Palavras</h1>\n";
        ofs << "<table border='1'>\n<tr><th>Palavra</th><th>Ocorrências</th></tr>\n";

        // Cria um vetor de pares e ordena conforme o modo de ordenação
        std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
        
        // Aplica a ordenação conforme o modo de ordenação selecionado
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first; // Ordem alfabética crescente
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first; // Ordem alfabética decrescente
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second; // Ordem por número de ocorrências crescente
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second; // Ordem por número de ocorrências decrescente
            });
        }

        // Escreve as palavras e suas contagens no arquivo HTML
        for (const auto& [palavra, contagem] : vec) {
            ofs << "<tr>\n<td>" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "</td>\n";
            ofs << "<td>" << contagem << "</td>\n</tr>\n";
        }

        ofs << "</table>\n</body>\n</html>\n"; // Finaliza a estrutura HTML
        ofs.close(); // Fecha o arquivo
        std::cout << "Exportação para HTML concluída: " << arquivo_saida << std::endl; // Informa que a exportação foi concluída
    }

    // Métodos getters para acessar os atributos da classe.
    std::string p_input::get_modo_de_ordenacao() const {
        return modo_de_ordenacao; // Retorna o modo de ordenação
    }

    std::string p_input::get_nome_do_arquivo() const {
        return nome_do_arquivo; // Retorna o nome do arquivo
    }

    std::string p_input::get_formato_de_saida() const {
        return formato_de_saida; // Retorna o formato de saída
    }

    int p_input::get_qtd_de_caracteres() const {
        return caracteres; // Retorna a quantidade de caracteres lidos
    }

    int p_input::get_total_de_palavras() const {
        return total_de_palavras; // Retorna o total de palavras
    }

    int p_input::get_palavras_distintas() const {
        return palavras_distintas; // Retorna a quantidade de palavras distintas
    }

    std::map<std::wstring, int> p_input::get_map() const {
        return ocorrencias; // Retorna o mapa de ocorrências de palavras
    }

} // Fim do namespace inp
