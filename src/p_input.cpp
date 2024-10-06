 #include "p_input.hpp"
#include <iostream>
#include <cstring>
#include <locale>
#include <map>
#include <string>
#include <fstream>
#include <cwctype>
#include <codecvt>
#include <vector>
#include <algorithm>

namespace inp {

    p_input::p_input()
        : modo_de_ordenacao{"-ac"}, formato_de_saida{"-csv"}, caracteres{0}, total_de_palavras{0}, palavras_distintas{0} {}

    void p_input::process_arg(int argc, char* argv[]) {
        if (argc == 1) {
            std::cout << "Informe um arquivo de texto para ser processado!\n";
            std::cout << "Opções permitidas:\n";
            std::cout << "-ac: Ordem alfabética crescente\n";
            std::cout << "-ad: Ordem alfabética decrescente\n";
            std::cout << "-nc: Ordem por número de ocorrências crescente\n";
            std::cout << "-nd: Ordem por número de ocorrências decrescente\n";
            std::cout << "-csv ou -html para definir o formato de saída.\n";
        } else {
            for (int i = 1; i < argc; ++i) {
                if (strcmp(argv[i], "-ac") == 0 || strcmp(argv[i], "-ad") == 0 ||
                    strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "-nd") == 0) {
                    modo_de_ordenacao = argv[i];
                } else if (strcmp(argv[i], "-html") == 0 || strcmp(argv[i], "-csv") == 0) {
                    formato_de_saida = argv[i];
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

        auto Locale = std::locale("");
        wif.imbue(Locale);

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

        if (!palavra.empty()) {
            ocorrencias[palavra]++;
            total_de_palavras++;
        }

        palavras_distintas = ocorrencias.size();
        wif.close();

        std::string nome_saida = "saida";
        if (formato_de_saida == "-csv") {
            exportar_csv(nome_saida + ".csv");
        } else if (formato_de_saida == "-html") {
            exportar_html(nome_saida + ".html");
        }
    }

    // Ordenar e exibir de acordo com o modo de ordenação fornecido
    void p_input::ordenar_e_exibir(const std::map<std::wstring, int>& map_ref) {
        std::vector<std::pair<std::wstring, int>> vec(map_ref.begin(), map_ref.end());

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

        for (const auto& [palavra, contagem] : vec) {
            std::wcout << L"Palavra: " << palavra << L" | Ocorrências: " << contagem << std::endl;
        }
    }

    void p_input::exportar_csv(const std::string& arquivo_saida) const {
    std::ofstream ofs(arquivo_saida);
    if (!ofs.is_open()) {
        std::cout << "Erro ao criar o arquivo CSV." << std::endl;
        return;
    }

    ofs << "Palavra,Ocorrências\n";

    // Criar um vetor de pares e ordenar conforme o modo de ordenação
    std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
    
    // Aplicar a ordenação conforme o modo de ordenação selecionado
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

    for (const auto& [palavra, contagem] : vec) {
        ofs << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "," << contagem << "\n";
    }

    ofs.close();
    std::cout << "Exportação para CSV concluída: " << arquivo_saida << std::endl;
}

void p_input::exportar_html(const std::string& arquivo_saida) const {
    std::ofstream ofs(arquivo_saida);
    if (!ofs.is_open()) {
        std::cout << "Erro ao criar o arquivo HTML." << std::endl;
        return;
    }

    ofs << "<html>\n<head>\n<title>Resultados da Contagem de Palavras</title>\n</head>\n<body>\n";
    ofs << "<h1>Resultados da Contagem de Palavras</h1>\n";
    ofs << "<table border='1'>\n<tr><th>Palavra</th><th>Ocorrências</th></tr>\n";

    // Criar um vetor de pares e ordenar conforme o modo de ordenação
    std::vector<std::pair<std::wstring, int>> vec(ocorrencias.begin(), ocorrencias.end());
    
    // Aplicar a ordenação conforme o modo de ordenação selecionado
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

    for (const auto& [palavra, contagem] : vec) {
        ofs << "<tr>\n<td>" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "</td>\n";
        ofs << "<td>" << contagem << "</td>\n</tr>\n";
    }

    ofs << "</table>\n</body>\n</html>\n";
    ofs.close();
    std::cout << "Exportação para HTML concluída: " << arquivo_saida << std::endl;
}

    // Getters
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