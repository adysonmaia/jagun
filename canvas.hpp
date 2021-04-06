#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <iostream>
#include "figura.hpp"
#include "polilinha.hpp"
#include "figuraBound.hpp"
#include "poligono.hpp"
#include "arco.hpp"

using namespace std;

class Canvas : public QGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setBufferConstrutor(bool valorConstrutor);
    
    // muda o numero de lados do poligono
    void setNumLadosPoligono(int);
    
    void setAnguloArco(int);

    void setEstado(int);
   
    //retornando o array de Figuras
    QList<Figura*> getArrayFiguras();    

    //faz picking para as figuras
    Figura* pick(QPoint);
    
    //faz picking para os pontos de referencia da figura selecionada
    void pickV(QPoint);
    
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    
private slots:
  void escolheNovaCor();
  void deletaFigura();
private:
	// o mais importante a lista de figuras
	QList<Figura*> arrayFiguras;
	// total de figuras
	int totalFiguras;
	 
	 //Figura selecionada
    Figura* figSelect;
    
    //posicao do ponto de referencia da figura selecionada selecionado no vetor figura->getPontos()
    int posPntSelect;
    
    //armazena que figura será desenhada, use enum de figura.hpp
    int estadoatual;
    //diz quando deve ser desenhado na tela
    bool desenha;
    //diz quando o botão esquerdo foi pressionado para desenhar figura
    bool botEsqPress;
	
	// diz que o botao esquerdo foi pressionado para editar figura
	bool botEsqPressEdit;
    //posição inicial do mouse
    QPoint posIni;
    //posição atual do mouse
    QPoint posAtu;
    // quando o usuario estiver pre desenha a figura na tela essa cor e' mostrada
    QColor corPreDesenho;
    // depois que a figura é colocado oficialmente na tela essa e' a sua cor
    QColor corDesenho;
    
	// menu quando o usuario clica com o botao direito
	QMenu *menuPopUp;
    // esse e' coracao do Jagun, aqui que tude e' mostrado ao usuario
    void draw(GLenum);
    
    // usado na draw. desenha as figuras definitivas
    void desenhaArrayFiguras(GLenum);
    // usado na draw. Desenha a figura temporaria
    void desenhaBuffer();
    // usado em mousePressEvent. Insere figura do buffer na lista. 
    void insereFiguraDoBufferParaLista(QMouseEvent*);
    // usado em mouseReleaseEvent. atualiza a figura do buffer
    void atualizaFiguraDoBuffer(QMouseEvent*);
    // numero de lados do poligono
    int numLadosPoligono;
    // angulo do arco
    int anguloArco;
    
    /**
     * Verifica se um ponto esta dentro de um retangulo
     * @param ponto ponto
     * @param centro centro do retangulo
     * @param largura largura do retangulo
     * @param altura altura do retangulo
     * @return bool esta ou nao esta dentro do retangulo
     */
    bool pontoDentroRetangulo( QPointF , QPointF, float, float );
        
    // permiti uma figura do buffer ser instanciada ou nao
    bool construtor;
    /* variaveis de buffer;*/
    Polilinha *linha;
    Polilinha *plinha;
    Poligono  *poligTemp;
    Arco      *arcTemp;
    QPointF pointIni;
    QPointF pointAtu;
	
	// cria os menu(s) necessarios
	void createMenus();
	
	// cria as acoes necessarios()
	void createActions();
	
	QAction *mudaCorAction;
	QAction *deletaFiguraAction;

};

#endif



