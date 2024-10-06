#ifndef P_INPUT_HPP // Verifica se o cabeçalho já foi incluído
#define P_INPUT_HPP // Define o cabeçalho para evitar inclusões múltiplas

#include <string> // Inclui a biblioteca para usar strings
#include <map>    // Inclui a biblioteca para usar mapas (estrutura de dados que associa chaves a valores)

namespace inp { // Inicia um espaço de nomes para evitar conflitos de nomes.

    // Declaração da classe p_input, responsável por processar e manipular dados de entrada.
    class p_input {
    private:
        // Atributos privados da classe
        std::string modo_de_ordenacao; // Armazena o modo de ordenação selecionado pelo usuário (crescente, decrescente, etc.)
        std::string nome_do_arquivo;    // Armazena o nome do arquivo de entrada
        std::string formato_de_saida;    // Armazena o formato de saída escolhido (CSV ou HTML)
        std::map<std::wstring, int> ocorrencias; // Mapa que associa palavras (wide string) ao número de ocorrências

        // Atributos para contar informações estatísticas
        int caracteres;          // Total de caracteres lidos
        int total_de_palavras;   // Total de palavras processadas
        int palavras_distintas;  // Total de palavras distintas encontradas

    public:
        // Construtor da classe p_input
        p_input();

        // Método para processar os argumentos da linha de comando
        void process_arg(int argc, char* argv[]);
        
        // Método para processar o conteúdo do arquivo fornecido
        void process_input(const std::string& arquivo);

        // Método para ordenar e exibir as palavras e suas ocorrências
        void ordenar_e_exibir(const std::map<std::wstring, int>& map_ref);

        // Métodos para exportar os dados em diferentes formatos
        void exportar_csv(const std::string& arquivo_saida) const; // Exporta dados para CSV
        void exportar_html(const std::string& arquivo_saida) const; // Exporta dados para HTML

        // Métodos getters para acessar os atributos da classe
        std::string get_modo_de_ordenacao() const; // Retorna o modo de ordenação
        std::string get_nome_do_arquivo() const;    // Retorna o nome do arquivo
        std::string get_formato_de_saida() const;    // Retorna o formato de saída

        // Métodos para obter as contagens estatísticas
        int get_qtd_de_caracteres() const;          // Retorna a quantidade total de caracteres
        int get_total_de_palavras() const;           // Retorna o total de palavras processadas
        int get_palavras_distintas() const;          // Retorna a quantidade de palavras distintas

        // Método para obter o mapa de ocorrências de palavras
        std::map<std::wstring, int> get_map() const; // Retorna o mapa de ocorrências de palavras
    };

}

#endif // Fim da definição do cabeçalho
