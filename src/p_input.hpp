#ifndef P_INPUT_HPP
#define P_INPUT_HPP

#include <string>
#include <map>

namespace inp {

    class p_input {
    private:
        std::string modo_de_ordenacao;
        std::string nome_do_arquivo;
        std::string formato_de_saida;
        std::map<std::wstring, int> ocorrencias;

        int caracteres;
        int total_de_palavras;
        int palavras_distintas;

    public:
        p_input();

        void process_arg(int argc, char* argv[]);
        void process_input(const std::string& arquivo);

        void ordenar_e_exibir(const std::map<std::wstring, int>& map_ref);

        void exportar_csv(const std::string& arquivo_saida) const;
        void exportar_html(const std::string& arquivo_saida) const;

        std::string get_modo_de_ordenacao() const;
        std::string get_nome_do_arquivo() const;
        std::string get_formato_de_saida() const;

        int get_qtd_de_caracteres() const;
        int get_total_de_palavras() const;
        int get_palavras_distintas() const;

        std::map<std::wstring, int> get_map() const;
    };

}

#endif
