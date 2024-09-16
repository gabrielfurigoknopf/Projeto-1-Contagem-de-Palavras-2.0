# Projeto #1: Contagem de Palavras 2.0
Esse é o repositório do primeiro projeto do Laboratório de Programação III.

# Integrantes:
Nomes: Cícero Pizetta Pizutti, Gabriel Furigo Knopf e Thiago Reis Petereit Dos Santos.
# Professor: 
Nome: Marcos Jose Brusso.

# Objetivo: 
Concluir os objetivos listados com êxito.

* Desenvolver uma nova versão do arquivo palavras.cpp que foi criado em aula.
* Expandir a funcionalidade para suportar não apenas arquivos ASCII, mas também arquivos Unicode. Para isso, explore o uso de std::wifstream, std::wstring e wchar_t.
* Modificar o programa para aceitar o nome do arquivo a ser lido através de argumentos na linha de comando (usando argc e argv).

### Métodos de ordenação das palavras e seus critérios:

* `-ac`: Ordem alfabética ascendente da palavra (default).
* `-ad`: Ordem alfabética descendente da palavra.
* `-nc`: Ordem ascendente do número de ocorrrências.
* `-nd`: Ordem descendente do número de ocorrrências.

### Formatos de saída:

* As saídas serão geradas nos formatos .csv ou .html, e a escolha do formato deve ser especificada através da linha de comando:
* Use -csv para gerar a saída em um arquivo .csv (este será o formato padrão se nenhuma opção for fornecida);
* Use -html para gerar a saída em um arquivo .html, exibindo os resultados em uma tabela (TABLE);
* Ao concluir a execução, o programa deve exibir na saída padrão a contagem de caracteres e palavras extraídas do arquivo, além da quantidade de palavras distintas encontradas.

### Lista de tarefas:

* Adicionar ao algoritmo palavras.cpp, desenvolvido em aula, a funcionalidade para receber o nome do arquivo a ser lido como parâmetro, permitindo a contagem de palavras.
* Modularizar e organizar o código existente para melhorar sua estrutura e manutenção.
* Explorar diferentes maneiras de organizar o map para possibilitar a aceitação de novos parâmetros no algoritmo.
* Implementar a função para exportar a saída do algoritmo em um arquivo .html.
* Pesquisar sobre arquivos Unicode para entender melhor como manipulá-los.
* Adaptar o palavras.cpp para gerar um arquivo .html em vez de .csv para fins de validação de conceito.












