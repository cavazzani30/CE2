#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::arquivarResultado(QString arquivoEntradaEndereco)
{
   QChar tipoAuxiliar;

   listaNomeArquivo = nomeArquivo.split(".");
   nomeArquivo = listaNomeArquivo[0];
   nomeArquivo = (nomeArquivo + QString(".tab"));

   QFile arquivo(nomeArquivo);
   QFile arquivoEntrada(arquivoEntradaEndereco);

   if(!arquivo.open(QFile::WriteOnly | QFile::Text))
   {
       QMessageBox::information(this, tr("Erro!"), QString("Não foi possível abrir o arquivo para gerar a tabela."));
       return ERRO_ABRINDO_ARQUIVO_ESCRITA;
   }

   if(!arquivoEntrada.open(QFile::ReadOnly | QFile::Text))
   {
       QMessageBox::information(this, tr("Erro!"), QString("Não foi possível abrir o arquivo para gerar a tabela."));
       return ERRO_ABRINDO_ARQUIVO_ESCRITA;
   }

   QTextStream out(&arquivo);
   QTextStream in(&arquivoEntrada);

   out<<QString("f ");

   for (int indiceNos = 1; indiceNos <= numeroNos; indiceNos++)
       out<<QString::number(indiceNos) + QString("m ") + QString::number(indiceNos) + QString("f ");

   for (int indiceElemento = 1; indiceElemento <= numeroElementos; indiceElemento++)
   {
       tipoAuxiliar = Netlist[indiceElemento].nome[0];

       if (tipoAuxiliar == QChar('E') || tipoAuxiliar == QChar('F') || tipoAuxiliar == QChar('V') || tipoAuxiliar == QChar('O') || tipoAuxiliar == QChar('L'))
           out<<QString(" j") + Netlist[indiceElemento].nome + QString("m") + QString(" j") + Netlist[indiceElemento].nome + QString("f ");
       else if (Netlist[indiceElemento].nome[0] == 'H')
       {
           out<<QString(" j") + QString::number(Netlist[indiceElemento].x) + Netlist[indiceElemento].nome + QString("m") +
                QString(" j") + QString::number(Netlist[indiceElemento].x) + Netlist[indiceElemento].nome + QString("f ");
           out<<QString(" j") + QString::number(Netlist[indiceElemento].y) + Netlist[indiceElemento].nome + QString("m") +
                QString(" j") + QString::number(Netlist[indiceElemento].y) + Netlist[indiceElemento].nome + QString("f ");
       }
   }

   out<<endl;

   while(!in.atEnd())
   {
       out<<in.readLine();
       out<<endl;
   }

   arquivoEntrada.remove();
   arquivo.close();

   ui->pte_JanelaTexto->insertPlainText(QString("Tabela de resultados salva em ") + nomeArquivo + QString('\n'));

   return OK;
}
