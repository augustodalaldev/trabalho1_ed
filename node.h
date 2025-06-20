/************************************************
 *
 * Grupo Itadakimais 2
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
 */

#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <cstdio>

class HuffmanTree;
class Heap;

class Node
{
  friend class HuffmanTree;
  friend class MinHeapNode;
  friend class Huffman;

public:
  Node();
  Node(const uint8_t byte, const int freq);
  Node(const int freq);
  void escreve(const char *sep = "");

private:
  uint8_t byte;
  int freq;
  Node *pai;
  Node *esq;
  Node *dir;
};

#endif // NODE_H
