/************************************************
 *
 * Grupo Itadakimais 2
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
 */

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <cstdio>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Nó
#include "node.h"
#include "min_heap_node.h"

class HuffmanTree
{
  friend class Huffman;

public:
  HuffmanTree();
  HuffmanTree(const HuffmanTree &outro); // construtor de cópia
  ~HuffmanTree();
  HuffmanTree &operator=(const HuffmanTree &outro); // operador de atribuição

  HuffmanTree(
      vector<bool> percurso,
      vector<uint8_t> letras);

  HuffmanTree(MinHeapNode *heap);

  void escreve_pre_ordem(); // escreve em percurso em-ordem

  void insere(int freq);

  void limpa(); // remove todos elementos da árvore

private:
  Node *raiz;

  HuffmanTree(Node *x);

  void escreve_pre_ordem(Node *x); // escreve em percurso em-ordem
  void insere(Node *z);

  void cria_arvore(
      vector<bool> *percurso, vector<uint8_t> *letras,
      int *contador_percurso, int *contador_folhas, Node *x);

  void limpa(Node *x); // dado um nó x, remove recursivamente elementos abaixo e deleta x
};

#endif // HUFFMAN_TREE_H
