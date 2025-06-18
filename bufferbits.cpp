#include <cstdio>
#include <cstdint>


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