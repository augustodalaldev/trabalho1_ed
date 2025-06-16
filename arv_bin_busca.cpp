#include "arv_bin_busca.h"

int main(void)
{
  ArvBinBusca T; // construtor ArvBinBusca()
  int v[] = {5, 4, 5, 5};

  for (const auto &x : v)
    T.insere(x);

  printf("T:\n");
  T.escreve();
  printf("Valores de T em ordem crescente: ");
  T.escreve_ordenado();

  //return 0; //TODO: remover após implementar minimo, maximo, sucessor, predecessor

  No *raiz = T.get_raiz();
  printf("Raiz: ");
  raiz->escreve("\n");

  No *pre = T.predecessor(raiz);
  printf("Predecessor da raiz: ");
  pre->escreve("\n");
  No *suc = T.sucessor(raiz);
  printf("Sucessor da raiz: ");
  suc->escreve("\n");

  printf("Sucessor do predecessor da raiz (== raiz): ");
  T.sucessor(pre)->escreve("\n");
  printf("Predecessor do sucessor da raiz (== raiz): ");
  T.predecessor(suc)->escreve("\n");

  No *minimo = T.minimo();
  No *maximo = T.maximo();
  printf("Mínimo: ");
  minimo->escreve("\n");
  printf("Máximo: ");
  maximo->escreve("\n");

  //return 0; //TODO: remover após implementar remoção


  T.remove(5);
  T.remove(5);
  T.remove(4);
  T.remove(5);

  printf("T:\n");
  T.escreve();
  T.escreve_ordenado();
  return 0; //TODO: remover após implementar construtor de cópia e operador de atribuição

  ArvBinBusca T2(T); // construtor de cópia
  T2.insere(30);
  printf("T:\n");
  T.escreve();
  printf("T2:\n");
  T2.escreve();

  ArvBinBusca T3 = T; // construtor de cópia
  T3.insere(-8);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();

  T3 = T; // operador de atribuição
  T3.insere(100);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();

  return 0;
}

//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE ARVBINBUSCA ***
//********************************************

ArvBinBusca::ArvBinBusca() {
  raiz = NULL;
}

ArvBinBusca::ArvBinBusca(const ArvBinBusca& outro) {
  copia(outro);
}

ArvBinBusca::~ArvBinBusca() {
  limpa();
}

ArvBinBusca& ArvBinBusca::operator=(const ArvBinBusca& outro) {
  limpa();
  copia(outro);
  return *this;
}

void ArvBinBusca::escreve_ordenado() {
  escreve_ordenado(raiz);
  putchar('\n');
}

void ArvBinBusca::escreve_ordenado(No *x) {
  //TODO: implementar (escrever em percurso em-ordem em uma única linha)
  if(x != NULL){
    escreve_ordenado(x->esq);
    printf("%d ", x->freq);
    escreve_ordenado(x->dir);
    }
}

void ArvBinBusca::escreve() {
  escreve("", raiz);
}

void ArvBinBusca::escreve(const string& prefixo, No *x) {
  if (x == NULL)
    return;

  bool ehDireito = x->pai and x->pai->dir == x;
  bool temIrmaoEsq = x->pai and x->pai->esq;

  printf(prefixo.c_str());
  printf(ehDireito and temIrmaoEsq ? "├──" : "└──" );

  if (x->pai == NULL) // raiz
    x->escreve("\n");
  else
    x->escreve(ehDireito ? "d\n" : "e\n");

  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->dir);
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->esq);
}

No *ArvBinBusca::get_raiz() {
  return raiz;
}

No *ArvBinBusca::busca(int k) {
  return busca(raiz, k);
}

No *ArvBinBusca::busca(No *x, int k) {
  //TODO: implementar
  if(x == NULL || x->freq == k)
    return x;

  if(k < x->freq)
    return busca(x->esq, k);

  return busca(x->dir, k);
}

No *ArvBinBusca::minimo() {
  return raiz ? minimo(raiz) : NULL;
}

No *ArvBinBusca::minimo(No *x) {
  //TODO: implementar
  while(x->esq != NULL)
    x = x->esq;

  return x;
}

No *ArvBinBusca::maximo() {
  return raiz ? maximo(raiz) : NULL;
}

No *ArvBinBusca::maximo(No *x) {
  //TODO: implementar
  while(x->dir != NULL)
    x = x->dir;

  return x;
}

No *ArvBinBusca::sucessor(No *x) {
  //TODO: implementar
  if(x->dir != NULL)
    return minimo(x->dir);

  No *y = x->pai;
  while(y != NULL && x == y->dir){
    x = y;
    y = y->pai;
  }
  return y;
}

No *ArvBinBusca::predecessor(No *x) {
  //TODO: implementar
  if(x->esq != NULL)
    return maximo(x->esq);

  No *aux = x->pai;
  while(aux != NULL && aux->esq == x)
    {
        x = aux;
        aux = aux->pai;
    }
  return aux;
}

void ArvBinBusca::insere(int freq) {
  No *z = new No(freq);
  insere(z);
}

void ArvBinBusca::insere(No *z) {
  //TODO: implementar

  No* y = NULL;
  No* x = raiz;
 // percorre até achar a posição para inserir o novo nó z. por que nosso mano z vai ser folha.
  while (x != NULL){
    y = x;
    if(z->freq < x->freq)
        x = x->esq;
    else
        x = x->dir;
  }

  z->pai = y; //y é o pai de z.

  if(y == NULL) //se isso ocorreu era pq a arvore era vazia
    raiz = z;
  else{
    if(z->freq < y->freq)
        y->esq = z;
    else
        y->dir = z;
  }

}

void ArvBinBusca::transplante(No *u, No *v) {
  //TODO: implementar
  if(u->pai == NULL)
    this->raiz = v;
  else{
    if(u == u->pai->esq)
      u->pai->esq = v;
    else
      u->pai->dir = v;
  }

  if(v != NULL)
    v->pai = u->pai;

}

bool ArvBinBusca::remove(int freq) {
  No *z = busca(raiz, freq);
  if (z == NULL)
    return false;

  remove(z);
  delete z;
  return true;
}

void ArvBinBusca::remove(No *z) {
  //TODO: implementar

  // caso 1: sem filho esquerdo
  if (z->esq == NULL) {
    transplante(z, z->dir);
  }

  else
    {
    if(z->dir == NULL) // caso 2: sem filho direito
        transplante(z, z->esq);

    else //caso 3
    {
        No *y = minimo(z->dir);  // sucessor de z
        if(y->pai != z) //caso 3b + 3a;
        {
            transplante(y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplante(z,y);
        y->esq = z->esq;
        y->esq->pai = y;

    }
  }

}

void ArvBinBusca::limpa() {
  limpa(raiz);
  raiz = NULL;
}

void ArvBinBusca::limpa(No *x) {
  //TODO: implementar
  if(x != NULL){
    limpa(x->esq);
    limpa(x->dir);
    delete x;
  }
}

void ArvBinBusca::copia(const ArvBinBusca& T) {
  if (T.raiz == NULL)
    raiz = NULL;
  else {
    raiz = new No(T.raiz->freq);
    copia(raiz, T.raiz);
  }
}

void ArvBinBusca::copia(No *dest, No *orig) {
  //TODO: implementar
}

