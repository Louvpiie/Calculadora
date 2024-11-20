#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "expressao.h"

// Estrutura para a pilha de números
typedef struct {
    float numeros[512];
    int topoNum;
} Pilha;

static Pilha pilha = {{0}, -1};  // Pilha global para números

// Estrutura para a pilha de strings
typedef struct {
    char strings[512][512];
    int topoStr;
} PilhaStr;

static PilhaStr pilhaStr = {{0}, -1};  // Pilha global para strings

// Funções da pilha de números
void pushNum(float valor) {
    pilha.numeros[++(pilha.topoNum)] = valor;
}

float popNum() {
    return pilha.numeros[(pilha.topoNum)--];
}

// Funções da pilha de strings
void pushStr(const char *str) {
    strcpy(pilhaStr.strings[++(pilhaStr.topoStr)], str);
}

char *popStr() {
    return pilhaStr.strings[(pilhaStr.topoStr)--];
}

// Função para calcular as operações binárias
float calculaOperacao(float op1, float op2, char operador) {
    switch (operador) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return pow(op1, op2);
        default: return 0;
    }
}

// Função para calcular funções unárias como sen, cos, tan, etc.
float calculaFuncao(float operando, const char *funcao) {
    if (strcmp(funcao, "sin") == 0) return sin(operando * M_PI / 180);
    if (strcmp(funcao, "cos") == 0) return cos(operando * M_PI / 180);
    if (strcmp(funcao, "tan") == 0) return tan(operando * M_PI / 180);
    if (strcmp(funcao, "log") == 0) return log10(operando);
    if (strcmp(funcao, "raiz") == 0) return sqrt(operando);
    return 0;
}

// Função para calcular o valor de uma expressão pós-fixada
float getValor(char *Str) {
    char temp[512];
    strcpy(temp, Str);
    char *tok = strtok(temp, " ");

    while (tok != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pushNum(atof(tok)); // Empilha números
        } else if (strlen(tok) == 1) { // Operadores binários
            float op2 = popNum();
            float op1 = popNum();
            pushNum(calculaOperacao(op1, op2, tok[0])); // Executa operação binária
        } else { // Funções unárias
            float op = popNum();
            pushNum(calculaFuncao(op, tok)); // Executa função unária
        }
        tok = strtok(NULL, " ");
    }

    return popNum(); // Retorna o resultado final
}

// Função para converter uma expressão pós-fixada para a forma infixa
char *getFormaInFixa(char *Str) {
    static char resultado[512];
    char temp[512];
    strcpy(temp, Str);

    // Resetar pilha de expressões
    pilhaStr.topoStr = -1;

    char *tok = strtok(temp, " ");
    while (tok != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pushStr(tok); // Empilha números como strings
        } else if (strlen(tok) == 1) { // Operadores binários
            char op2[512], op1[512], expr[512];
            strcpy(op2, popStr());
            strcpy(op1, popStr());
            sprintf(expr, "(%s %s %s)", op1, tok, op2); // Formata a operação binária
            pushStr(expr); // Empilha a expressão infixa
        } else { // Funções unárias
            char op[512], expr[512];
            strcpy(op, popStr());
            sprintf(expr, "%s(%s)", tok, op); // Formata a função unária
            pushStr(expr); // Empilha a expressão infixa
        }
        tok = strtok(NULL, " ");
    }

    return popStr(); // Retorna a expressão infixa
}
