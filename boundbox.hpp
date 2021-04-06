#ifndef BOUND_BOX_HPP
#define BOUND_BOX_HPP

#include <QtOpenGL>
#include "figuraBound.hpp"
#include <math.h>
#include <iostream>
using namespace std;

class BoundBox;

/**
 * classe da bound box
 */
class BoundBox : public FiguraBound {
	
public:
	/** Construtor
	 * @param id identificacao da boundbox
	 * @param QColor cor da boundbox
	 * @param QPoint centro da bounding box
	 * @param QPoint ponto de referencia para o raio box
	 * @param figura figura que a buondbox envolve
	 */
	BoundBox(int , QColor, QPointF,QPointF,FiguraBound*);
  
  /**
   * Destrutor
   */
  ~BoundBox();

private:
	FiguraBound* figuraBound; //figura que a buondbox envolve

public:
	
	/**
	 * Faz o escalonamento da boundbox por um fator
	 * @param fator
	 */
	void Escala(float) ;
	
	 /**
	  * desenha a boundbox na tela
	  * @param mode modo da pintura GL_SELECT ou GL_RENDER
	  * @return void
	  */
	void Desenha(GLenum);

   /**
	 * desenha a bounbox selecionada
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	void DesenhaSelecionado(GLenum);
	
	/**
	 * Pega todos pontos de referencia da figura
	 * @return lista de todos os pontos de referencia
	 */
	QList<QPointF> getPontos();
	
	
};

#endif //BOUND_BOX_HPP
