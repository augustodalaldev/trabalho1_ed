#ifndef NO_H
#define NO_H

#include <cstdint>
#include <cstdio>

class ArvBinBusca;
class Heap;

class No {
  friend class ArvBinBusca;
  friend class MinHeap;

public:
  No(const uint8_t byte, const int freq);
  No(const int freq);
  void escreve(const char *sep = "");

private:
    uint8_t byte;
    int freq;
    No *pai;
    No *esq;
    No *dir;
};


#endif // NO_H
