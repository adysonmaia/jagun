#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QCursor>
#include <QPixmap>
#include <QBitmap>
#include <QWidget>
#include <QFile>
#include <QSpinBox>
#include <QXmlDefaultHandler>
#include <QDomNode>
#include <QTextStream>
#include "figura.hpp"
#include "polilinha.hpp"
#include <iostream>
using namespace std;

// classes do Jangun
class Figura;
class Polilinha;

// classe do Qt
class QAction;
class QLabel;
class Canvas;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
   
private slots:
    void NovoArquivo();
    void Abrir();
    bool Salvar();
    bool SalvarComo();
    void AtualizarStatusBar();
    void Sobre();

    /* slots da toolbar esquerda */
    //void preAcaoArco();
    void setPadrao();
    void preDesenhoPolilinha();
    void preDesenhoPoligono();
    void preDesenhoArco();
       
    
private:
	
    void createActions();
    void createMenus();
    void createToolBars();
private slots:

    void getNumLadosPoligono(int);
    void getAnguloArco(int);
    
private:
    
    /*antes de salvar verifica as mudanças no arquivo*/
    bool okToContinue();
    /*Método para escrever em XML*/
    bool EscreverXML(const QString &arquivoNome);
    /*Colocar novo arquivo corrente*/
    void setArquivoCorrente(const QString &fileName);
    /*nome do arquivo completo*/
    QString strippedName(const QString &fullFileName);
    /*salvar arquivo no xml*/
    bool salvarArquivo(const QString &fileName);
    
    /** Cursor */
    QCursor cursor;
    QBitmap bitmapCursor;
    
    Canvas *canvas;
    
    /*Arquivo corrente*/
    QString curFile;
 
    QLabel *statusBarLabel;
    
    QAction *separatorAction;

    QMenu *arquivoMenu;
    QMenu *ajudaMenu;

    //toolbars
    QToolBar *arquivoToolBar;
    QToolBar *ferramentasToolBar;
    QToolBar *propriedadesPoligonoToolBar;
    QToolBar *propriedadesArcoToolBar;

    //spinBox do numero de lados do polígono
    QSpinBox *spinNumLadosPolig;
    QSpinBox *spinAnguloArco;
     
    //Label do numero de Lados do polígono
    QLabel *numLadosPoligLab;
    QLabel *labelAnguloArco;

    /* acoes do menu superior e da toolbar superior */
    QAction *novoAction; 
    QAction *abrirAction;
    QAction *sobreAction;
    QAction *salvarAction;
    QAction *salvarComoAction;
    QAction *sairAction;

    /* acoes da toolbar esquerda */
   
    QAction *padraoAction;
    QAction *polilinhaAction;
    QAction *poligonoAction;
    QAction *arcoAction; 

    

};
#endif






