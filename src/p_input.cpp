#include "p_input.hpp"  //Inclui o arquivo de cabeçalho da classe 'p_input' para definir as funcionalidades de entrada e processamento.
#include <iostream>     //entrada/saída (std::cout e std::wcout).
#include <cstring>      //manipulação de strings em C (strcmp, etc.).
#include <locale>       //configurar e usar locais específicos (ex: suporte a caracteres Unicode).
#include <map>          //estrutura de dados mapa (associação chave-valor).
#include <string>       //manipulação de strings em C++.
#include <fstream>      //manipulação de arquivos.
#include <cwctype>      //funções de caractere amplo, como verificação de tipos (ex: iswalpha).
#include <codecvt>      //conversão entre formatos de codificação (usada para manipular UTF-8/UTF-16).
#include <vector>       //vetores (listas dinâmicas).
#include <algorithm>    //operações de ordenação e algoritmos padrão.

// Criação do namespace 'inp', que contém a classe 'p_input' e suas funções associadas.
namespace inp {

    // Construtor da classe 'p_input', inicializando os valores padrão: modo de ordenação (-ac), formato de saída (-csv),
    // e outras variáveis de contagem (caracteres, palavras, etc.) com zero.
    p_input::p_input()
        : modo_de_ordenacao{"-ac"}, formato_de_saida{"-csv"}, caracteres{0}, total_de_palavras{0}, palavras_distintas{0} {}

    // Função para processar os argumentos passados na linha de comando.
    void p_input::process_arg(int argc, char* argv[]) {
        // Se nenhum argumento for passado, exibe uma mensagem explicando o uso.
        if (argc == 1) {
            std::cout << "Informe um arquivo de texto para ser processado!\n";
            std::cout << "Opções permitidas:\n";
            std::cout << "-ac: Ordem alfabética crescente\n";
            std::cout << "-ad: Ordem alfabética decrescente\n";
            std::cout << "-nc: Ordem por número de ocorrências crescente\n";
            std::cout << "-nd: Ordem por número de ocorrências decrescente\n";
            std::cout << "-csv ou -html para definir o formato de saída.\n";
        } else {
            // Percorre os argumentos e identifica se são modos de ordenação, formato de saída ou o nome do arquivo.
            for (int i = 1; i < argc; ++i) {
                if (strcmp(argv[i], "-ac") == 0 || strcmp(argv[i], "-ad") == 0 ||
                    strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "-nd") == 0) {
                    modo_de_ordenacao = argv[i];  // Define o modo de ordenação.
                } else if (strcmp(argv[i], "-html") == 0 || strcmp(argv[i], "-csv") == 0) {
                    formato_de_saida = argv[i];   // Define o formato de saída.
                } else {
                    nome_do_arquivo = argv[i];    // Define o nome do arquivo a ser processado.
                }
            }
        }
    }

    // Função para processar o arquivo de entrada e contar caracteres e palavras.
    void p_input::process_input(const std::string& arquivo) {
        // Abre o arquivo em formato wide (suporte a Unicode).
        std::wifstream wif(arquivo);
        if (!wif.is_open()) {
            std::cout << "Não foi possível abrir o arquivo de entrada." << std::endl;
            return;
        }

        // Define o local como o padrão do sistema, para suporte a caracteres locais.
        auto Locale = std::locale("");
        wif.imbue(Locale);

        wchar_t ch;            // Armazena cada caractere lido.
        std::wstring palavra;   // Armazena palavras temporariamente.

        // Lê o arquivo caractere por caractere.
        while (wif.get(ch)) {
            if (iswalpha(ch)) { // Verifica se o caractere é uma letra.
                caracteres++;   // Incrementa o contador de caracteres.
                palavra += std::towlower(ch);  // Converte a letra para minúscula e a adiciona à palavra.
            } else if (!palavra.empty()) { // Se não for letra e houver uma palavra formada:
                ocorrencias[palavra]++;    // Incrementa o contador da palavra no mapa de ocorrências.
                total_de_palavras++;       // Incrementa o contador de palavras.
                palavra.clear();           // Limpa a variável palavra para a próxima leitura.
            }
        }

        // Se houver uma palavra ao final do arquivo, processa-a também.
        if (!palavra.empty()) {
            ocorrencias[palavra]++;
            total_de_palavras++;
        }

        palavras_distintas = ocorrencias.size();  // Conta quantas palavras distintas foram encontradas.
        wif.close();  // Fecha o arquivo.

        // Exporta os resultados no formato escolhido (CSV ou HTML).
        std::string nome_saida = "saida";
        if (formato_de_saida == "-csv") {
            exportar_csv(nome_saida + ".csv");
        } else if (formato_de_saida == "-html") {
            exportar_html(nome_saida + ".html");
        }
    }

    // Função para ordenar e exibir os resultados de acordo com o modo de ordenação escolhido.
    void p_input::ordenar_e_exibir(const std::map<std::wstring, int>& map_ref) {
        std::vector<std::pair<std::wstring, int>> vec(map_ref.begin(), map_ref.end());  // Transforma o mapa em vetor.

        // Verifica o modo de ordenação escolhido e aplica a ordenação correspondente.
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;  // Ordem alfabética crescente.
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;  // Ordem alfabética decrescente.
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;  // Ordem crescente por número de ocorrências.
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;  // Ordem decrescente por número de ocorrências.
            });
        }

        // Exibe o resultado ordenado.
        for (const auto& [palavra, contagem] : vec) {
            std::wcout << L"Palavra: " << palavra << L" | Ocorrências: " << contagem << std::endl;
        }
    }

    // Função para exportar os dados em formato CSV.
    void p_input::exportar_csv(const std::string& arquivo_saida) const {
        std::ofstream ofs(arquivo_saida);
        if (!ofs.is_open()) {
            std::cout << "Erro ao criar o arquivo CSV." << std::endl;
            return;
        }

        ofs << "Palavra,Ocorrências\n";  // Cabeçalho do CSV.

        // Ordena os dados com base no modo de ordenação e exporta.
        std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
        }

        // Converte para UTF-8 e escreve no arquivo.
        for (const auto& [palavra, contagem] : vec) {
            ofs << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "," << contagem << "\n";
        }

        ofs.close();
        std::cout << "Exportação para CSV concluída: " << arquivo_saida << std::endl;
    }

    // Função para exportar os dados em formato HTML.
    void p_input::exportar_html(const std::string& arquivo_saida) const {
        std::ofstream ofs(arquivo_saida);
        if (!ofs.is_open()) {
            std::cout << "Erro ao criar o arquivo HTML." << std::endl;
            return;
        }

        // Gera a estrutura básica de um arquivo HTML.
        ofs << "<html>\n<head>\n<title>Resultados da Contagem de Palavras</title>\n</head>\n<body>\n";
        ofs << "<h1>Resultados da Contagem de Palavras</h1>\n";
        ofs << "<table border='1'>\n<tr><th>Palavra</th><th>Ocorrências</th></tr>\n";

        // Ordena os dados e exporta para HTML.
        std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
        if (modo_de_ordenacao == "-ac") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;
            });
        } else if (modo_de_ordenacao == "-ad") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });
        } else if (modo_de_ordenacao == "-nc") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
        } else if (modo_de_ordenacao == "-nd") {
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
        }

        // Converte para UTF-8 e escreve no arquivo.
        for (const auto& [palavra, contagem] : vec) {
            ofs << "<tr>\n<td>" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "</td>\n";
            ofs << "<td>" << contagem << "</td>\n</tr>\n";
        }

        ofs << "</table>\n</body>\n</html>\n";
        ofs.close();
        std::cout << "Exportação para HTML concluída: " << arquivo_saida << std::endl;
    }

    // Funções 'getter' para acessar variáveis privadas.
    std::string p_input::get_modo_de_ordenacao() const {
        return modo_de_ordenacao;
    }

    std::string p_input::get_nome_do_arquivo() const {
        return nome_do_arquivo;
    }

    std::string p_input::get_formato_de_saida() const {
        return formato_de_saida;
    }

    int p_input::get_qtd_de_caracteres() const {
        return caracteres;
    }

    int p_input::get_total_de_palavras() const {
        return total_de_palavras;
    }

    int p_input::get_palavras_distintas() const {
        return palavras_distintas;
    }

    std::map<std::wstring, int> p_input::get_map() const {
        return ocorrencias;
    }

}
