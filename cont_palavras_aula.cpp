#include <iostream>
#include <fstream> // Para ler os arquivos e operações de entrada e saída.
#include <cctype> //Biblioteca C com funções de manipulação de caracteres.
#include <map>

using namespace std;

int main(){
    ifstream arq("gpl.txt"); //ifstream --> input file stream
    ofstream csv("palavras.csv");

    char ch; // Armaznena cada caractere lido do arquivo.
    string palavra;
    map<string, int> ocorrencias; //Armazena palavras e a quantidade de vezes que aparecem.

    while(arq.get(ch)){ //Lê caractere por caractere do arquivo "gpl.txt".
        if(isalpha(ch)){ //isalpha verifica se o caractere é uma letra.
            palavra += tolower(ch); //Concatenamos em string e o caracter em maiusculo.
        }
        else if(palavra.size() > 0){ //verifica se tem alguma palavra acumulada.
            cout << palavra << endl;
            ocorrencias[palavra]++; //Incrementa o contador dessa palavra no mapa.
            palavra.clear(); //Limpa a variável "palavra" para começar a próxima.
        }
    }
    csv << "\"Palavra\";\"N\"\n"; //Coloca o cabeçalho do arquivo CSV (as colunas "Palavra" e "N" para contagem).
    for(auto [k, v] : ocorrencias){ 
        csv << '"' << k << '"' << v << endl; //Escrevemos a palavra e sua contagem de ocorrências.
    }

}