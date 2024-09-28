// contagem_palavras.hpp
#ifndef CONTAGEM_PALAVRAS_HPP
#define CONTAGEM_PALAVRAS_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

void exportToCSV(const std::map<std::wstring, int>& occurrences);
void exportToHTML(const std::map<std::wstring, int>& occurrences);
int processFile(const std::wstring& filename, const std::wstring& outputFormat, const std::wstring& sortOption);

#endif // CONTAGEM_PALAVRAS_HPP
