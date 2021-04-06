#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "figuraBound.hpp"
#include "boundbox.hpp"
#include <QtOpenGL>
#include <iostream>
using namespace std;
/**
 * clase que controla as figuras do tipo poligono
 */
class Poligono : public FiguraBound {
public:
	/**
	 * Construtor, recebe o id, a cor de preenchimento, o ponto do centro, um ponto de referencia para o raio e quantidade de lados
	 * @param id
	 * @param cor
	 * @param centro
	 * @param pReferencia
	 * @param qtdlados
	 */
	Poligono(int, QColor, QPointF,QPointF,int);
	
	/**
	 * Destrutor
	 */
	~Poligono();

private:
	
	int lados;  //quantidades de lados do poligono

public:

	/**
	 * Faz o escalonamento do poligono por um fator
	 * @param fator
	 */
	void Escala(float) ;
		
   /**
	 * desenha o poligono na tela
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	void Desenha(GLenum);
	
   /**
	 * Retorna o raio do poligono
	 * @return raio do poligono
	 */
  int getLados(); 
	
};

#endif //POLIGONO_HPP
