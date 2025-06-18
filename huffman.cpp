/************************************************
 *
 * Grupo Itadakimais
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
*/

#include <cstdio>
#include <vector>
#include <string>
#include "min_heap_node.h"
#include "arv_bin_busca.h"


using std::vector;
using std::string;

class Huffman{
    public:
        Huffman();
        static void compacta(const string& arquivoEntrada, FILE *arquivoSaida);
        static void descompacta(const string& arquivoEntrada, FILE *arquivoSaida);

        //vai virar private dps
        static vector<int> contaFreq(const string& arquivoEntrada);
        static MinHeapNode* constroiheap(vector<int> dados);
        static ArvBinBusca* constroiarvore(MinHeapNode* heap);
    private:



};

vector<int> Huffman::contaFreq(const string& arq){

    FILE *f = fopen(arq.c_str(), "rb");
    vector<int> v(256, 0);

    char a;
    while(fread(&a, 1, 1, f))
    {
        v[(int)a]++;
    }

    fclose(f);
    return v;
}

MinHeapNode* Huffman::constroiheap(vector<int> dados)
{
  return new MinHeapNode(dados);
}

ArvBinBusca* Huffman::constroiarvore(MinHeapNode* heap)
{
  while (heap->tamanho() > 1)
  {
    Node* x = new Node();
    x->esq = heap->extrai_minima();
    x->dir = heap->extrai_minima();
    x->freq = x->dir->freq + x->esq->freq;
    heap->insere(x);
  }
  
  return new ArvBinBusca(heap->extrai_minima());
}


int main(void)
{
    vector<int> i = Huffman::contaFreq("text.txt");
    MinHeapNode* heap = Huffman::constroiheap(i);
    ArvBinBusca* arvore = Huffman::constroiarvore(heap);
    arvore->escreve();

    /*
    int j = 0;
    for(int x : i){
        printf("%d %d\n", x, j++);
    }
    */
   
    return 0;
}
