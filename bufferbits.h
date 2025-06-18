#ifndef BUFFER_BITS_H
#define BUFFER_BITS_H

#include <cstdio>
#include <cstdint>


// Buffer de 1 byte para leitura ou escrita bit-a-bit em arquivo (classe base).
class BufferBits {
friend class Huffman;

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

#endif