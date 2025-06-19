#include "arv_bin_busca.h"

//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE ARVBINBUSCA ***
//********************************************

ArvBinBusca::ArvBinBusca(vector<bool> percurso, vector<uint8_t> letras){

    raiz = new Node();
    int contador_percurso = 0;
    int contador_folha = 0;
    cria_arvore(&percurso, &letras, &contador_percurso, &contador_folha, raiz);
}


ArvBinBusca::ArvBinBusca(Node *x) {
  raiz = x;
}

ArvBinBusca::ArvBinBusca() {
  raiz = NULL;
}

ArvBinBusca::ArvBinBusca(const ArvBinBusca& outro) {
  copia(outro);
}

ArvBinBusca::~ArvBinBusca() {
  limpa();
}

//0010111
void ArvBinBusca::cria_arvore(vector<bool>* percurso, vector<uint8_t>* letras, int* contador_percurso, int* contador_folhas, Node* x){

    if((*percurso)[(*contador_percurso)]){
        //printf("letras[%d] = %c\n", *contador_folhas, (*letras)[(*contador_folhas)]);
        x->byte = (*letras)[(*contador_folhas)++];
        return;
    }

    Node* esq = new Node();
    Node* dir = new Node();
    x->esq = esq;
    x->dir = dir;
    (*contador_percurso)++;
    cria_arvore(percurso, letras, contador_percurso, contador_folhas, x->esq);
    (*contador_percurso)++;
    cria_arvore(percurso, letras, contador_percurso, contador_folhas, x->dir);

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

void ArvBinBusca::escreve_ordenado(Node *x) {
  //TODO: implementar (escrever em percurso em-ordem em uma única linha)
  if(x != NULL){
    escreve_ordenado(x->esq);
    printf("%d ", x->byte);
    //printf("freq = %d\n", x->freq);
    escreve_ordenado(x->dir);
    }
}

void ArvBinBusca::escreve() {
  escreve("", raiz);
}

void ArvBinBusca::escreve(const string& prefixo, Node *x) {
  if (x == NULL) {
    return;
  }

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

Node *ArvBinBusca::get_raiz() {
  return raiz;
}

Node *ArvBinBusca::busca(int k) {
  return busca(raiz, k);
}

Node *ArvBinBusca::busca(Node *x, int k) {
  //TODO: implementar
  if(x == NULL || x->freq == k)
    return x;

  if(k < x->freq)
    return busca(x->esq, k);

  return busca(x->dir, k);
}

Node *ArvBinBusca::minimo() {
  return raiz ? minimo(raiz) : NULL;
}

Node *ArvBinBusca::minimo(Node *x) {
  //TODO: implementar
  while(x->esq != NULL)
    x = x->esq;

  return x;
}

Node *ArvBinBusca::maximo() {
  return raiz ? maximo(raiz) : NULL;
}

Node *ArvBinBusca::maximo(Node *x) {
  //TODO: implementar
  while(x->dir != NULL)
    x = x->dir;

  return x;
}

Node *ArvBinBusca::sucessor(Node *x) {
  //TODO: implementar
  if(x->dir != NULL)
    return minimo(x->dir);

  Node *y = x->pai;
  while(y != NULL && x == y->dir){
    x = y;
    y = y->pai;
  }
  return y;
}

Node *ArvBinBusca::predecessor(Node *x) {
  //TODO: implementar
  if(x->esq != NULL)
    return maximo(x->esq);

  Node *aux = x->pai;
  while(aux != NULL && aux->esq == x)
    {
        x = aux;
        aux = aux->pai;
    }
  return aux;
}

void ArvBinBusca::insere(int freq) {
  Node *z = new Node(freq);
  insere(z);
}

void ArvBinBusca::insere(Node *z) {
  //TODO: implementar

  Node* y = NULL;
  Node* x = raiz;
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

void ArvBinBusca::transplante(Node *u, Node *v) {
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
  Node *z = busca(raiz, freq);
  if (z == NULL)
    return false;

  remove(z);
  delete z;
  return true;
}

void ArvBinBusca::remove(Node *z) {
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
        Node *y = minimo(z->dir);  // sucessor de z
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

void ArvBinBusca::limpa(Node *x) {
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
    raiz = new Node(T.raiz->freq);
    copia(raiz, T.raiz);
  }
}

void ArvBinBusca::copia(Node *dest, Node *orig) {
  //TODO: implementar
}

