#ifndef P_INPUT_HPP //Verifica se o identificador P_INPUT_HPP já foi definido. Se não, prossegue com a definição.
#define P_INPUT_HPP //Define o identificador P_INPUT_HPP para evitar múltiplas inclusões deste arquivo no mesmo programa (proteção contra redefinições).

#include <string> //manipulação de strings em C++.
#include <map> //uso de mapas (associação chave-valor), que será usada para armazenar as palavras e suas ocorrências.

namespace inp { //Define um namespace chamado 'inp' para organizar o código e evitar conflitos de nomes com outras partes do programa.

    //Declaração da classe 'p_input' que será responsável por processar a entrada, armazenar as ocorrências das palavras e exportar os dados.
    class p_input {
    private:  //Seção privada da classe, onde as variáveis e funções são acessíveis apenas por funções da própria classe.

        std::string modo_de_ordenacao; //Armazena o modo de ordenação escolhido (-ac, -ad, -nc, -nd).
        std::string nome_do_arquivo;   //Armazena o nome do arquivo de entrada fornecido pelo usuário.
        std::string formato_de_saida;  //Armazena o formato de saída escolhido (-csv ou -html).
        std::map<std::wstring, int> ocorrencias;  // Mapa que armazena as palavras encontradas no arquivo e o número de vezes que cada uma apareceu.

        int caracteres;         //Armazena o número total de caracteres no arquivo.
        int total_de_palavras;  //Armazena o número total de palavras no arquivo.
        int palavras_distintas; //Armazena o número de palavras distintas (sem repetições).

    public:  //Seção pública da classe, onde as funções podem ser acessadas por qualquer parte do programa.

        //Construtor da classe, responsável por inicializar as variáveis com valores padrão.
        p_input();

        //Função que processa os argumentos passados na linha de comando (modo de ordenação, formato de saída, nome do arquivo).
        void process_arg(int argc, char* argv[]);

        //Função que processa o arquivo de entrada, lendo as palavras e contando suas ocorrências.
        void process_input(const std::string& arquivo);

        //Função que ordena as palavras de acordo com o modo de ordenação escolhido e exibe o resultado.
        void ordenar_e_exibir(const std::map<std::wstring, int>& map_ref);

        //Função que exporta o resultado no formato CSV.
        void exportar_csv(const std::string& arquivo_saida) const;

        //Função que exporta o resultado no formato HTML.
        void exportar_html(const std::string& arquivo_saida) const;

        // Funções 'getter' para acessar os valores privados (modo de ordenação, nome do arquivo, formato de saída).
        std::string get_modo_de_ordenacao() const;
        std::string get_nome_do_arquivo() const;
        std::string get_formato_de_saida() const;

        // Funções 'getter' para acessar os contadores de caracteres, palavras e palavras distintas.
        int get_qtd_de_caracteres() const;
        int get_total_de_palavras() const;
        int get_palavras_distintas() const;

        // Função 'getter' para acessar o mapa de ocorrências das palavras.
        std::map<std::wstring, int> get_map() const;
    };

}  // Fim do namespace 'inp'.

#endif  //Fim da verificação se P_INPUT_HPP já foi definido.
