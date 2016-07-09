#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pb_AbrirNetlist, SIGNAL(clicked()), this, SLOT(lerNetlist()));
    connect(ui->pb_Fechar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->cb_ignorarComando, SIGNAL(clicked()), this, SLOT(linhaComando()));

    ui->le_frequenciaInicial->setValidator(new QDoubleValidator(1, 10E30, 12, ui->le_frequenciaInicial));
    ui->le_frequenciaFinal->setValidator(new QDoubleValidator(1, 10E30, 12, ui->le_frequenciaFinal));
    ui->le_numeroPontos->setValidator(new QIntValidator(0, 1E6, ui->le_numeroPontos));

    ui->le_frequenciaInicial->hide();
    ui->le_frequenciaFinal->hide();
    ui->le_numeroPontos->hide();
    ui->l_frequenciaInicial->hide();
    ui->l_frequenciaFinal->hide();
    ui->l_numeroPontos->hide();
    ui->rb_linear->hide();
    ui->rb_decada->hide();
    ui->rb_oitava->hide();

    ui->pte_JanelaTexto->insertPlainText(QString("Programa criado por:\nBruno Campello de Andrade - email: bruno.candrade@poli.ufrj.br\n") +
                                         QString("Vínicius Allemand Mancebo - email: vinicius.allemand@poli.ufrj.br\n") +
                                         QString("Bernardo Teixeira Marques - email: btm@poli.ufrj.br\n"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linhaComando(void)
{
    if(ui->cb_ignorarComando->isChecked())
    {
        ui->le_frequenciaInicial->show();
        ui->le_frequenciaFinal->show();
        ui->le_numeroPontos->show();
        ui->l_frequenciaInicial->show();
        ui->l_frequenciaFinal->show();
        ui->l_numeroPontos->show();
        ui->rb_linear->show();
        ui->rb_decada->show();
        ui->rb_oitava->show();
    }
    else
    {
        ui->le_frequenciaInicial->hide();
        ui->le_frequenciaFinal->hide();
        ui->le_numeroPontos->hide();
        ui->l_frequenciaInicial->hide();
        ui->l_frequenciaFinal->hide();
        ui->l_numeroPontos->hide();
        ui->rb_linear->hide();
        ui->rb_decada->hide();
        ui->rb_oitava->hide();
    }
}

int MainWindow::atribuirNumero(QString nome)
{
    int i = 0;
    bool achou = false;

    while ((!achou) && (i <= numeroVariaveis))
        if (!(achou =! !(nome == Lista[i])))
            i++;
    if (!achou)
    {
        numeroVariaveis++;
        Lista[numeroVariaveis] = nome;
        return numeroVariaveis; // novo no
    }
    else
        return i; //no ja conhecido
}

//------------------------------------------------------------------------------------------------------
//FUNCAO QUE LISTA O NETLIST
//-----------------------------------------------------------------------------------------------------
void MainWindow::listarNetlist(void)
{
   ui->pte_JanelaTexto->insertPlainText(QString("\nVariáveis Internas:\n\n"));

   for (int i = 0; i <= numeroVariaveis; i++)
       ui->pte_JanelaTexto->insertPlainText(QString::number(i) + QString(" -> ") + Lista[i] + QString('\n'));
   ui->pte_JanelaTexto->insertPlainText(QString("\nNetlist interno final\n"));
   for (int i = 1; i <= numeroElementos; i++)
   {
       tipo = Netlist[i].nome[0];
       if (tipo == 'R' || tipo == 'I' || tipo == 'V')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + QString::number(Netlist[i].a) + QString(" ") + QString::number(Netlist[i].b) + QString(" ") +
                                                QString::number(Netlist[i].valor, 'g', 12) + QString('\n'));
       else if (tipo == 'C' || tipo == 'L')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + QString::number(Netlist[i].a) + QString(" ") + QString::number(Netlist[i].b) + QString(" ") +
                                                QString::number(Netlist[i].valor, 'g', 12) + QString('\n'));
       else if (tipo == 'K')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + Netlist[i].la + QString(" ") + Netlist[i].lb + QString(" ") + QString::number(Netlist[i].valor, 'g', 12) +
                                                QString('\n'));
       else if (tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'H')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + QString::number(Netlist[i].a) + QString(" ") + QString::number(Netlist[i].b) + QString(" ") +
                                                QString::number(Netlist[i].c) + QString(" ") + QString::number(Netlist[i].d) + QString(" ") + QString::number(Netlist[i].valor, 'g', 12) +
                                                QString('\n'));
       else if (tipo == 'O')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + QString::number(Netlist[i].a) + QString(" ") + QString::number(Netlist[i].b) + QString(" ") +
                                                QString::number(Netlist[i].c) + QString(" ") + QString::number(Netlist[i].d) + QString('\n'));
       else if (tipo == 'Q')
           ui->pte_JanelaTexto->insertPlainText(Netlist[i].nome + QString(" ") + QString::number(Netlist[i].a) + QString(" ") + QString::number(Netlist[i].b) + QString(" ") +
                                                QString::number(Netlist[i].c) + QString(" ") + QString::number(Netlist[i].hfe) + QString(" ") + QString::number(Netlist[i].hie) + QString(" ") +
                                                QString::number(Netlist[i].hre) + QString(" ") + QString::number(Netlist[i].hoe) + QString('\n'));
       if (tipo == 'V' || tipo == 'E' || tipo == 'F' || tipo == 'O')
           ui->pte_JanelaTexto->insertPlainText(QString("Corrente jx: ") + QString::number(Netlist[i].x) + QString('\n'));
       else if (tipo == 'H')
           ui->pte_JanelaTexto->insertPlainText(QString("Correntes jx e jy: ") + QString::number(Netlist[i].x) + QString(", ") + QString::number(Netlist[i].y) + QString('\n'));
   }
   ui->pte_JanelaTexto->insertPlainText(QString("\nO circuito tem ") + QString::number(numeroNos) + QString(" nós, ") + QString::number(numeroVariaveis) + QString(" variáveis e ") +
                                        QString::number(numeroElementos) + QString(" elementos.\n\n\n"));
}

//------------------------------------------------------------------------------------------------------
//FIM DA FUNCAO QUE LISTA O NETLIST
//------------------------------------------------------------------------------------------------------

void MainWindow::lerNetlist(void)
{
    numeroElementos = 0;
    numeroVariaveis = 0;
    numeroNos = 0;
    Lista[0] = QString("0");
    numeroIntEstampas = 0;
    numeroIntResulado = 0;

    nomeArquivo = QFileDialog::getOpenFileName(this, tr("Abrir Netlist"), "./", "Netlist(*.net)");

    QFile arquivo(nomeArquivo);

    if(!arquivo.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, tr("Erro!"), QString("Não foi possível abrir o arquivo."));
        return;
    }

    ui->pte_JanelaTexto->clear();
    ui->pte_JanelaTexto->insertPlainText(QString("Lendo a netlist ") + nomeArquivo + QString("\n\n"));

    QTextStream in(&arquivo);

    in.readLine(); //despreza a primeira linha do netlist.
    while(!in.atEnd())
    {
        linhaNetlist = in.readLine();
        numeroElementos++; //netlist começa na posição 1
        if(numeroElementos > NUMERO_MAXIMO_ELEMENTOS)
        {
            QMessageBox::information(this, tr("Erro!"), QString("A netlist estrapolou o número máximo de elementos permitidos no programa."));
            ui->pte_JanelaTexto->insertPlainText(QString("\nErro...\n"));
            ui->pte_JanelaTexto->insertPlainText(QString("Análise Encerrada.\n"));
            return;
        }

        linhaNetlist[0] = linhaNetlist[0].toUpper();
        tipo = linhaNetlist[0];
        listaLinhaNetlist = linhaNetlist.split(" ");

        if(tipo == 'R')
        {
           Netlist[numeroElementos].nome = listaLinhaNetlist[0];
           na = listaLinhaNetlist[1];
           nb = listaLinhaNetlist[2];
           Netlist[numeroElementos].valor = listaLinhaNetlist[3].toFloat();
           ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " ") + QString::number(Netlist[numeroElementos].valor) + QString('\n'));
           Netlist[numeroElementos].a = atribuirNumero(na);
           Netlist[numeroElementos].b = atribuirNumero(nb);
        }
        else if(tipo == 'C' || tipo == 'L')
        {
           Netlist[numeroElementos].nome = listaLinhaNetlist[0];
           na = listaLinhaNetlist[1];
           nb = listaLinhaNetlist[2];
           Netlist[numeroElementos].valor = listaLinhaNetlist[3].toFloat();
           ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " ") + QString::number(Netlist[numeroElementos].valor) + QString('\n'));
           Netlist[numeroElementos].a = atribuirNumero(na);
           Netlist[numeroElementos].b = atribuirNumero(nb);
        }
        else if(tipo == 'K')
        {
            Netlist[numeroElementos].nome = listaLinhaNetlist[0];
            Netlist[numeroElementos].la = listaLinhaNetlist[1];
            Netlist[numeroElementos].lb = listaLinhaNetlist[2];
            Netlist[numeroElementos].valor = listaLinhaNetlist[3].toFloat();
            ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + Netlist[numeroElementos].la + " " + Netlist[numeroElementos].lb + " ") +
                                                 QString::number(Netlist[numeroElementos].valor) + QString('\n'));
        }
        else if(tipo == 'I' || tipo == 'V')
        {
            Netlist[numeroElementos].nome = listaLinhaNetlist[0];
            na = listaLinhaNetlist[1];
            nb = listaLinhaNetlist[2];
            Netlist[numeroElementos].valor = listaLinhaNetlist[3].toFloat();
            Netlist[numeroElementos].fase = listaLinhaNetlist[4].toFloat();
            ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " ") + QString::number(Netlist[numeroElementos].valor) +
                                                 QString(" ") + QString::number(Netlist[numeroElementos].fase) + QString('\n'));
            Netlist[numeroElementos].a = atribuirNumero(na);
            Netlist[numeroElementos].b = atribuirNumero(nb);
        }
        else if(tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'H')
        {
            Netlist[numeroElementos].nome = listaLinhaNetlist[0];
            na = listaLinhaNetlist[1];
            nb = listaLinhaNetlist[2];
            nc = listaLinhaNetlist[3];
            nd = listaLinhaNetlist[4];
            Netlist[numeroElementos].valor = listaLinhaNetlist[5].toFloat();
            ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " " + nc + " " + nd + " ") + QString::number(Netlist[numeroElementos].valor) +
                                                 QString('\n'));
            Netlist[numeroElementos].a = atribuirNumero(na);
            Netlist[numeroElementos].b = atribuirNumero(nb);
            Netlist[numeroElementos].c = atribuirNumero(nc);
            Netlist[numeroElementos].d = atribuirNumero(nd);
        }
        else if(tipo == 'O')
        {
            Netlist[numeroElementos].nome = listaLinhaNetlist[0];
            na = listaLinhaNetlist[1];
            nb = listaLinhaNetlist[2];
            nc = listaLinhaNetlist[3];
            nd = listaLinhaNetlist[4];
            ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " " + nc + " " + nd + '\n'));
            Netlist[numeroElementos].a = atribuirNumero(na);
            Netlist[numeroElementos].b = atribuirNumero(nb);
            Netlist[numeroElementos].c = atribuirNumero(nc);
            Netlist[numeroElementos].d = atribuirNumero(nd);
        }
        else if(tipo == 'Q')
        {
            Netlist[numeroElementos].nome = listaLinhaNetlist[0];
            na = listaLinhaNetlist[1];
            nb = listaLinhaNetlist[2];
            nc = listaLinhaNetlist[3];
            Netlist[numeroElementos].hfe = listaLinhaNetlist[4].toFloat();
            Netlist[numeroElementos].hie = listaLinhaNetlist[5].toFloat();
            Netlist[numeroElementos].hre = listaLinhaNetlist[6].toFloat();
            Netlist[numeroElementos].hoe = listaLinhaNetlist[7].toFloat();
            ui->pte_JanelaTexto->insertPlainText(QString(Netlist[numeroElementos].nome + " " + na + " " + nb + " " + nc + " ") + QString::number(Netlist[numeroElementos].hfe) +
                                                 QString(" ") + QString::number(Netlist[numeroElementos].hie) + QString(" ") + QString::number(Netlist[numeroElementos].hre) + QString(" ") +
                                                 QString::number(Netlist[numeroElementos].hoe) + QString(" ") +  QString('\n'));
            Netlist[numeroElementos].a = atribuirNumero(na);
            Netlist[numeroElementos].b = atribuirNumero(nb);
            Netlist[numeroElementos].c = atribuirNumero(nc);
        }
        else if(tipo == '*')
        {
            numeroElementos--;
            ui->pte_JanelaTexto->insertPlainText(QString("\n-->Comentário: ") + linhaNetlist + '\n');
        }
        else if(tipo == '.')
        {
            numeroElementos--;
            tipoAnalise = listaLinhaNetlist[1];
            numeroPontos = listaLinhaNetlist[2].toInt();
            frequenciaInicial = listaLinhaNetlist[3].toFloat();
            frequenciaFinal = listaLinhaNetlist[4].toFloat();
            ui->pte_JanelaTexto->insertPlainText(listaLinhaNetlist[0] + QString(" ") + tipoAnalise + QString(" ") + QString::number(numeroPontos) + QString(" ") +
                                                 QString::number(frequenciaInicial) + QString(" ") + QString::number(frequenciaFinal) + QString('\n'));
        }
        else
        {
            QMessageBox::information(this, tr("Erro!"), QString("Um elemento desconhecido foi encontrado na netlist."));
            ui->pte_JanelaTexto->insertPlainText(QString("\nErro...\n"));
            ui->pte_JanelaTexto->insertPlainText(QString("Análise Encerrada.\n"));
            return;
        }
        arquivo.close();
    }

        //------------------------------------------------------------------------------------------------------
        //ACRESCENTA VARIAVEIS DE CORRENTE ACIMA DOS NOS, ANOTANDO NO NETLIST
        //------------------------------------------------------------------------------------------------------

    numeroNos = numeroVariaveis;
    for (int i = 1; i <= numeroElementos; i++)
    {
        tipo = Netlist[i].nome[0];

        if (tipo == 'V' || tipo == 'E' || tipo == 'F' || tipo == 'O' || tipo == 'L')
        {
            numeroVariaveis++;
            if (numeroVariaveis > NUMERO_MAXIMO_NOS)
            {
                ui->pte_JanelaTexto->insertPlainText(QString("\nERRO!\n"));
                printf("As correntes extras excederam o numero de variaveis permitido.\n");
                return;
            }
            Lista[numeroVariaveis] = QString("j");
            Lista[numeroVariaveis] = (Lista[numeroVariaveis] + Netlist[i].nome);
            Netlist[i].x = numeroVariaveis;
        }
        else if (tipo == 'H')
        {
            numeroVariaveis = (numeroVariaveis + 2);
            if (numeroVariaveis > NUMERO_MAXIMO_NOS)
            {
                printf("\nERRO!\n");
                printf("As correntes extra excederam o numero de variaveis permitido.\n");
                return;
            }
            Lista[numeroVariaveis-1] = QString("jx");
            Lista[numeroVariaveis-1] = (Lista[numeroVariaveis-1] + Netlist[i].nome);
            Netlist[i].x = (numeroVariaveis - 1);
            Lista[numeroVariaveis] = QString("jy");
            Lista[numeroVariaveis] = (Lista[numeroVariaveis] + Netlist[i].nome);
            Netlist[i].y = numeroVariaveis;
        }
    }

   //------------------------------------------------------------------------------------------------------
   //FIM -- ACRESCENTA VARIAVEIS DE CORRENTE ACIMA DOS NOS, ANOTANDO NO NETLIST
   //------------------------------------------------------------------------------------------------------

    if(ui->cb_ignorarComando->isChecked())
    {
        numeroPontos = ui->le_numeroPontos->text().toInt();
        frequenciaInicial = ui->le_frequenciaInicial->text().toFloat();
        frequenciaFinal = ui->le_frequenciaFinal->text().toFloat();
        if(ui->rb_linear->isChecked())
            tipoAnalise = QString("LIN");
        else if(ui->rb_decada->isChecked())
            tipoAnalise = QString("DEC");
        else if(ui->rb_oitava->isChecked())
            tipoAnalise = QString("OCT");
    }

    listarNetlist();
    resolver(numeroPontos, tipoAnalise);
    arquivarResultado(nomeArquivoAux);
}
