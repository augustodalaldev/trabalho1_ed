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


int main(void)
{

    vector<int> i = Huffman::contaFreq("text.txt");

    /**
    int j = 0;
    for(int x : i){
        printf("%d %d\n", x, j++);
    }
    */



    return 0;
}
