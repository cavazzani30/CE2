#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QString>
#include <QChar>
#include <QStringList>
#include <QMessageBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QFileDialog>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QValidator>
#include <QDoubleValidator>
#include <QIntValidator>
#include <math.h>

#include "defines.h"
#include "constantes.h"

namespace Ui {
class MainWindow;
}

class elemento
{
public:
    QString nome,
            la, lb;
    float valor, fase, hfe, hie, hre, hoe;
    int a, b, c, d, x, y;
};

class complexo
{
public:
    float real, img;
};

class resultado
{
public:
    float modulo, fase;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int atribuirNumero(QString);
    int montarEstampas(elemento[NUMERO_MAXIMO_ELEMENTOS], complexo[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2], float, int, int);
    void resolver(int, QString);
    void mostrarVetor(complexo[NUMERO_MAXIMO_NOS+1], int, int);
    int arquivarResultado(QString);
    int divisaoComplexa(complexo, complexo, complexo*);
    complexo ProdutoComplexo(complexo, complexo);
    int gaussJordan(complexo [NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2], int);
    void zerarSistema(complexo [NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2]);
    void zerarVetor(complexo [NUMERO_MAXIMO_NOS+1]);
    void listarNetlist(void);
    int numeroIntEstampas,
        numeroIntResulado;
    ~MainWindow();

public slots:
    void lerNetlist(void);
    void linhaComando(void);

private:
    Ui::MainWindow *ui;

    QString mensagemAjuda,
            nomeArquivo,
            nomeArquivoAux,
            linhaNetlist,
            linhaNetlistAux,
            na, nb, nc, nd,
            tipoAnalise,
            Lista[NUMERO_MAXIMO_NOS+1];
    QStringList listaLinhaNetlist,
                listaLinhaNetlistAux,
                listaNomeArquivo;
    QChar tipo;
    elemento Netlist [NUMERO_MAXIMO_ELEMENTOS];
    complexo Sistema[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2],
             matrizSistema[NUMERO_MAXIMO_NOS+1][NUMERO_MAXIMO_NOS+2],
             ResultadoComplexo[NUMERO_MAXIMO_NOS+1];
    int numeroElementos,
        numeroVariaveis,
        numeroNos,
        numeroPontos;
    float frequenciaInicial, frequenciaFinal;
    resultado Resultado[NUMERO_MAXIMO_NOS+1];
};

#endif // MAINWINDOW_H
