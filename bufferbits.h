/************************************************
 *
 * Grupo Itadakimais 2
 * Augusto Dalal, Luís Favoreto e Thiago Fernandes
 *
 * Trabalho de Estuturas de Dados
 * Professor (a): Diego Padilha Rubert
 *
 */

#ifndef BUFFER_BITS_H
#define BUFFER_BITS_H

#include <cstdio>
#include <cstdint>

class BufferBits
{
  friend class Huffman;

protected:
  FILE *arquivo;
  uint8_t byte;
  uint8_t n;

public:
  BufferBits(FILE *arquivo);
  uint8_t ocupados();
  uint8_t livres();
};

// Buffer de leitura de bits
class BufferBitsLeitura : public BufferBits
{
public:
  BufferBitsLeitura(FILE *arquivo);
  uint8_t le_bit();
};

// Buffer de escrita de bits
class BufferBitsEscrita : public BufferBits
{
public:
  BufferBitsEscrita(FILE *arquivo);
  void escreve_bit(uint8_t bit);
  void descarrega();
};

#endif