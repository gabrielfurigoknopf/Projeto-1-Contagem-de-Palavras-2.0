#ifndef P_INPUT_HPP
#define P_INPUT_HPP

#include <string>
#include <map>

namespace inp {

    class p_input {
    private:
        // Definindo os atributos de configuração e estatísticas
        std::string modo_de_ordenacao;     // Modo de ordenação dos dados
        std::string nome_do_arquivo;       // Nome do arquivo a ser processado
        std::string formato_de_saida;      // Formato da saída dos dados (ex: CSV, JSON, etc.)

        // Mapa para armazenar as ocorrências das palavras
        std::map<std::wstring, int> ocorrencias;  // Chave do tipo wstring para suportar caracteres Unicode

        int caracteres;                    // Contagem total de caracteres no arquivo
        int total_de_palavras;             // Contagem total de palavras no arquivo
        int palavras_distintas;            // Contagem de palavras distintas no arquivo

    public:
        // Construtor da classe inicializando variáveis
        p_input() : caracteres(0), total_de_palavras(0), palavras_distintas(0) {
            // Iniciando atributos com valores padrão, como modo de ordenação, nome de arquivo e formato de saída
        }

        // Processa os argumentos passados via linha de comando
        void process_arg(int argc, char* argv[]) {
            // Aqui seria implementado o tratamento dos argumentos da linha de comando
            // por exemplo, definindo valores como o nome do arquivo e o modo de ordenação
        }

        // Processa o arquivo de entrada, lendo e contando palavras, caracteres, etc.
        void process_input(const std::string& arquivo) {
            // Esse método abriria o arquivo especificado e processaria as palavras,
            // atualizando o mapa de ocorrências e outras estatísticas
        }

        // Métodos getters para acessar as variáveis privadas
        std::string get_modo_de_ordenacao() const {
            return modo_de_ordenacao;  // Retorna o modo de ordenação (alfabética, numérica, etc.)
        }

        std::string get_nome_do_arquivo() const {
            return nome_do_arquivo;  // Retorna o nome do arquivo que está sendo processado
        }

        std::string get_formato_de_saida() const {
            return formato_de_saida;  // Retorna o formato de saída especificado
        }

        int get_qtd_de_caracteres() const {
            return caracteres;  // Retorna o total de caracteres no arquivo
        }

        int get_total_de_palavras() const {
            return total_de_palavras;  // Retorna o número total de palavras processadas
        }

        int get_palavras_distintas() const {
            return palavras_distintas;  // Retorna a contagem de palavras distintas
        }

        // Retorna o mapa de ocorrências de palavras
        std::map<std::wstring, int> get_ocorrencias() const {
            return ocorrencias;
        }
    };

}

#endif
