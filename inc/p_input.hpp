#ifndef P_INPUT_HPP
#define P_INPUT_HPP

#include <string>
#include <map> 
#include <iostream>
#include <vector>

namespace inp {

class p_input { 
private:
    std::string modo_de_ordenacao;  
    std::string nome_do_arquivo;     
    std::string formato_de_saida;    

    std::map<std::string, int> ocorrencias;  
    int caracteres = 0;                      
    int total_de_palavras = 0;                
    int palavras_distintas = 0;              

public:
    p_input() = default;

    void process_arg(int argc, char* argv[]);
    void process_input(const std::string& arquivo);

    const std::string& get_modo_de_ordenacao() const {
        return modo_de_ordenacao;
    }

    const std::string& get_nome_do_arquivo() const {
        return nome_do_arquivo;
    }

    const std::string& get_formato_de_saida() const {
        return formato_de_saida;
    }

    int get_qtd_caracteres() const {
        return caracteres;
    }

    int get_total_de_palavras() const {
        return total_de_palavras;
    }

    int get_palavras_distintas() const {
        return palavras_distintas;
    }

    const std::map<std::string, int>& get_ocorrencias() const {  
        return ocorrencias;
    }
};

}

#endif
