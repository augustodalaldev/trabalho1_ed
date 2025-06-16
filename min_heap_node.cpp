#include "min_heap_node.h"

//Apagar dps
int main(void)
{
  MinHeapNode h; // construtor MinHeapNode()
  
  for (int i = 10; i > 5; i--)
    h.insere(i);
  printf("h:\n");
  h.escreve();

  h.extrai_minima();
  h.altera_prioridade(0, 20);
  printf("h:\n");
  h.escreve();

  int v[] = {1,2,3,4,5};
  
  MinHeapNode h2(5, v); // construtor MinHeapNode(int n, int dados[])
  h2.insere(15);
  printf("h2:\n");
  h2.escreve();

  MinHeapNode h3(h2); // construtor de cópia padrão
  h2.insere(30);
  printf("h3:\n");
  h3.escreve();

  MinHeapNode h4 = h2; // construtor de cópia padrão
  h2.insere(40);
  printf("h4:\n");
  h4.escreve();
  
  h = h2; // operador de atribuição, sem constructor ou constructor de cópia
  h.insere(100);
  printf("h2:\n");
  h2.escreve();
  printf("h:\n");
  h.escreve();

  h = MinHeapNode(5, v); // construtor MinHeapNode(int n, int dados[]), seguido de atribuição (de cópia, não transferência (move))
  printf("h:\n");
  h.escreve();
  
  h.extrai_minima();
  h.altera_prioridade(0, -2);
  printf("h:\n");
  h.escreve();

  return 0;
}


MinHeapNode::MinHeapNode() {
}

MinHeapNode::MinHeapNode(int n, int dados[]) :
  S(dados, dados + n) {
  for (int i = n/2 - 1; i >= 0; i--)
    desce(i);
}

MinHeapNode::~MinHeapNode() {
}

void MinHeapNode::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(auto const& elemento: S) {
    printf("(%df, %dby) ", elemento.freq, elemento.byte);
    if (++escritos == fim_nivel) {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

void MinHeapNode::escreve(const string& prefixo, int i) {
  if (i < (int) S.size()) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < (int) S.size()-1;
    
    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    printf("(%df,%dby)\n", S[i].freq, S[i].byte);
      
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int MinHeapNode::pai(int i) {
  return (i - 1) / 2;
}

int MinHeapNode::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int MinHeapNode::direito(int i) {
  return 2 * (i + 1);
}

void MinHeapNode::troca(int i, int j) {
  Node aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void MinHeapNode::desce(int i) {
  int e, d, menor;
  e = esquerdo(i);
  d = direito(i);
  if (e < (int) S.size() && S[e].freq < S[i].freq)
    menor = e;
  else
    menor = i;
  if (d < (int) S.size() && S[d].freq < S[menor].freq)
    menor = d;
  if (menor != i) {
    troca(i, menor);
    desce(menor);
  }
}

void MinHeapNode::sobe(int i) {
  while (S[pai(i)].freq > S[i].freq) {
    troca(i, pai(i));
    i = pai(i);
  }
}

void MinHeapNode::insere(const int p) {
  Node newNode = Node(p);
  S.push_back(newNode);
  sobe(S.size() - 1);
}

void MinHeapNode::insere(Node* n) {
  S.push_back(*n);
  sobe(S.size() - 1);
}

Node MinHeapNode::consulta_minima() {
  return S[0];
}

Node MinHeapNode::extrai_minima() {
  Node menor = S[0];
  if (S.size() > 0) {
    S[0] = S.back(); // ou S[S.size()-1]
    S.pop_back();
    desce(0);
    return menor;
  }
  else
    return INT_MIN;
}

void MinHeapNode::altera_prioridade(int i, int p) {
  int antiga = S[i].freq;
  S[i].freq = p;
  if (p > antiga)
    desce(i);
  else
    sobe(i);
}
