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

using std::vector;

class Huffman{
    public:
        Huffman();
};

int main(void)
{
    FILE *f = fopen("teste.txt", "rb");
    vector<int> v(256, 0);

    int a;
    while(fread(&a, 1, 1, f))
    {
      v[a]++;
    }
    fclose(f);

    return 0;
}
