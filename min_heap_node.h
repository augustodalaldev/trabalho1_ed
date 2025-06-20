/************************************************
 *
 * Grupo Itadakimais 2
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
 */

#ifndef MIN_HEAP_NODE_H
#define MIN_HEAP_NODE_H

#include <cstdio>
#include <climits>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "node.h"

class MinHeapNode
{
  friend class Huffman;
  friend class HuffmanTree;

public:
  MinHeapNode();
  MinHeapNode(vector<int> dados);
  ~MinHeapNode();
  void escreve_niveis();
  void altera_prioridade(int i, int p);
  int tamanho();

  void insere(const int freq);

private:
  // TODO: ALTERAR ISSO DAQUI PARA NO, E MUDAR TUDO QUE DER PAU
  vector<Node *> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);

  Node *consulta_minima();
  Node *extrai_minima();
  void insere(Node *n);
};

#endif // MIN_HEAP_NODE_H
