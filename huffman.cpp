#include "huffman.h"

int Huffman::compacta(const string &arquivo_entrada, const string &arquivo_saida)
{
    FILE *fe = fopen(arquivo_entrada.c_str(), "rb");

    //caso não consiga abrir o arquivo de entrada
    if (!fe)
        return 0;

    //verificação caso o arquivo não possua nenhum byte
    uint8_t teste;
    if (!fread(&teste, 1, 1, fe))
        return 0;

    //voltando cursor para o começo do arquivo caso exista bytes no arquivo de entrada
    fseek(fe, 0, SEEK_SET);

    vector<int> frequencia = Huffman::conta_frequencia(fe);
    MinHeapNode *heap = new MinHeapNode(frequencia);
    uint16_t alfabeto_t = (uint16_t)heap->tamanho();
    HuffmanTree *arvore = new HuffmanTree(heap);

    vector<vector<bool>> tabela = Huffman::constroi_tabela(arvore);

    pair<vector<uint8_t>, vector<bool>> par = Huffman::percorre_letras(arvore);

    fe = freopen(arquivo_entrada.c_str(), "rb", fe);
    FILE *fs = fopen(arquivo_saida.c_str(), "wb");

    escreve_compacta(fe, fs, alfabeto_t, par.first, par.second, tabela);

    fclose(fe);
    fclose(fs);

    //Chamando destrutores
    delete heap;
    delete arvore;

    return 1;
}

int Huffman::descompacta(const string &arquivo_entrada, const string &arquivo_saida)
{

    FILE *fe = fopen(arquivo_entrada.c_str(), "rb");

    //caso não consiga abrir o arquivo de entrada
    if (!fe)
        return 0;

    uint16_t alfabeto_t;
    //Lendo os dois primeiros bytes = K.
    //Faz também a verificação caso o arquivo não possua nenhum byte
    if (!fread(&alfabeto_t, 2, 1, fe))
        return 0;

    uint8_t sobra;
    //Lendo a sobra
    fread(&sobra, 1, 1, fe);

    //Lendo as letras do alfabeto
    vector<uint8_t> letras(alfabeto_t);
    for (int i = 0; i < alfabeto_t; i++)
        fread(&letras[i], 1, 1, fe);

    //Lendo o percurso das letras em pré-ordem
    vector<bool> percurso;
    BufferBitsLeitura buffer_leitura(fe);
    int cont = 0;
    while (cont < alfabeto_t)
    {
        uint8_t simbolo = buffer_leitura.le_bit();
        percurso.push_back(simbolo);
        if (simbolo == 1)
            cont++;
    }

    //criando a árvore
    HuffmanTree *arvore = new HuffmanTree(percurso, letras);

    FILE *fs = fopen(arquivo_saida.c_str(), "wb");
    escreve_descompacta(fe, fs, &buffer_leitura, arvore, sobra);

    fclose(fe);
    fclose(fs);

    //Chamando destrutores
    delete arvore;

    return 1;
}

vector<int> Huffman::conta_frequencia(FILE *arquivo_entrada)
{

    vector<int> frequencia(256, 0);

    uint8_t a;
    while (fread(&a, 1, 1, arquivo_entrada))
        frequencia[(int)a]++;

    return frequencia;
}

vector<vector<bool>> Huffman::constroi_tabela(HuffmanTree *arvore)
{
    Node *raiz = arvore->raiz;
    vector<vector<bool>> tabela(256, vector<bool>(0));
    vector<bool> buffer(0);
    constroi_tabela(raiz, &tabela, &buffer);
    return tabela;
}

void Huffman::constroi_tabela(Node *x, vector<vector<bool>> *tabela, vector<bool> *buffer)
{
    if (x == NULL)
    {
        return;
    }
    if (x->dir == NULL && x->esq == NULL)
    {
        (*tabela)[x->byte] = *buffer;
        return;
    }
    buffer->push_back(0);
    constroi_tabela(x->esq, tabela, buffer);
    buffer->pop_back();
    buffer->push_back(1);
    constroi_tabela(x->dir, tabela, buffer);
    buffer->pop_back();
}

pair<vector<uint8_t>, vector<bool>> Huffman::percorre_letras(HuffmanTree *arvore)
{
    Node *raiz = arvore->raiz;
    vector<uint8_t> letras(0);
    vector<bool> bits(0);
    pair<vector<uint8_t>, vector<bool>> letras_bits(letras, bits);
    percorre_letras(raiz, &letras_bits);
    return letras_bits;
}

void Huffman::percorre_letras(Node *x, pair<vector<uint8_t>, vector<bool>> *letras_bits)
{
    if (x == NULL)
        return;

    if (x->dir == NULL && x->esq == NULL)
    {
        letras_bits->first.push_back(x->byte);
        letras_bits->second.push_back(1);
        return;
    }
    letras_bits->second.push_back(0);
    percorre_letras(x->esq, letras_bits);
    percorre_letras(x->dir, letras_bits);
}

void Huffman::escreve_compacta(FILE *arquivo_entrada, FILE *arquivo_saida, uint16_t alfabeto_t,
                               vector<uint8_t> letras, vector<bool> percurso, vector<vector<bool>> tabela)
{
    BufferBitsEscrita buffer_escrita(arquivo_saida);

    //Escreve o K no arquivo de saída
    fwrite(&alfabeto_t, 2, 1, arquivo_saida);

    //Escreve oplaceholder de S no arquivo de saída
    uint8_t aux = 0;
    fwrite(&aux, 1, 1, arquivo_saida);

    //Escreve as n letras no arquivo de saída
    for (int i = 0; i < (int)letras.size(); i++)
        fwrite(&letras[i], 1, 1, arquivo_saida);

    //Escreve o percurso pré-ordem no arquivo de saída
    for (int i = 0; i < (int)percurso.size(); i++)
        buffer_escrita.escreve_bit(percurso[i]);

    //Escreve os bytes compactados no arquivo de saída
    uint8_t a;
    while (fread(&a, 1, 1, arquivo_entrada))
    {
        vector<bool> codigo = tabela[(int)a];
        for (int i = 0; i < (int)codigo.size(); i++)
            buffer_escrita.escreve_bit(codigo[i]);
    }
    int s = 8 - buffer_escrita.n;
    buffer_escrita.descarrega();

    //Escreve o S no arquivo de saída
    fseek(arquivo_saida, 2, SEEK_SET);
    fwrite(&s, 1, 1, arquivo_saida);
}

/**
 * 
 * Para solucionar o problema da sobra (s), utilizamos uma abordagem de fila criada a partir do tamanho de s.
 * Lemos s bits dos códigos já compactados (no arquivo .huff) e colocamos eles na fila.
 * Então, vamos desenfilando os bits da fila, percorrendo a arvore com base nisso e escrevendo no arquivo de saida.
 * Além disso, enfileiramos novos bits do arquivo de entrada nesse processo.
 * Quando chegamos no fim do arquivo, significa que nossa fila está completa de 0's, e a descompactação foi completa
 * 
 */
void Huffman::escreve_descompacta(FILE *arquivo_entrada, FILE *arquivo_saida,
                                  BufferBitsLeitura *buffer_leitura, HuffmanTree *arvore, int sobra)
{

    //isso deveria ser uma queue (fila)
    //mas como usamos apenas nessa parte, adaptamos um vector para ser usado como tal
    vector<bool> bits_sobra(sobra, 0);

    for (int i = 0; i < sobra; i++)
        bits_sobra[i] = buffer_leitura->le_bit();

    uint8_t bit_arquivo;
    uint8_t bit_sobra;
    Node *aux;

    int primeira_vez;
    //verificação codigo de erro 2 no buffer bits leitura
    while ((bit_arquivo = buffer_leitura->le_bit()) != 2)
    {
        primeira_vez = 1;
        uint8_t simbolo;
        aux = arvore->raiz;

        while (!(aux->freq))
        {
            bit_sobra = bits_sobra.front();
            bits_sobra.erase(bits_sobra.begin());
            bits_sobra.push_back(primeira_vez ? bit_arquivo : buffer_leitura->le_bit());
            primeira_vez = 0;

            bit_sobra ? aux = aux->dir : aux = aux->esq;
        }

        simbolo = aux->byte;
        fwrite(&simbolo, 1, 1, arquivo_saida);
    }
}

//métodos para boniteza

void info_flag_inválida()
{
    printf("\nFlag Inválida - Opções Disponíveis: \n");
    printf("\td -> Descompactar arquivo\n");
    printf("\tc -> Compactar Arquivo\n");
    printf("Além disso, seguir as flags com nome do arquivo_entrada e arquivo_saida.\n\n");
}

void info_numero_argumentos_inválido()
{
    printf("\nNúmero de argumentos inválido: \n");
    printf("\tFlags Disponíveis:\n");
    printf("\t\td -> Descompactar arquivo\n");
    printf("\t\tc -> Compactar Arquivo\n");
    printf("Além disso, seguir as flags com nome do arquivo_entrada e arquivo_saida.\n\n");
}

void info_arquivo_inválido(const string &arquivo)
{
    printf("\nNão foi possível abrir o arquivo: %s\n", arquivo.c_str());
    printf("Verifique se ele existe ou se ele possui conteúdo.\n\n");
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        info_numero_argumentos_inválido();
        return 0;
    }

    string flag(argv[1]);
    string arquivo_entrada(argv[2]);
    string arquivo_saida(argv[3]);

    if (!flag.compare("c"))
    {
        printf("\nCompactando...\n");
        if (Huffman::compacta(arquivo_entrada, arquivo_saida))
        {
            printf("Arquivo compactado com sucesso!\n\n");
            return 0;
        }
        info_arquivo_inválido(arquivo_entrada);
        return 0;
    }
    else if (!flag.compare("d"))
    {
        printf("\nDescompactando...\n");
        if (Huffman::descompacta(arquivo_entrada, arquivo_saida))
        {
            printf("Arquivo descompactado com sucesso!\n\n");
            return 0;
        }
        info_arquivo_inválido(arquivo_entrada);
        return 0;
    }
    else
    {
        info_flag_inválida();
    }

    return 0;
}
