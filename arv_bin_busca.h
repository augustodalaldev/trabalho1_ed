#include <cstdio>
#include <string>
using std::string;

//Nó
#include "node.h";

class ArvBinBusca
{
public:
  ArvBinBusca();
  ArvBinBusca(const ArvBinBusca& outro); // construtor de cópia
  ~ArvBinBusca();
  ArvBinBusca& operator=(const ArvBinBusca& outro); // operador de atribuição

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  Node *get_raiz(); // devolve a raiz
  Node *busca(int k); // devolve o ponteiro para um elemento, se achar, ou NULL
  Node *minimo(); // devolve o menor elemento da árvore
  Node *maximo(); // devolve o maior elemento da árvore
  Node *sucessor(Node *x); // devolve o sucessor de um elemento
  Node *predecessor(Node *x); // devolve o predecessor de um elemento

  void insere(int freq);
  bool remove(int freq);

  void limpa(); // remove todos elementos da árvore

private:
  Node *raiz;

  void escreve_ordenado(Node *x); // escreve em percurso em-ordem
  void escreve(const string& prefixo, Node *x);

  Node *busca(Node *x, int k);
  Node *minimo(Node *x);
  Node *maximo(Node *x);

  void insere(Node *z);
  void transplante(Node *u, Node *v);
  void remove(Node *z);

  void limpa(Node *x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

  void copia(const ArvBinBusca& T); // copia uma árvore T para a atual a partir da raiz,
                                    // usada no construtor de cópia e no operador de atribuição
  void copia(Node *dest, Node *orig);   // copia um nó e os descendentes recursivamente
};