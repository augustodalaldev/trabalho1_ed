#include <cstdio>
#include <string>
using std::string;

//Nó
#include "no.h";

class ArvBinBusca
{
public:
  ArvBinBusca();
  ArvBinBusca(const ArvBinBusca& outro); // construtor de cópia
  ~ArvBinBusca();
  ArvBinBusca& operator=(const ArvBinBusca& outro); // operador de atribuição

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  No *get_raiz(); // devolve a raiz
  No *busca(int k); // devolve o ponteiro para um elemento, se achar, ou NULL
  No *minimo(); // devolve o menor elemento da árvore
  No *maximo(); // devolve o maior elemento da árvore
  No *sucessor(No *x); // devolve o sucessor de um elemento
  No *predecessor(No *x); // devolve o predecessor de um elemento

  void insere(int freq);
  bool remove(int freq);

  void limpa(); // remove todos elementos da árvore

private:
  No *raiz;

  void escreve_ordenado(No *x); // escreve em percurso em-ordem
  void escreve(const string& prefixo, No *x);

  No *busca(No *x, int k);
  No *minimo(No *x);
  No *maximo(No *x);

  void insere(No *z);
  void transplante(No *u, No *v);
  void remove(No *z);

  void limpa(No *x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

  void copia(const ArvBinBusca& T); // copia uma árvore T para a atual a partir da raiz,
                                    // usada no construtor de cópia e no operador de atribuição
  void copia(No *dest, No *orig);   // copia um nó e os descendentes recursivamente
};