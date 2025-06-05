// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Vanessa da conceição dos santos
//  email: 20241160038@ifba.edu.br
//  Matrícula: 20241160038
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "VanessaSantos20241160038.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]) {
    DataQuebrada dq;
    char sDia[3], sMes[3], sAno[5];
    int i, j;

    for (i = 0; data[i] != '/'; i++) {
        sDia[i] = data[i];
    }
    sDia[i] = '\0'; 
    if (i != 1 && i != 2) {
        dq.valido = 0;
        return dq;
    }

    j = i + 1;
    for (i = 0; data[j] != '/'; j++, i++) {
        sMes[i] = data[j];
    }
    sMes[i] = '\0';
    if (i != 1 && i != 2) {
        dq.valido = 0;
        return dq; 
    }

    j = j + 1;
    for (i = 0; data[j] != '\0'; j++, i++) {
        sAno[i] = data[j];
    }
    sAno[i] = '\0'; 
    if (i != 2 && i != 4) {
        dq.valido = 0;
        return dq; 
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);
    dq.valido = 1;

    return dq;
}

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    DataQuebrada dq = quebraData(data);

    if (dq.valido == 0)
        return 0;

    int dia = dq.iDia;
    int mes = dq.iMes;
    int ano = dq.iAno;

    if (ano < 100)
    {
        if (ano >= 0 && ano <= 49)
            ano += 2000;
        else
            ano += 1900;
    }

    if (mes < 1 || mes > 12)
        return 0;

    if (dia < 1)
        return 0;

    int diasMes;

    switch (mes)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        diasMes = 31;
        break;
    case 4: case 6: case 9: case 11:
        diasMes = 30;
        break;
    case 2:
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
            diasMes = 29;
        else
            diasMes = 28;
        break;
    default:
        return 0;
    }

    if (dia > diasMes)
        return 0;

    return 1;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;

    if (q1(datainicial) == 0)
    {
        dma.retorno = 2;
        return dma;
    }

    if (q1(datafinal) == 0)
    {
        dma.retorno = 3;
        return dma;
    }

    DataQuebrada ini = quebraData(datainicial);
    DataQuebrada fim = quebraData(datafinal);

    if (ini.iAno < 100)
        ini.iAno += (ini.iAno <= 49) ? 2000 : 1900;

    if (fim.iAno < 100)
        fim.iAno += (fim.iAno <= 49) ? 2000 : 1900;

    if (fim.iAno < ini.iAno ||
        (fim.iAno == ini.iAno && fim.iMes < ini.iMes) ||
        (fim.iAno == ini.iAno && fim.iMes == ini.iMes && fim.iDia < ini.iDia))
    {
        dma.retorno = 4;
        return dma;
    }

    int dia1 = ini.iDia;
    int mes1 = ini.iMes;
    int ano1 = ini.iAno;
    int dia2 = fim.iDia;
    int mes2 = fim.iMes;
    int ano2 = fim.iAno;

    dma.qtdAnos = ano2 - ano1;
    dma.qtdMeses = mes2 - mes1;
    dma.qtdDias = dia2 - dia1;

    if (dma.qtdDias < 0)
    {
        dma.qtdMeses--;
        int diasNoMesAnterior;
        int m = mes2 - 1;
        int a = ano2;

        if (m == 0)
        {
            m = 12;
            a--;
        }

        switch (m)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasNoMesAnterior = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasNoMesAnterior = 30;
            break;
        case 2:
            diasNoMesAnterior = ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28;
            break;
        default:
            diasNoMesAnterior = 30;
        }

        dma.qtdDias += diasNoMesAnterior;
    }

    if (dma.qtdMeses < 0)
    {
        dma.qtdAnos--;
        dma.qtdMeses += 12;
    }

    dma.retorno = 1;
    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
	
    if (isCaseSensitive != 1) {
        if (c >= 'A' && c <= 'Z') {
            c = c + 32; 
        }
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        char atual = texto[i];

        if (isCaseSensitive != 1) {
            if (atual >= 'A' && atual <= 'Z') {
                atual = atual + 32;
            }
        }

        if (atual == c) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}


/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
 void noSpecials(char *text){
  int i, j=0;

  const char *comAcentos[] = {"Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
                                "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
                                "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
                                "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
                                "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
                                "Ç", "ç"};
                                
  const char *semAcentos[] = {"A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
                              "E", "E", "E", "E", "e", "e", "e", "e",
                              "I", "I", "I", "I", "i", "i", "i", "i",
                              "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
                              "U", "U", "U", "u", "u", "u", "u",
                              "C", "c"};

  char buffer[256];
  buffer[0] = '\0';

  for (int i = 0; i < strlen(text);) {
    int found = 0;
    for (int j = 0; j < sizeof(comAcentos) / sizeof(comAcentos[0]); j++) {
      int len = strlen(comAcentos[j]);

      if (strncmp(&text[i], comAcentos[j], len) == 0) {
        strcat(buffer, semAcentos[j]);
        i += len;
        found = 1;
        break;
      }
    }
    if (!found) {
      strncat(buffer, &text[i], 1);
      i++;
    }
  }
  strcpy(text, buffer);
}

int q4(char *strTexto, char *strBusca, int posicoes[30]){
    int qtdOcorrencias = 0;
    int posicao = 0;
    int len = strlen(strBusca);
    noSpecials(strTexto);
    noSpecials(strBusca);

    for(int i = 0; i<strlen(strTexto);){
      int achou = 0;
      if(strTexto[i]==strBusca[0]){
        achou=1;
        for(int j=i, k=0; k<len; j++,k++){
          if(strBusca[k]!=strTexto[j])achou=0;
        }
        if(achou){
          qtdOcorrencias++;
          posicoes[posicao] = i+1;
          posicao++;
          posicoes[posicao] = i+len;
          posicao++;

          i += len;
        }else{
          i++;
        }
      }
      if(!achou)i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
    int invertido = 0;

    while (num > 0) {
        invertido = invertido * 10 + (num % 10);
        num /= 10;
    }

    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
    int qtdOcorrencias = 0;
    char baseStr[50], buscaStr[50];

    sprintf(baseStr, "%d", numerobase);
    sprintf(buscaStr, "%d", numerobusca);

    int tamBusca = strlen(buscaStr);
    int tamBase = strlen(baseStr);

    for (int i = 0; i <= tamBase - tamBusca; i++) {
        int encontrou = 1;
        for (int j = 0; j < tamBusca; j++) {
            if (baseStr[i + j] != buscaStr[j]) {
                encontrou = 0;
                break;
            }
        }
        if (encontrou)
            qtdOcorrencias++;
    }

    return qtdOcorrencias;
}
/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5]) {
    int linhas = 8, colunas = 10;
    int tamPalavra = strlen(palavra);
    
    int direcoes[8][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            for (int d = 0; d < 8; d++) {
                int dirX = direcoes[d][0], dirY = direcoes[d][1];
                int k, x = i, y = j;
                int encontrado = 1;
                
                for (k = 0; k < tamPalavra; k++) {
                    if (x < 0 || x >= linhas || y < 0 || y >= colunas || matriz[x][y] != palavra[k]) {
                        encontrado = 0;
                        break;
                    }
                    x += dirX;
                    y += dirY;
                }
                
                if (encontrado) {
                    return 1;  
                }
            }
        }
    }
    
    return 0;
}
