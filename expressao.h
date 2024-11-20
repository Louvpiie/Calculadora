#ifndef EXPRESSAO_H
#define EXPRESSAO_H

// Estrutura para armazenar expressões
typedef struct {
    char posFixa[512]; // Expressão em notação pós-fixada
    char inFixa[512];  // Expressão em notação infixa
    float Valor;       // Valor calculado da expressão
} Expressao;

// Funções da pilha de números
void pushNum(float valor);   // Empilha um número
float popNum();              // Desempilha um número

// Funções da pilha de strings
void pushStr(const char *str);    // Empilha uma string
char *popStr();                  // Desempilha uma string

// Função para calcular o valor de uma expressão pós-fixada
float getValor(char *Str);

// Função para converter uma expressão pós-fixada para a forma infixa
char *getFormaInFixa(char *Str);

#endif
