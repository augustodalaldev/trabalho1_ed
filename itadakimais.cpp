/************************************************
 * 
 * Grupo Itadakimais
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 * 
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 * 
*/
//padrao
#include <stdio.h>

#include <string>
#include <climits>
#include <cstdio>
#include <vector>

using std::string;
using std::vector;

//CLASSE Nó

class No {
  friend class ArvBinBusca;

public:
  No(const int chave);

  void escreve(const char *sep = "");

private:
  int chave;
  No *pai;
  No *esq;
  No *dir;
};

//CLASSE ArvBinariaBusca

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

  void insere(int chave);
  bool remove(int chave);

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

//CLASSE Heap 
//TODO: (alterar para min_heap usando Nó)
class Heap
{
public:
  Heap();
  Heap(int n, int dados[]);
  ~Heap();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);
  int consulta_maxima();
  int extrai_maxima();
  void altera_prioridade(int i, int p);

  
private:
  vector<int> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};

//CLASSE BufferBits
// Buffer de 1 byte para leitura ou escrita bit-a-bit em arquivo (classe base).
class BufferBits {
    protected:
      FILE *arquivo;  // Ponteiro para o arquivo sendo lido/escrito
      uint8_t byte;   // Buffer com bits de um byte
      uint8_t n;      // Quantidade de posições ocupadas no byte
    
    public:
      BufferBits(FILE *arquivo);  // Construtor padrão com o arquivo que será lido ou escrito
      uint8_t ocupados();         // Devolve quantos bits estão ocupados no buffer
      uint8_t livres();           // Devolve quantos bits ainda podem ser adicionados ao buffer do byte
    };
    
// Buffer de leitura de bits
class BufferBitsLeitura : public BufferBits {
public:
    BufferBitsLeitura(FILE *arquivo); // Construtor padrão com o arquivo que será lido
    uint8_t le_bit();                 // Lê o próximo bit do buffer (lê um byte do arquivo se estiver vazio)
};

// Buffer de escrita de bits
class BufferBitsEscrita : public BufferBits {
public:
    BufferBitsEscrita(FILE *arquivo);  // Construtor padrão com o arquivo que será escrito
    void escreve_bit(uint8_t bit);     // Escreve um bit 0 ou 1 no buffer (escreve byte no arquivo se completar 8 bits)
    void descarrega();                 // Força a escrita do byte no buffer (completa com 0s, caso necessário)
};

//CLASSE Huffman
class Huffman{
    //declarar aqui métodos e atributos
}


//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE NO ***
//***********************************

No::No(const int chave) :
  chave(chave),
  pai(NULL),
  esq(NULL),
  dir(NULL) {
}

void No::escreve(const char *sep) {
  printf("%2d%s", chave, sep);
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
    printf("%d ", x->chave);
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
  if(x == NULL || x->chave == k)
    return x;

  if(k < x->chave)
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

void ArvBinBusca::insere(int chave) {
  No *z = new No(chave);
  insere(z);
}

void ArvBinBusca::insere(No *z) {
  //TODO: implementar

  No* y = NULL;
  No* x = raiz;
 // percorre até achar a posição para inserir o novo nó z. por que nosso mano z vai ser folha.
  while (x != NULL){
    y = x;
    if(z->chave < x->chave)
        x = x->esq;
    else
        x = x->dir;
  }

  z->pai = y; //y é o pai de z.

  if(y == NULL) //se isso ocorreu era pq a arvore era vazia
    raiz = z;
  else{
    if(z->chave < y->chave)
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

bool ArvBinBusca::remove(int chave) {
  No *z = busca(raiz, chave);
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
    raiz = new No(T.raiz->chave);
    copia(raiz, T.raiz);
  }
}

void ArvBinBusca::copia(No *dest, No *orig) {
  //TODO: implementar
}

//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE HEAP ***
//***********************************

Heap::Heap() {
}

Heap::Heap(int n, int dados[]) :
  S(dados, dados + n) {
  //TODO: implementar (constroi_max_heap)
  for (int i = n/2 - 1; i >= 0; i--)
    desce(i);
}

Heap::~Heap() {
}

void Heap::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(auto const& elemento: S) {
  // Equivalente a for (unsigned i = 0; i < S.size(); i++) { printf("%d ", S[i]);
    printf("%d ", elemento);
    if (++escritos == fim_nivel) {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

void Heap::escreve(const string& prefixo, int i) {
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

int Heap::pai(int i) {
  return (i - 1) / 2;
}

int Heap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int Heap::direito(int i) {
  return 2 * (i + 1);
}

void Heap::troca(int i, int j) {
  int aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void Heap::desce(int i) {
  //TODO: implementar
  int e, d, maior;
  e = esquerdo(i);
  d = direito(i);
  if (e < (int) S.size() && S[e] > S[i])
    maior = e;
  else
    maior = i;
  if (d < (int) S.size() && S[d] > S[maior])
    maior = d;
  if (maior != i) {
    troca(i, maior);
    desce(maior);
  }
}

void Heap::sobe(int i) {
  while (S[pai(i)] < S[i]) {
    troca(i, pai(i));
    i = pai(i);
  }
}

void Heap::insere(int p) {
  S.push_back(p);
  sobe(S.size()-1);
}

int Heap::consulta_maxima() {
  //TODO: implementar
  return S[0];
}

int Heap::extrai_maxima() {
  //TODO: implementar
  int maior;
  if (S.size() > 0) {
    maior = S[0]; // ou S.front()
    S[0] = S.back(); // ou S[S.size()-1]
    S.pop_back();
    desce(0);
    return maior;
  }
  else
    return INT_MIN;
}

void Heap::altera_prioridade(int i, int p) {
  //TODO: implementar
  int antiga = S[i];
  S[i] = p;
  if (p < antiga)
    desce(i);
  else
    sobe(i);
}

//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE BUFFERBITS ***
//***********************************

int DEBUG_BITS = 1;


int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "rb");
  //FILE *r = fopen(argv[2], "wb");
  BufferBitsLeitura bl(f);
  //BufferBitsEscrita bf(r);
  uint8_t bit;

  while((bit = bl.le_bit()) != 2){
    //bl.escreve_bit(bit);
    printf("Leu bit %u\n", bit);
  }

  // Criar buffer de leitura, ler e escrever cada byte

  fclose(f);
  return 0;
}


void escrever_binario(uint8_t numero)
{
  for (int i = 128; i > 0; i >>= 1)
    printf("%c", numero & i ? '1' : '0');
}

BufferBits::BufferBits(FILE *arquivo) :
  arquivo(arquivo),
  byte(0),
  n(0)
{ }

uint8_t BufferBits::ocupados()
{
  return n;
}

uint8_t BufferBits::livres()
{
  return 8 - n;
}

BufferBitsLeitura::BufferBitsLeitura(FILE *f) :
  BufferBits(f)
{ }

uint8_t BufferBitsLeitura::le_bit()
{
  // TODO:
  // Caso n == 0, deve ler 1 byte do arquivo e colocar no buffer
  // Se não houver mais bytes para serem lidos do arquivo, devolver o valor 2
  // Dica: leia sobre a função fread
    if(!n){
        if(fread(&byte, 1, 1, arquivo) == 0)
            return 2;

        n = 8;
    }

  if (DEBUG_BITS) printf("n: %d, byte: %d (", n, byte);
  if (DEBUG_BITS) escrever_binario(byte);

  // TODO: Colocar em bit o próximo bit, e decrementar n
  uint8_t bit;
    byte & (1 << (n - 1)) ? bit = 1 : bit = 0;
    n--;

  if (DEBUG_BITS) printf(") --> %d(", byte);
  if (DEBUG_BITS) escrever_binario(byte);
  if (DEBUG_BITS) printf("), bit: %d\n", bit);

  return bit;
}

BufferBitsEscrita::BufferBitsEscrita(FILE *f) :
  BufferBits(f)
{ }

void BufferBitsEscrita::escreve_bit(uint8_t bit)
{
  if (DEBUG_BITS) printf("bit: %d, n: %d, byte: %d (", bit, n, byte);
  if (DEBUG_BITS) escrever_binario(byte);



  // TODO: Adicionar o bit ao byte na posição correta
    bit &= 1; //pega o valor do bit mais a direita
    byte |= bit << 7 - n;
    n++;

  if (DEBUG_BITS) printf(") --> %d(", byte);
  if (DEBUG_BITS) escrever_binario(byte);
  if (DEBUG_BITS) printf(")\n");

  if (n == 8)
    descarrega();
}

void BufferBitsEscrita::descarrega()
{
  // TODO:
  // Escrever no arquivo o byte SE ao menos 1 bit tiver sido adicionao ao byte
  // Dica: não esqueça de atualizar os atributos da classe
  // Dica: leia sobre a função fwrite

    if(!n)
        return;
    n = 0;

    fwrite(&byte, 1, 1, arquivo);

    byte = 0;
}

//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE HUFFMAN ***
//***********************************

//implementar aqui


//***********************************
//*** MAIN ***
//***********************************

int main(void)
{
  
  return 0;
}