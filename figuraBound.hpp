#ifndef FIGURA_BOUND_HPP
#define FIGURA_BOUND_HPP

class FiguraBound;

#include "figura.hpp"
#include <QPointF> // classe de manipulcao de pontos flutuantes do Qt
#include <math.h>
#include <iostream>
using namespace std;


/**
 * define o valor padrao para pi
 */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

/**
 * classe de figuras que contem uma boundbox
 */
class FiguraBound : public Figura {

public:
	/**
	 * Construtor, recebe o id, a cor de preenchimento, centro e o boundbox da figura
	 * @param id // id da figura
	 * @param cor // cor da figura
	 * @param centro // centro da figura
	 * @param pReferencia ponto de referencia
	 */
	FiguraBound(int , QColor, QPointF,QPointF);
	
	/**
	 * Destrutor
	 */
	~FiguraBound() { delete boundBox; };

protected:

	float raio; //raio da circunferencia circunscrita no poligono regular
	QPointF centro; // centro da figura
	QPointF pReferencia; // ponto de referencia
	FiguraBound *boundBox; //boundbox da figura
	 
public:
	/**
	 * Move o centro da figua
	 * @param destino
	 */
	virtual void MoveC(QPointF);
	

	/**
	 * muda o raio pegando um ponto de referencia que é calculado pela distancia da raiz a ele
	 * @param QPoint pRef
	 */
	void setRaio(QPointF);
	
	 /**
	 * move um ponto de referencia da posicao de origem, para a posicao de destino
	 * @param origem
	 * @param destino
	 * @return true se o vertice existe
	 * @return false se o vertice nao existe
	 */
	virtual bool moveV(QPointF,QPointF) ;
	
	virtual bool moveV(int,QPointF);
	
	/**
	 * desenha o arco selecionado
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	virtual void DesenhaSelecionado(GLenum);
	
	/**
	 * Pega todos pontos de referencia da figura
	 * @return lista de todos os pontos de referencia
	 */
	virtual QList<QPointF> getPontos();
};

#endif //FIGURA_BOUND_HPP
