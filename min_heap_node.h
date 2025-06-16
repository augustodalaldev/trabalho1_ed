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
public:
  MinHeapNode();
  MinHeapNode(int n, int dados[]);
  ~MinHeapNode();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(const int freq);
  void altera_prioridade(int i, int p);
  Node consulta_minima();
  Node extrai_minima();

private:
  //TODO: ALTERAR ISSO DAQUI PARA NO, E MUDAR TUDO QUE DER PAU
  vector<Node> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);

  void insere(Node* n);
};

#endif //MIN_HEAP_NODE_H