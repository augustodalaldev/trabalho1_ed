#include "min_heap_node.h"

MinHeapNode::MinHeapNode()
{
}

MinHeapNode::MinHeapNode(vector<int> dados) : S()
{
  for (int i = 0; i < (int)dados.size(); i++)
  {
    if (dados[i] != 0)
    {
      // printf("i = %d, dados[i] = %d\n", i, dados[i]);
      S.push_back(new Node((uint8_t)i, dados[i]));
    }
  }
  for (int i = S.size() / 2 - 1; i >= 0; i--)
    desce(i);
}

MinHeapNode::~MinHeapNode()
{
}

void MinHeapNode::escreve_niveis()
{
  int escritos = 0, fim_nivel = 1;

  for (auto const &elemento : S)
  {
    printf("(%df, %dby) ", elemento->freq, elemento->byte);
    if (++escritos == fim_nivel)
    {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

int MinHeapNode::tamanho()
{
  return S.size();
}

int MinHeapNode::pai(int i)
{
  return (i - 1) / 2;
}

int MinHeapNode::esquerdo(int i)
{
  return 2 * (i + 1) - 1;
}

int MinHeapNode::direito(int i)
{
  return 2 * (i + 1);
}

void MinHeapNode::troca(int i, int j)
{
  Node *aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void MinHeapNode::desce(int i)
{
  int e, d, menor;
  e = esquerdo(i);
  d = direito(i);
  if (e < (int)S.size() && S[e]->freq < S[i]->freq)
    menor = e;
  else
    menor = i;
  if (d < (int)S.size() && S[d]->freq < S[menor]->freq)
    menor = d;
  if (menor != i)
  {
    troca(i, menor);
    desce(menor);
  }
}

void MinHeapNode::sobe(int i)
{
  while (S[pai(i)]->freq > S[i]->freq)
  {
    troca(i, pai(i));
    i = pai(i);
  }
}

void MinHeapNode::insere(const int p)
{
  S.push_back(new Node(p));
  sobe(S.size() - 1);
}

void MinHeapNode::insere(Node *n)
{
  S.push_back(n);
  sobe(S.size() - 1);
}

Node *MinHeapNode::consulta_minima()
{
  return S[0];
}

Node *MinHeapNode::extrai_minima()
{
  Node *menor = S[0];
  if (S.size() > 0)
  {
    S[0] = S.back(); // ou S[S.size()-1]
    S.pop_back();
    desce(0);
    return menor;
  }
  else
    return NULL;
}

void MinHeapNode::altera_prioridade(int i, int p)
{
  int antiga = S[i]->freq;
  S[i]->freq = p;
  if (p > antiga)
    desce(i);
  else
    sobe(i);
}
