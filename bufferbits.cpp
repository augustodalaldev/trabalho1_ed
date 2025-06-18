#include "bufferbits.h"

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

  // TODO: Colocar em bit o próximo bit, e decrementar n
  uint8_t bit;
    byte & (1 << (n - 1)) ? bit = 1 : bit = 0;
    n--;

  return bit;
}

BufferBitsEscrita::BufferBitsEscrita(FILE *f) :
  BufferBits(f)
{ }

void BufferBitsEscrita::escreve_bit(uint8_t bit)
{
  // TODO: Adicionar o bit ao byte na posição correta
    bit &= 1; //pega o valor do bit mais a direita
    byte |= bit << 7 - n;
    n++;

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