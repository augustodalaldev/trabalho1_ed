#include "node.h"

Node::Node() :
  byte(0),
  freq(0),
  pai(NULL),
  esq(NULL),
  dir(NULL) {
}

Node::Node(const uint8_t byte, const int freq) :
    byte(byte),
    freq(freq),
    pai(NULL),
    esq(NULL),
    dir(NULL) {
}

Node::Node(const int freq) :
    byte(0),
    freq(freq),
    pai(NULL),
    esq(NULL),
    dir(NULL) {
}


void Node::escreve(const char *sep) {
  printf("%2d%s", freq, sep);
}