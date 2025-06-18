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


  return 0;
}


MinHeapNode::MinHeapNode() {
}

MinHeapNode::MinHeapNode(vector<int> dados) :
  S() {
    for(int i = 0; i < dados.size(); i++){
        if(dados[i] != 0){
            printf("i = %d, dados[i] = %d\n", i, dados[i]);
            S.push_back(Node((uint8_t)i, dados[i]));
        }
    }
    for (int i = S.size()/2 - 1; i >= 0; i--)
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
