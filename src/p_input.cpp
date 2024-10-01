#include "p_input.hpp"
#include <iostream>
#include <cstring>
#include <locale>
#include <map>
#include <string>
#include <fstream>
#include <cwctype>
#include <codecvt>

namespace inp {

    // Construtor inicializando os valores padrão para o modo de ordenação, formato de saída e contadores
    p_input::p_input()
        : modo_de_ordenacao{"-ac"}, formato_de_saida{"-csv"}, caracteres{0}, total_de_palavras{0}, palavras_distintas{0} {}

    // Função para processar argumentos da linha de comando
    void p_input::process_arg(int argc, char* argv[]) {
        if (argc == 1) {
            // Caso nenhum argumento seja passado, exibe as instruções de uso
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
            // Processa os argumentos fornecidos
            for (int i = 1; i < argc; ++i) {
                // Verifica o critério de ordenação (alfabética ou por número de ocorrências)
                if (strcmp(argv[i], "-ac") == 0 || strcmp(argv[i], "-ad") == 0 || 
                    strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "-nd") == 0) {
                    modo_de_ordenacao = argv[i];
                }
                // Verifica o formato de saída (CSV ou HTML)
                else if (strcmp(argv[i], "-html") == 0) {
                    formato_de_saida = "-html";
                } else if (strcmp(argv[i], "-csv") == 0) {
                    formato_de_saida = "-csv";
                }
                // Caso não seja nem critério de ordenação nem formato de saída, assume que é o nome do arquivo
                else {
                    nome_do_arquivo = argv[i];
                }
            }
        }
    }

    // Função para processar o arquivo de entrada e contar palavras e caracteres
    void p_input::process_input(const std::string& arquivo) {
        // Abre o arquivo para leitura no formato wide (suporta caracteres Unicode)
        std::wifstream wif(arquivo);
        if (!wif.is_open()) {
            std::cout << "Não foi possível abrir o arquivo de entrada." << std::endl;
            return;
        }

        // Configura a localização para suportar adequadamente caracteres especiais (Unicode)
        auto Locale = std::locale("");
        wif.imbue(Locale);

        wchar_t ch;
        std::wstring palavra;

        // Loop para ler o arquivo caractere por caractere
        while (wif.get(ch)) {
            // Verifica se o caractere é uma letra (alfa) e converte para minúscula
            if (iswalpha(ch)) {
                caracteres++;  // Incrementa o contador de caracteres
                palavra += std::towlower(ch);  // Concatena o caractere à palavra, convertendo para minúsculo
            } 
            // Quando encontra um separador (espaço, pontuação, etc.), processa a palavra
            else if (!palavra.empty()) {
                ocorrencias[palavra]++;  // Incrementa o contador da palavra no mapa
                total_de_palavras++;     // Incrementa o contador total de palavras
                palavra.clear();         // Limpa a palavra para iniciar a próxima
            }
        }

        // Processa a última palavra no final do arquivo (se houver)
        if (!palavra.empty()) {
            ocorrencias[palavra]++;
            total_de_palavras++;
        }

        // Conta o número de palavras distintas (o tamanho do mapa)
        palavras_distintas = ocorrencias.size();
        
        // Saindo do arquivo após o processamento
        wif.close();  

        // Exportando os resultados
        std::string nome_saida = "saida";
        if (formato_de_saida == "-csv") {
            exportar_csv(nome_saida + ".csv");
        } else if (formato_de_saida == "-html") {
            exportar_html(nome_saida + ".html");
        }
    }

    void p_input::exportar_csv(const std::string& arquivo_saida) const {
        std::ofstream ofs(arquivo_saida);
        if (!ofs.is_open()) {
            std::cout << "Erro ao criar o arquivo CSV." << std::endl;
            return;
        }

        ofs << "Palavra,Ocorrências\n"; // Cabeçalho do CSV
        for (const auto& [palavra, contagem] : ocorrencias) {
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

        // Escrevendo o cabeçalho HTML
        ofs << "<html>\n<head>\n<title>Resultados da Contagem de Palavras</title>\n</head>\n<body>\n";
        ofs << "<h1>Resultados da Contagem de Palavras</h1>\n";
        ofs << "<table border='1'>\n<tr><th>Palavra</th><th>Ocorrências</th></tr>\n";

        // Adicionando dados ao corpo do HTML
        for (const auto& [palavra, contagem] : ocorrencias) {
            ofs << "<tr>\n";
            ofs << "<td>" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(palavra) << "</td>\n";
            ofs << "<td>" << contagem << "</td>\n";
            ofs << "</tr>\n";
        }

        // Fechando as tags HTML
        ofs << "</table>\n</body>\n</html>\n";

        ofs.close();  // Fecha o arquivo após a escrita
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

    int p_input::get_qtd_caracteres() const {
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
