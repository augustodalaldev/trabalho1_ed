/************************************************
 *
 * Grupo Itadakimais 2
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include "min_heap_node.h"
#include "huffman_tree.h"
#include "bufferbits.h"

using std::pair;
using std::string;
using std::vector;

class Huffman
{
public:
    static int compacta(const string &arquivo_entrada, const string &arquivo_saida);

    static int descompacta(const string &arquivo_entrada, const string &arquivo_saida);

private:
    static vector<int> conta_frequencia(FILE *arquivo_entrada);

    static vector<vector<bool>> constroi_tabela(HuffmanTree *arvore);

    static void constroi_tabela(
        Node *x, vector<vector<bool>> *tabela,
        vector<bool> *buffer);

    static pair<vector<uint8_t>, vector<bool>> percorre_letras(HuffmanTree *arvore);

    static void percorre_letras(
        Node *x, 
        pair<vector<uint8_t>,
        vector<bool>> *letras_bits);

    static void escreve_compacta(
        FILE *arquivo_entrada,
        FILE *arquivo_saida,
        uint16_t alfabeto_t,
        vector<uint8_t> letras,
        vector<bool> percurso,
        vector<vector<bool>> tabela);

    static void escreve_descompacta(
        FILE *arquivo_entrada,
        FILE *arquivo_saida,
        BufferBitsLeitura *buffer_leitura,
        HuffmanTree *arvore,
        int sobra);
};

#endif // HUFFMAN_H