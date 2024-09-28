#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <codecvt>

void exportToCSV(const std::map<std::wstring, int>& occurrences) {
    std::wofstream csv("palavras.csv");
    csv << L"\"Palavra\";\"N\"\n"; // Cabeçalho do CSV
    for (const auto& [k, v] : occurrences) {
        csv << L'"' << k << L'"' << L";" << v << std::endl;
    }
}

void exportToHTML(const std::map<std::wstring, int>& occurrences) {
    std::wofstream html("palavras.html");
    html << L"<html><body>\n";
    html << L"<table border='1'><tr><th>Palavra</th><th>N</th></tr>\n";
    for (const auto& [k, v] : occurrences) {
        html << L"<tr><td>" << k << L"</td><td>" << v << L"</td></tr>\n";
    }
    html << L"</table></body></html>\n";
}

int main(int argc, char* argv[]) {
    // Configuração do locale - isso é importante para entradas de Unicode
    std::locale::global(std::locale("")); // Usa o locale do sistema para a entrada Unicode

    // Verifica se os argumentos estão corretos.
    if (argc < 2) {
        std::wcerr << L"Uso: " << argv[0] << L" <nome_do_arquivo> [-csv|-html] [-ac|-ad|-nc|-nd]" << std::endl;
        return 1;
    }

    // Converte o nome do arquivo de char* para std::wstring
    std::wstring nome_arquivo = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[1]);

    // Use std::wifstream e c_str() se você tiver certeza que seu sistema suporta
    std::wifstream arq(nome_arquivo.c_str()); // Tente aqui
    if (!arq.is_open()) {
        std::wcerr << L"Erro ao abrir o arquivo: " << nome_arquivo << std::endl;
        return 1;
    }

    // Ler palavras e contar ocorrências
    std::wstring palavra;
    std::map<std::wstring, int> ocorrencias;

    while (arq >> palavra) {
        palavra.erase(remove_if(palavra.begin(), palavra.end(), [](wchar_t c) {
            return !std::iswalpha(c); // Mantém apenas letras
        }), palavra.end());

        if (!palavra.empty()) {
            ocorrencias[palavra]++; // Incrementa a contagem
        }
    }

    // Obtenção da opção de saída e ordenação
    std::wstring outputFormat = L"-csv"; // Formato padrão
    std::wstring sortOption = L"-ac"; // Ordem padrão
    if (argc >= 3) outputFormat = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[2]);
    if (argc == 4) sortOption = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[3]);

    // Ordenação das palavras com base nas opções fornecidas
    std::vector<std::pair<std::wstring, int>> sortedOccurrences(ocorrencias.begin(), ocorrencias.end());
    
    // Ordenar com base nas opções
    if (sortOption == L"-ad") {
        std::sort(sortedOccurrences.rbegin(), sortedOccurrences.rend());
    } else {
        std::sort(sortedOccurrences.begin(), sortedOccurrences.end()); // Ordem padrão/ascendente
    }

    // Gera a saída com base no formato escolhido
    if (outputFormat == L"-html") {
        exportToHTML(ocorrencias);
    } else {
        exportToCSV(ocorrencias);
    }

    // Contagem de palavras e caracteres
    std::wcout << L"Total de palavras: " << ocorrencias.size() << std::endl;

    return 0; // Finaliza o programa com sucesso.
}
