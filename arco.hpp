#ifndef ARCO_HPP
#define ARCO_HPP


#include "figuraBound.hpp"
#include "boundbox.hpp"
#include <QtOpenGL>
#include <iostream>
using namespace std;

/**
 * classe do arco
 */
class Arco : public FiguraBound {
public:
	/**
	 * Construtor
	 * @param id      identificao da figura
	 * @param cor     cor de preenchimento
	 * @param centro  centro do arco
	 * @param extremo primeiro extremo do arco
	 * @param angulo  angulo para descobri o segundo extremo
	 */
	Arco(int, QColor, QPointF, QPointF, float);
	
	/**
	 * Destrutor
	 */
	~Arco();
	
private:
	
	float angulo;  //angulo para descobrir o outro extremo do arco

public:
   /**
	 * desenha o arco na tela
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	void Desenha(GLenum);
	
  /**
	 * Retorna o angulo do arco
	 * @return angulo do arco
	 */
   float getAngulo(); 
	
};

#endif //ARCO_HPP
