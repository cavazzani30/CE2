#include "mainwindow.h"

int MainWindow::divisaoComplexa(complexo numerador, complexo denominador, complexo *resultado)
{
   // testa divisão por zero
   if (denominador.real == 0)
   {
      if (denominador.img == 0)
         return ERRO_DIVISAO_COMPLEXO;
   }
    // realiza a divisão
    else
    {
       resultado->real = ((numerador.real*denominador.real)+(numerador.img*denominador.img))/((denominador.real)*(denominador.real)+(denominador.img)*(denominador.img));
       resultado->img = ((numerador.img*denominador.real)-(numerador.real*denominador.img))/((denominador.real)*(denominador.real)+(denominador.img)*(denominador.img));
    }
    return OK;
}

// PRODUTO COMPLEXO --- Função que opera multiplicação entre números complexos

complexo MainWindow::ProdutoComplexo(complexo fator1, complexo fator2)
{
   // variável de saída
   complexo resultado;

   // realiza a divisão
   resultado.real = ((fator1.real*fator2.real)-(fator1.img*fator2.img));
   resultado.img = ((fator1.real*fator2.img)+(fator1.img*fator2.real));
   return resultado;
}

int MainWindow::gaussJordan(complexo SistemaAux[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2], int numero_variaveis)
{
   complexo fatorEscalonamento,
            linhaTroca[NUMERO_MAXIMO_NOS+2],
            produto;

   for (int indice_pivot = 1; indice_pivot <= numero_variaveis; indice_pivot++)
   {
      if ((SistemaAux[indice_pivot][indice_pivot].img == 0) && (SistemaAux[indice_pivot][indice_pivot].real == 0))
      {
         for (int linhas = indice_pivot; linhas <= numero_variaveis; linhas++)
         {
            if ((SistemaAux[linhas][indice_pivot].real != 0) || (SistemaAux[linhas][indice_pivot].img != 0))
            {
               for (int colunas = 1; colunas <= numero_variaveis+1; colunas++)
               {
                  linhaTroca[colunas].real = SistemaAux[indice_pivot][colunas].real;
                  linhaTroca[colunas].img = SistemaAux[indice_pivot][colunas].img;
               }
               for (int colunas = 1; colunas <= numero_variaveis+1; colunas++)
               {
                  SistemaAux[indice_pivot][colunas].real = SistemaAux[linhas][colunas].real;
                  SistemaAux[indice_pivot][colunas].img = SistemaAux[linhas][colunas].img;
               }
               for (int colunas = 1; colunas <= numero_variaveis+1; colunas++)
               {
                  SistemaAux[linhas][colunas].real = linhaTroca[colunas].real;
                  SistemaAux[linhas][colunas].img = linhaTroca[colunas].img;
               }
               linhas = numero_variaveis;
            }
         }
      }
      fatorEscalonamento = SistemaAux[indice_pivot][indice_pivot];
      for (int colunas = 1; colunas <= numero_variaveis+1; colunas++)
         if(divisaoComplexa(SistemaAux[indice_pivot][colunas], fatorEscalonamento, &SistemaAux[indice_pivot][colunas]))
            return ERRO_DIVISAO_COMPLEXO;
      for (int linhas = indice_pivot+1; linhas <= numero_variaveis; linhas++)
      {
         if ((SistemaAux[linhas][indice_pivot].real != 0) || (SistemaAux[linhas][indice_pivot].img != 0))
         {
            fatorEscalonamento = SistemaAux[linhas][indice_pivot];
            for (int colunas = indice_pivot; colunas <= numero_variaveis+1; colunas++)
            {
               produto = ProdutoComplexo(fatorEscalonamento, SistemaAux[indice_pivot][colunas]);
               SistemaAux[linhas][colunas].real = SistemaAux[linhas][colunas].real - produto.real;
               SistemaAux[linhas][colunas].img = SistemaAux[linhas][colunas].img - produto.img;
            }
         }
      }
    }
    for (int indice_pivot = numero_variaveis-1; indice_pivot >= 1; indice_pivot--)
    {
       for (int colunas = numero_variaveis; colunas > indice_pivot; colunas--)
       {
          produto = ProdutoComplexo(SistemaAux[indice_pivot][colunas], SistemaAux[colunas][numero_variaveis+1]);
          SistemaAux[indice_pivot][colunas].real = 0;
          SistemaAux[indice_pivot][colunas].img = 0;
          SistemaAux[indice_pivot][numero_variaveis+1].real -= produto.real;
          SistemaAux[indice_pivot][numero_variaveis+1].img -= produto.img;
       }
    }
    return OK;
}
