#ifndef NO_H
#define NO_H

#include <cstdint>
#include <cstdio>

class ArvBinBusca;
class Heap;

class Node {
  friend class ArvBinBusca;
  friend class MinHeapNode;

public:
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


#endif // NO_H
