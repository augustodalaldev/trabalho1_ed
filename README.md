# 📄 Trabalho 1 Estruturas de Dados
## 📁 Implementação Compactador Huffman

### Cabeçalho:

     Grupo Itadakimais 2
     Augusto Dalal, Luís Favoreto e Thiago Fernandes
    
     Trabalho de Estuturas de Dados
     Professor (a): Diego Padilha Rubert
    
### Compilação:
Primeiro clone esse repositório com: 
```shell
git clone https://github.com/augustodalaldev/trabalho1_ed
```

Então, para compilar, basta utilizar o seguinte comando:    
```shell
g++ -Wall -pedantic -std=c++11 -g huffman.cpp huffman_tree.cpp min_heap_node.cpp node.cpp bufferbits.cpp -o cod_compilado
```
O comando utiliza o g++ para compilação, e as mesmas flags definidas na descrição do trabalho.

- OBS: Caso esteja no windows, basta trocar cod_compilado para cod_compilado.exe

### Execução:

Para executar, basta utilizar o comando:
```shell
./cod_compilado [flag] [arquivo_entrada] [arquivo_saida]
```

Em que:
- **[flag]** -> `d` ou `c` (`descompactar` ou `compactar`) 
- **[arquivo_entrada]** -> arquivo que você quer compactar ou descompactar
- **[arquivo_saida]** -> arquivo de saida padrão

