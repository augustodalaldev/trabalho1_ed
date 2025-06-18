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
#include <utility>
#include "min_heap_node.h"
#include "arv_bin_busca.h"

using std::vector;
using std::string;
using std::pair;

class Huffman{
    public:
        Huffman();
        static void compacta(const string& arquivoEntrada, FILE *arquivoSaida);
        static void descompacta(const string& arquivoEntrada, FILE *arquivoSaida);

        //vai virar private dps
        static vector<int> conta_freq(const string& arquivoEntrada);
        static MinHeapNode* constroi_heap(vector<int> dados);
        //TODO: K = size heap
        static ArvBinBusca* constroi_arvore(MinHeapNode* heap);
        static vector<vector<bool>> constroi_tabela(ArvBinBusca* arvore);
        static void constroi_tabela(Node* x, vector<vector<bool>>* v, vector<bool>* buffer);
        static pair<vector<uint8_t>, vector<bool>> percorre_letras(ArvBinBusca* arvore);
        static void percorre_letras(Node* x, pair<vector<uint8_t>, vector<bool>>* letras_bits);
    private:



};

vector<int> Huffman::conta_freq(const string& arq){

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

MinHeapNode* Huffman::constroi_heap(vector<int> dados)
{
    return new MinHeapNode(dados);
}

ArvBinBusca* Huffman::constroi_arvore(MinHeapNode* heap)
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

vector<vector<bool>> Huffman::constroi_tabela(ArvBinBusca* arvore)
{
    Node* raiz = arvore->raiz;
    vector<vector<bool>> v(256, vector<bool>(0));
    vector<bool> buffer(0);
    constroi_tabela(raiz, &v, &buffer);
    return v;
}

void Huffman::constroi_tabela(Node* x, vector<vector<bool>>* v, vector<bool>* buffer)
{
    if(x == NULL)
    {
        return;
    }
    if(x->dir == NULL && x->esq == NULL)
    {
        (*v)[x->byte] = *buffer;
        return;
    }
    buffer->push_back(0);
    constroi_tabela(x->esq, v, buffer);
    buffer->pop_back();
    buffer->push_back(1);
    constroi_tabela(x->dir, v, buffer);
    buffer->pop_back();
}

pair<vector<uint8_t>, vector<bool>> Huffman::percorre_letras(ArvBinBusca* arvore)
{
    Node* raiz = arvore->raiz;
    vector<uint8_t> letras(0);
    vector<bool> bits(0);
    pair<vector<uint8_t>, vector<bool>> letras_bits(letras, bits);
    percorre_letras(raiz, &letras_bits);
    return letras_bits;
}

void Huffman::percorre_letras(Node* x, pair<vector<uint8_t>, vector<bool>>* letras_bits)
{
    if(x == NULL)
    {
        return;
    }
    if(x->dir == NULL && x->esq == NULL)
    {
        letras_bits->first.push_back(x->byte);
        letras_bits->second.push_back(1);
        return;
    }
    letras_bits->second.push_back(0);
    percorre_letras(x->esq, letras_bits);
    percorre_letras(x->dir, letras_bits);
}

int main(void)
{
    vector<int> i = Huffman::conta_freq("text.txt");
    MinHeapNode* heap = Huffman::constroi_heap(i);
    ArvBinBusca* arvore = Huffman::constroi_arvore(heap);
    vector<vector<bool>> v = Huffman::constroi_tabela(arvore);
    pair<vector<uint8_t>, vector<bool>> par = Huffman::percorre_letras(arvore);

    for (int i = 0; i < par.first.size(); i++)
    {
        printf("%d: %d\n", i, par.first[i]);
    }
    printf("percurso: ");
    for (int i = 0; i < par.second.size(); i++)
    {
        printf("%d", (int)par.second[i]);
    }
    printf("\n");
    
    /*
    for (int i = 0; i < 256; i++)
    {
        if (v[i].size() != 0)
        {
            vector<bool> aux(v[i]);
            printf("%d: ", i);
            for (int j = 0; j < v[i].size(); j++)
            {
                printf("%d", (int)aux[j]);
                
            }
            printf("\n");
        }
    }
    */

    return 0;
}
