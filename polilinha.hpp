#ifndef POLILINHA_HPP_
#define POLILINHA_HPP_

class Polilinha;

#include <QList> // classe de manipulacao de lista do Qt
#include <QColor> // classe de manipulacao de cores do Qt
#include <QPointF> // classe de manipulcao de pontos flutuantes do Qt
#include <QGLWidget>
#include <GL/gl.h>
#include <iostream>
using namespace std;

#include "figura.hpp" // classe base das figuras

/**
 * clase que controla as figuras do tipo polilinha
 */
class Polilinha : public Figura
{
	
private:
	QList<QPointF> vertices; /**< lista de todos os vertices da polilinha */
	
public:
	
	/**
	 * costrutor da polinha, recebe o id, a cor de preenchimento e o primeiro ponto da polilinha
	 * @param id
	 * @param cor
	 * @param vertice_origem
	 */
	
	Polilinha(int,QColor,QPointF);
	
	/**
	 * destrutor da polilinha
	 */
	~Polilinha(void);
	
	/**
	 * move um vertice da polilinha da posicao de origem, para a posicao de destino
	 * @param origem
	 * @param destino
	 * @return true se o vertice existe
	 * @return false se o vertice nao existe
	 */
	bool moveV(QPointF,QPointF);
	bool moveV(int,QPointF);
	
	/**
	 * adiciona um vertice na polilinha
	 * @param novo_vertice 
	 * @return true se o vertice foi adicionado
	 * @return false caso o vertice ja esteja na polilinha
	 */
	bool adicionaV(QPointF);
	
	/**
	 * remove um vertice na polilinha
	 * @param vertice 
	 * @return true se o vertice foi removido
	 * @return false caso o vertice nao ja esteja na polilinha
	 */
	bool removeV(QPointF);
	
	bool removeV(int);
	
	/**
	 * desenha a polilinha
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	void Desenha(GLenum);
	
	/**
	 * desenha a polilinha selecionada
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


#endif /*POLILINHA_HPP_*/
