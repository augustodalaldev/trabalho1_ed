#include <cstdio>
#include <climits>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "no.h"

class MinHeap
{
public:
  MinHeap();
  MinHeap(int n, int dados[]);
  ~MinHeap();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);
  int consulta_minima();
  int extrai_minima();
  void altera_prioridade(int i, int p);

  
private:
  //TODO: ALTERAR ISSO DAQUI PARA NO, E MUDAR TUDO QUE DER PAU
  vector<int> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


int main(void)
{
  MinHeap h; // construtor MinHeap()
  
  for (int i = 10; i > 5; i--)
    h.insere(i);
  printf("h:\n");
  h.escreve();

  h.extrai_minima();
  h.altera_prioridade(0, 20);
  printf("h:\n");
  h.escreve();

  int v[] = {1,2,3,4,5};
  
  MinHeap h2(5, v); // construtor MinHeap(int n, int dados[])
  h2.insere(15);
  printf("h2:\n");
  h2.escreve();

  MinHeap h3(h2); // construtor de cópia padrão
  h2.insere(30);
  printf("h3:\n");
  h3.escreve();

  MinHeap h4 = h2; // construtor de cópia padrão
  h2.insere(40);
  printf("h4:\n");
  h4.escreve();
  
  h = h2; // operador de atribuição, sem constructor ou constructor de cópia
  h.insere(100);
  printf("h2:\n");
  h2.escreve();
  printf("h:\n");
  h.escreve();

  h = MinHeap(5, v); // construtor MinHeap(int n, int dados[]), seguido de atribuição (de cópia, não transferência (move))
  printf("h:\n");
  h.escreve();
  
  h.extrai_minima();
  h.altera_prioridade(0, -2);
  printf("h:\n");
  h.escreve();

  return 0;
}


MinHeap::MinHeap() {
}

MinHeap::MinHeap(int n, int dados[]) :
  S(dados, dados + n) {
  for (int i = n/2 - 1; i >= 0; i--)
    desce(i);
}

MinHeap::~MinHeap() {
}

void MinHeap::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(auto const& elemento: S) {
    printf("%d ", elemento);
    if (++escritos == fim_nivel) {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

void MinHeap::escreve(const string& prefixo, int i) {
  if (i < (int) S.size()) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < (int) S.size()-1;
    
    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    printf("%d\n", S[i]);
      
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int MinHeap::pai(int i) {
  return (i - 1) / 2;
}

int MinHeap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int MinHeap::direito(int i) {
  return 2 * (i + 1);
}

void MinHeap::troca(int i, int j) {
  int aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void MinHeap::desce(int i) {
  int e, d, menor;
  e = esquerdo(i);
  d = direito(i);
  if (e < (int) S.size() && S[e] < S[i])
    menor = e;
  else
    menor = i;
  if (d < (int) S.size() && S[d] < S[menor])
    menor = d;
  if (menor != i) {
    troca(i, menor);
    desce(menor);
  }
}

void MinHeap::sobe(int i) {
  while (S[pai(i)] > S[i]) {
    troca(i, pai(i));
    i = pai(i);
  }
}

void MinHeap::insere(int p) {
  S.push_back(p);
  sobe(S.size() - 1);
}

int MinHeap::consulta_minima() {
  return S[0];
}

int MinHeap::extrai_minima() {
  int menor;
  if (S.size() > 0) {
    menor = S[0]; // ou S.front()
    S[0] = S.back(); // ou S[S.size()-1]
    S.pop_back();
    desce(0);
    return menor;
  }
  else
    return INT_MIN;
}

void MinHeap::altera_prioridade(int i, int p) {
  int antiga = S[i];
  S[i] = p;
  if (p > antiga)
    desce(i);
  else
    sobe(i);
}
