#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::montarEstampas (elemento NetlistAux[NUMERO_MAXIMO_ELEMENTOS], complexo SistemaAux[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2], float frequenciaAux, int numeroElementosAux, int numeroVariaveisAux)
{
   int x1, x2;
   float L1, L2, frequenciaAngular;
   QString stringAux;

   frequenciaAngular = 2*PI*frequenciaAux;

   for (int i = 1; i <= numeroElementosAux; i++)
   {
      if (NetlistAux[i].nome[0] == 'R') //estampa do resistor
      {
          if (NetlistAux[i].valor == 0)
             return ERRO_DIVISAO_POR_ZERO;

          SistemaAux[NetlistAux[i].a][NetlistAux[i].a].real += (1/NetlistAux[i].valor);
          SistemaAux[NetlistAux[i].b][NetlistAux[i].b].real += (1/NetlistAux[i].valor);
          SistemaAux[NetlistAux[i].a][NetlistAux[i].b].real -= (1/NetlistAux[i].valor);
          SistemaAux[NetlistAux[i].b][NetlistAux[i].a].real -= (1/NetlistAux[i].valor);

      }

      else if (NetlistAux[i].nome[0] == 'C')  // estampa do capacitor
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].a].img += (frequenciaAngular*NetlistAux[i].valor);
         SistemaAux[NetlistAux[i].b][NetlistAux[i].b].img += (frequenciaAngular*NetlistAux[i].valor);
         SistemaAux[NetlistAux[i].a][NetlistAux[i].b].img -= (frequenciaAngular*NetlistAux[i].valor);
         SistemaAux[NetlistAux[i].b][NetlistAux[i].a].img -= (frequenciaAngular*NetlistAux[i].valor);
      }

      else if (NetlistAux[i].nome[0] == 'L') // estampa do indutor
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].a].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].b].real += 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].x].img += (frequenciaAngular*NetlistAux[i].valor);
      }

      else if (NetlistAux[i].nome[0] == 'K')
      {
         for (int j = 1; j < numeroElementosAux; j++)
         {
            if (NetlistAux[j].nome == NetlistAux[i].la)
            {
               L1 = NetlistAux[j].valor;
               x1 = NetlistAux[j].x;
            }
            else if (NetlistAux[j].nome == NetlistAux[i].lb)
            {
               L2 = NetlistAux[j].valor;
               x2 = NetlistAux[j].x;
            }
         }
         SistemaAux[x1][x2].img += (frequenciaAngular*NetlistAux[i].valor*(sqrt(L1*L2)));
         SistemaAux[x2][x1].img += (frequenciaAngular*NetlistAux[i].valor*(sqrt(L1*L2)));
      }

      else if (NetlistAux[i].nome[0] == 'G')  // estampa de fonte de corrente controlada a tensao
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].c].real += NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].a][NetlistAux[i].d].real -= NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].c].real -= NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].d].real += NetlistAux[i].valor;
      }

      else if (NetlistAux[i].nome[0] == 'E') // estampa de fonte de tensao controlada a tensao
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].a].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].b].real += 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].c].real += NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].d].real -= NetlistAux[i].valor;
      }

      else if (NetlistAux[i].nome[0] == 'F') // estampa de fonte de corrente controlada a corrente
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].x].real += NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].x].real -= NetlistAux[i].valor;
         SistemaAux[NetlistAux[i].c][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].d][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].c].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].d].real += 1;
      }

      else if (NetlistAux[i].nome[0] == 'H') // estampa de fonte de tensao controlada a corrente
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].y].real += 1;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].y].real -= 1;
         SistemaAux[NetlistAux[i].c][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].d][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].c].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].d].real += 1;
         SistemaAux[NetlistAux[i].y][NetlistAux[i].a].real -= 1;
         SistemaAux[NetlistAux[i].y][NetlistAux[i].b].real += 1;
         SistemaAux[NetlistAux[i].y][NetlistAux[i].x].real += NetlistAux[i].valor;
      }

      else if (NetlistAux[i].nome[0] == 'O') // estampa do amplificador operacional ideal
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].c].real += 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].d].real -= 1;
      }

      else if (NetlistAux[i].nome[0] == 'V')
      {
         SistemaAux[NetlistAux[i].a][NetlistAux[i].x].real += 1;
         SistemaAux[NetlistAux[i].b][NetlistAux[i].x].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].a].real -= 1;
         SistemaAux[NetlistAux[i].x][NetlistAux[i].b].real += 1;
         SistemaAux[NetlistAux[i].x][numeroVariaveisAux+1].real -= (NetlistAux[i].valor*cos((PI/180)*(NetlistAux[i].fase)));
         SistemaAux[NetlistAux[i].x][numeroVariaveisAux+1].img -= (NetlistAux[i].valor*sin((PI/180)*(NetlistAux[i].fase)));

      }

      else if (NetlistAux[i].nome[0] == 'I')
      {
         SistemaAux[NetlistAux[i].a][numeroVariaveisAux+1].real -= (NetlistAux[i].valor*cos((PI/180)*NetlistAux[i].fase));
         SistemaAux[NetlistAux[i].a][numeroVariaveisAux+1].img -= (NetlistAux[i].valor*sin((PI/180)*NetlistAux[i].fase));
         SistemaAux[NetlistAux[i].b][numeroVariaveisAux+1].real += (NetlistAux[i].valor*cos((PI/180)*NetlistAux[i].fase));
         SistemaAux[NetlistAux[i].b][numeroVariaveisAux+1].img += (NetlistAux[i].valor*sin((PI/180)*NetlistAux[i].fase));
      }
      else if (NetlistAux[i].nome[0] == 'Q')
      {
          SistemaAux[NetlistAux[i].a][NetlistAux[i].a].real += (NetlistAux[i].hoe-((NetlistAux[i].hre*NetlistAux[i].hfe)/NetlistAux[i].hie));
          SistemaAux[NetlistAux[i].a][NetlistAux[i].b].real += (NetlistAux[i].hfe/NetlistAux[i].hie);
          SistemaAux[NetlistAux[i].a][NetlistAux[i].c].real += (((NetlistAux[i].hfe*(NetlistAux[i].hre-1))/NetlistAux[i].hie)-NetlistAux[i].hoe);
          SistemaAux[NetlistAux[i].b][NetlistAux[i].a].real += (-(NetlistAux[i].hre/NetlistAux[i].hie));
          SistemaAux[NetlistAux[i].b][NetlistAux[i].b].real += (1/NetlistAux[i].hie);
          SistemaAux[NetlistAux[i].b][NetlistAux[i].c].real += ((NetlistAux[i].hre-1)/NetlistAux[i].hie);
          SistemaAux[NetlistAux[i].c][NetlistAux[i].a].real += (((NetlistAux[i].hre/NetlistAux[i].hie)*(NetlistAux[i].hfe+1))-NetlistAux[i].hoe);
          SistemaAux[NetlistAux[i].c][NetlistAux[i].b].real += (-((NetlistAux[i].hfe+1)/NetlistAux[i].hie));
          SistemaAux[NetlistAux[i].c][NetlistAux[i].c].real += (NetlistAux[i].hoe-(((NetlistAux[i].hre-1)*(NetlistAux[i].hfe+1))/NetlistAux[i].hie));
      }

      else
         return ELEMENTO_DESCONHECIDO;

      if(ui->cb_MostrarEstampas->isChecked() && numeroIntEstampas < 5)
      {
          ui->pte_JanelaTexto->insertPlainText(QString("Estampas após ") + NetlistAux[i].nome + QString(" para f = ") + QString::number(frequenciaAux) + QString(" :\n\n\n\n"));
          for (int linha = 1; linha < numeroVariaveisAux+1; linha++)
          {
              for (int coluna = 1; coluna < numeroVariaveisAux+2; coluna++)
                  ui->pte_JanelaTexto->insertPlainText(QString::number(SistemaAux[linha][coluna].real, 'f', 2) + QString("+j") + QString::number(SistemaAux[linha][coluna].img, 'f', 2) +
                                                       QString("        "));
              ui->pte_JanelaTexto->insertPlainText("\n\n\n\n");
          }
      }
   }
   numeroIntEstampas++;
   return OK;
}
