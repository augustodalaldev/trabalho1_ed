#include "huffman_tree.h"

// Construtor que cria a árvore de Huffman a partir da heap
// Usada na compactação
HuffmanTree::HuffmanTree(MinHeapNode *heap)
{
  while (heap->tamanho() > 1)
  {
    Node *x = new Node();
    x->esq = heap->extrai_minima();
    x->dir = heap->extrai_minima();
    x->freq = x->dir->freq + x->esq->freq;
    heap->insere(x);
  }

  raiz = heap->extrai_minima();
}

// Construtor que cria a árvore de Huffman a partir do percurso e das letras do alfabeto
// Usada na descompactação
HuffmanTree::HuffmanTree(vector<bool> percurso, vector<uint8_t> letras)
{
  raiz = new Node();
  int contador_percurso = 0;
  int contador_folha = 0;
  cria_arvore(&percurso, &letras, &contador_percurso, &contador_folha, raiz);
}

// Cria arvore de huffman a partir do percurso e das letras de maneira recursiva
void HuffmanTree::cria_arvore(vector<bool> *percurso, vector<uint8_t> *letras,
                              int *contador_percurso, int *contador_folhas, Node *x)
{

  if ((*percurso)[(*contador_percurso)])
  {
    x->byte = (*letras)[(*contador_folhas)++];
    x->freq = 1;
    return;
  }

  Node *esq = new Node();
  Node *dir = new Node();
  x->esq = esq;
  x->dir = dir;
  (*contador_percurso)++;
  cria_arvore(percurso, letras, contador_percurso, contador_folhas, x->esq);
  (*contador_percurso)++;
  cria_arvore(percurso, letras, contador_percurso, contador_folhas, x->dir);
}

HuffmanTree::HuffmanTree(Node *x)
{
  raiz = x;
}

HuffmanTree::HuffmanTree()
{
  raiz = NULL;
}

HuffmanTree::~HuffmanTree()
{
  limpa();
}

void HuffmanTree::escreve_pre_ordem()
{
  escreve_pre_ordem(raiz);
  putchar('\n');
}

void HuffmanTree::escreve_pre_ordem(Node *x)
{
  if (x != NULL)
  {
    printf("%dbyte %dfrequencia\n", x->byte, x->freq);
    escreve_pre_ordem(x->esq);
    escreve_pre_ordem(x->dir);
  }
}

void HuffmanTree::insere(int freq)
{
  Node *z = new Node(freq);
  insere(z);
}

void HuffmanTree::insere(Node *z)
{

  Node *y = NULL;
  Node *x = raiz;

  while (x != NULL)
  {
    y = x;
    if (z->freq < x->freq)
      x = x->esq;
    else
      x = x->dir;
  }

  z->pai = y;

  if (y == NULL)
    raiz = z;
  else
  {
    if (z->freq < y->freq)
      y->esq = z;
    else
      y->dir = z;
  }
}

void HuffmanTree::limpa()
{
  limpa(raiz);
  raiz = NULL;
}

void HuffmanTree::limpa(Node *x)
{
  if (x != NULL)
  {
    limpa(x->esq);
    limpa(x->dir);
    delete x;
  }
}
