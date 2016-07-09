#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::zerarSistema(complexo SistemaAux[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2])
{
   for (int linhas = 0; linhas <= NUMERO_MAXIMO_NOS+1; linhas++)
      for (int colunas = 0; colunas <= NUMERO_MAXIMO_NOS+2; colunas++)
      {
         SistemaAux[linhas][colunas].real = 0;
         SistemaAux[linhas][colunas].img = 0;
      }
}

/*void MainWindow::zerarVetor(complexo Vetor[NUMERO_MAXIMO_NOS+1])
{
   for (int indice = 0; indice <= NUMERO_MAXIMO_NOS+1; indice++)
   {
      Vetor[indice].real = 0;
      Vetor[indice].img = 0;
   }
}*/

void MainWindow::mostrarVetor(complexo ResultadoComplexoAux [NUMERO_MAXIMO_NOS+1], int numeroVariaveisAux, int numeroNosAux)
{
    for (int indiceVetor = 1; indiceVetor <= numeroVariaveisAux; indiceVetor++)
    {
        if(indiceVetor <= numeroNosAux)
            ui->pte_JanelaTexto->insertPlainText(QString("  E") + QString::number(indiceVetor) + QString(":   "));
        else
            ui->pte_JanelaTexto->insertPlainText(QString("  J") + QString::number(indiceVetor) + QString(":   "));
        ui->pte_JanelaTexto->insertPlainText(QString::number(ResultadoComplexoAux[indiceVetor].real, 'G', 2));
        if(ResultadoComplexoAux[indiceVetor].img > 0)
            ui->pte_JanelaTexto->insertPlainText(QString(" + j") + QString::number(ResultadoComplexoAux[indiceVetor].img, 'G', 2));
        else
            ui->pte_JanelaTexto->insertPlainText(QString(" - j") + QString::number((ResultadoComplexoAux[indiceVetor].img * (-1)), 'G', 2));
        ui->pte_JanelaTexto->insertPlainText(QString("\n\n\n"));
    }
}

void MainWindow::resolver(int numeroPontosAux, QString tipoAnaliseAux)
{
    listaNomeArquivo = nomeArquivo.split(".");
    nomeArquivoAux = listaNomeArquivo[0];
    nomeArquivoAux = (nomeArquivoAux + QString("_buffer") + QString(".temp"));

    QFile arquivo(nomeArquivoAux);

    if(!arquivo.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, tr("Erro!"), QString("Não foi possível abrir o arquivo para gerar a tabela."));
        return;
    }

    QTextStream out(&arquivo);

    ui->pte_JanelaTexto->insertPlainText(QString("\n\n"));

    for(float frequenciaAux = frequenciaInicial; frequenciaAux < frequenciaFinal; )
    {
        zerarSistema(Sistema);
        //ui->pte_JanelaTexto->insertPlainText(QString::number(frequenciaAux, 'f', 6) + QString("\n"));
        if(montarEstampas(Netlist, Sistema, frequenciaAux, numeroElementos, numeroVariaveis))
        {
            QMessageBox::information(this, tr("Erro!"), QString("Há um resistor com valor zero no netlist."));
            ui->pte_JanelaTexto->insertPlainText(QString("\nERRO!\n"));
            ui->pte_JanelaTexto->insertPlainText(QString("\nAnálise Abortada.\n"));
            return;
        }

        if(gaussJordan(Sistema, numeroVariaveis))
        {
            QMessageBox::information(this, tr("Erro!"), QString("Houve um erro na divisão de um número complexo."));
            ui->pte_JanelaTexto->insertPlainText(QString("\nERRO!\n"));
            ui->pte_JanelaTexto->insertPlainText(QString("\nAnálise Abortada.\n"));
            return;
        }

        for (int indiceResultado = 1; indiceResultado <= numeroVariaveis; indiceResultado++)
        {
            ResultadoComplexo[indiceResultado].real = Sistema[indiceResultado][numeroVariaveis+1].real;
            ResultadoComplexo[indiceResultado].img = Sistema[indiceResultado][numeroVariaveis+1].img;
        }

        if(ui->cb_MostrarResultados->isChecked() && numeroIntResulado < 5)
        {
            ui->pte_JanelaTexto->insertPlainText(QString("Solução do sistema para a frequência f = ") + QString::number(frequenciaAux, 'G', 6) + QString("\n\n"));
            mostrarVetor(ResultadoComplexo, numeroVariaveis, numeroNos);
            numeroIntResulado++;
        }

        out<<QString::number(frequenciaAux, 'G', 4);
        for (int indiceResultado = 1; indiceResultado <= numeroVariaveis; indiceResultado++)
        {
            Resultado[indiceResultado].modulo = sqrt(pow(ResultadoComplexo[indiceResultado].real, 2.0) + pow(ResultadoComplexo[indiceResultado].img, 2.0));
            Resultado[indiceResultado].fase = ((180/PI)*atan2(ResultadoComplexo[indiceResultado].img,ResultadoComplexo[indiceResultado].real));


            out<<QString(" ") + QString::number(Resultado[indiceResultado].modulo, 'G', 4) + QString(" ") + QString::number(Resultado[indiceResultado].fase, 'f', 0) + QString ("  ");
        }
        out<<endl;

        if (tipoAnaliseAux == QString("LIN"))
            frequenciaAux += ((frequenciaFinal-frequenciaInicial)/numeroPontosAux);
        else if(tipoAnaliseAux == QString("DEC"))
            frequenciaAux = frequenciaAux*pow(10.0, (1.0/(numeroPontosAux-1)));
        else if(tipoAnaliseAux == QString("OCT"))
            frequenciaAux = frequenciaAux*pow(2.0, (1.0/(numeroPontosAux-1)));
    }
}
