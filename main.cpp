// main.cpp
#include "contagem_palavras.hpp"
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

int processFile(const std::wstring& filename, const std::wstring& outputFormat, const std::wstring& sortOption) {
    std::locale::global(std::locale("")); // Configuração do locale
    std::wifstream arq(filename.c_str());

    if (!arq.is_open()) {
        std::wcerr << L"Erro ao abrir o arquivo: " << filename << std::endl;
        return 1;
    }

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

    // Ordenação das palavras e geração da saída
    std::vector<std::pair<std::wstring, int>> sortedOccurrences(ocorrencias.begin(), ocorrencias.end());

    if (sortOption == L"-ad") {
        std::sort(sortedOccurrences.rbegin(), sortedOccurrences.rend());
    } else {
        std::sort(sortedOccurrences.begin(), sortedOccurrences.end()); // Ordem padrão/ascendente
    }

    // Gera a saída de acordo com o formato escolhido
    if (outputFormat == L"-html") {
        exportToHTML(ocorrencias);
    } else {
        exportToCSV(ocorrencias);
    }

    std::wcout << L"Total de palavras: " << ocorrencias.size() << std::endl;
    return 0; // Finaliza o programa com sucesso.
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::wcerr << L"Uso: " << argv[0] << L" <nome_do_arquivo> [-csv|-html] [-ac|-ad]" << std::endl;
        return 1;
    }

    // Converte o nome do arquivo de char* para std::wstring
    std::wstring nome_arquivo = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[1]);
    std::wstring outputFormat = (argc >= 3) ? std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[2]) : L"-csv";
    std::wstring sortOption = (argc == 4) ? std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(argv[3]) : L"-ac";

    return processFile(nome_arquivo, outputFormat, sortOption);
}
