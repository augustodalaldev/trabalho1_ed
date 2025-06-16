#include "no.h"

No::No(const uint8_t byte, const int freq) :
    byte(byte),
    freq(freq),
    pai(NULL),
    esq(NULL),
    dir(NULL) {
}

No::No(const int freq) :
    byte(0),
    freq(freq),
    pai(NULL),
    esq(NULL),
    dir(NULL) {
}


void No::escreve(const char *sep) {
  printf("%2d%s", freq, sep);
}