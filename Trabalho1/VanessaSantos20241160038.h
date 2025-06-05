// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo contém exemplos de testes das questões do trabalho.
//  o aluno pode incrementar os testes

//  ----- Dados do Aluno -----
//  Nome: Vanessa da conceição dos santos
//  email: 20241160038@ifba.edu.br
//  Matrícula: 20241160038
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 19/08/2016 - 12/12/2018

// #################################################
#ifndef TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H
#define TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H

typedef struct DQ
{
    int iDia; 
    int iMes;
    int iAno;
    int valido; // 0 se inválido, e 1 se válido 

} DataQuebrada;

typedef struct Qtd
{
    int qtdDias;
    int qtdMeses;
    int qtdAnos;
    int retorno;

} DiasMesesAnos;

int somar(int x, int y); //função utilizada para testes
int fatorial(int x); //função utilizada para testes
int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);
int q7(char matriz[8][10], char palavra[5]);
DataQuebrada quebraData(char data[]);

#endif 
