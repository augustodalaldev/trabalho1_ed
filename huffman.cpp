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
#include "bufferbits.h"

using std::vector;
using std::string;
using std::pair;

class Huffman{
    public:
        Huffman();
        static void compacta(const string& arquivo_entrada, const string& arquivo_saida);
        static void descompacta(const string& arquivo_entrada, const string& arquivo_saida);

    private:
        static vector<int> conta_freq(const string& arquivo_entrada);
        static MinHeapNode* constroi_heap(vector<int> dados);
        static ArvBinBusca* constroi_arvore(MinHeapNode* heap);

        static vector<vector<bool>> constroi_tabela(ArvBinBusca* arvore);
        static void constroi_tabela(Node* x, vector<vector<bool>>* v, vector<bool>* buffer);
        static pair<vector<uint8_t>, vector<bool>> percorre_letras(ArvBinBusca* arvore);
        static void percorre_letras(Node* x, pair<vector<uint8_t>, vector<bool>>* letras_bits);

        static void escreve_compacta(
            FILE* arquivo_entrada,
            FILE* arquivo_saida,
            uint16_t alfabeto_t,
            vector<uint8_t> letras,
            vector<bool> percurso,
            vector<vector<bool>> tabela
        );

        static void escreve_descompacta(
            FILE* arquivo_entrada,
            FILE* arquivo_saida,
            uint16_t alfabeto_t,
            vector<uint8_t> letras,
            vector<bool> percurso,
            vector<vector<bool>> tabela
        );
};

void Huffman::compacta(const string& arquivo_entrada, const string& arquivo_saida)
{
    vector<int> frequencia = Huffman::conta_freq(arquivo_entrada);
    MinHeapNode* heap = Huffman::constroi_heap(frequencia);
    uint16_t alfabeto_t = (uint16_t)heap->tamanho();
    ArvBinBusca* arvore = Huffman::constroi_arvore(heap);

    vector<vector<bool>> tabela = Huffman::constroi_tabela(arvore);
    pair<vector<uint8_t>, vector<bool>> par = Huffman::percorre_letras(arvore);

    FILE *fe = fopen(arquivo_entrada.c_str(), "rb");
    FILE *fs = fopen(arquivo_saida.c_str(), "wb");

    escreve_compacta(fe, fs, alfabeto_t, par.first, par.second, tabela);

    fclose(fe);
    fclose(fs);
}

void Huffman::descompacta(const string& arquivo_entrada, const string& arquivo_saida)
{

    FILE *fe = fopen(arquivo_entrada.c_str(), "rb");
    FILE *fs = fopen(arquivo_saida.c_str(), "wb");

    uint16_t alfabeto_t;
    //Lendo os dois primeiros bytes = K.
    fread(&alfabeto_t, 2, 1, fe);

    uint8_t sobra;
    //Lendo a sobra
    fread(&sobra, 1,1, fe);

    //Lendo as letras do alfabeto
    vector<uint8_t> letras(alfabeto_t);
    for(int i =0; i < alfabeto_t; i++)
        fread(&letras[i], 1,1, fe);

    /**for(int i =0; i < alfabeto_t; i++)
        printf("i = %d ASCII = %d\n", i, letras[i]);*/

    //Lendo o percurso das letras em pré-ordem
    vector<bool> percurso;
    BufferBitsLeitura buffer_leitura(fe);
    int cont = 0;
    while(cont < alfabeto_t){
        uint8_t simbolo = buffer_leitura.le_bit();
        percurso.push_back(simbolo);
        if(simbolo == 1)
            cont++;
    }

    //criando a árvore
    ArvBinBusca* arvore = new ArvBinBusca(percurso, letras);


    /**for(int i = 0; i < percurso.size(); i++)
        printf("%d", (int)percurso[i]);

    printf("\n");*/


    //printf("%d", sobra);



//    escreve_descompacta(fe, fs, alfabeto_t, par.first, par.second, tabela);

    fclose(fe);
    fclose(fs);
}

vector<int> Huffman::conta_freq(const string& arquivo_entrada){

    FILE *f = fopen(arquivo_entrada.c_str(), "rb");
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

void Huffman::escreve_compacta(FILE* arquivo_entrada, FILE* arquivo_saida, uint16_t alfabeto_t,
    vector<uint8_t> letras, vector<bool> percurso, vector<vector<bool>> tabela)
{
    BufferBitsEscrita buffer_escrita(arquivo_saida);

    //Escreve o K no arquivo de saída
    fwrite(&alfabeto_t, 2, 1, arquivo_saida);

    //Escreve oplaceholder de S no arquivo de saída
    uint8_t aux = 0;
    fwrite(&aux, 1, 1, arquivo_saida);

    //Escreve as n letras no arquivo de saída
    for (int i = 0; i < letras.size(); i++)
        fwrite(&letras[i], 1, 1, arquivo_saida);

    //Escreve o percurso pré-ordem no arquivo de saída
    for (int i = 0; i < percurso.size(); i++)
        buffer_escrita.escreve_bit(percurso[i]);

    //Escreve os bytes compactados no arquivo de saída
    char a;
    while(fread(&a, 1, 1, arquivo_entrada))
    {
        vector<bool> codigo = tabela[(int)a];
        for (int i = 0; i < codigo.size(); i++)
            buffer_escrita.escreve_bit(codigo[i]);
    }
    int s = 8 - buffer_escrita.n;
    buffer_escrita.descarrega();

    //Escreve o S no arquivo de saída
    fseek(arquivo_saida, 2, SEEK_SET);
    fwrite(&s, 1, 1, arquivo_saida);
}

void Huffman::escreve_descompacta(FILE* arquivo_entrada, FILE* arquivo_saida, uint16_t alfabeto_t,
    vector<uint8_t> letras, vector<bool> percurso, vector<vector<bool>> tabela)
{
    BufferBitsEscrita buffer_escrita(arquivo_saida);

    //Escreve o K no arquivo de saída
    fwrite(&alfabeto_t, 2, 1, arquivo_saida);

    //Escreve oplaceholder de S no arquivo de saída
    uint8_t aux = 0;
    fwrite(&aux, 1, 1, arquivo_saida);

    //Escreve as n letras no arquivo de saída
    for (int i = 0; i < letras.size(); i++)
        fwrite(&letras[i], 1, 1, arquivo_saida);

    //Escreve o percurso pré-ordem no arquivo de saída
    for (int i = 0; i < percurso.size(); i++)
        buffer_escrita.escreve_bit(percurso[i]);

    //Escreve os bytes compactados no arquivo de saída
    char a;
    while(fread(&a, 1, 1, arquivo_entrada))
    {
        vector<bool> codigo = tabela[(int)a];
        for (int i = 0; i < codigo.size(); i++)
            buffer_escrita.escreve_bit(codigo[i]);
    }
    int s = 8 - buffer_escrita.n;
    buffer_escrita.descarrega();

    //Escreve o S no arquivo de saída
    fseek(arquivo_saida, 2, SEEK_SET);
    fwrite(&s, 1, 1, arquivo_saida);
}



int main(void)
{
    Huffman::compacta("text.txt", "a.huff");
    Huffman::descompacta("a.huff", "bteste.txt");

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
    */

    return 0;
}
