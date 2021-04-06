#ifndef FIGURA_HPP_
#define FIGURA_HPP_

class Figura;

#include <QtOpenGL>
#include <QColor> // classe de cor do Qt
/**
 * Define os tipos de figuras
 */
enum
{
  semfigura = -1,
  polilinha,
  arco,
  poligono,

};

/**
 * Classe Base de todas as figuras
 */
class Figura
{
private:
	
	int id; /**< id que identifica unicamente uma figura */
	
protected:
	int classe; /**< classe da figura */
	QColor cor; /**< cor de preenchimento da figura */
	
	
	
public:
	
	/**
	 * construtor da figura, recebe o id e a cor de preenchimento
	 * @param id
	 * @param cor
	 */
	Figura(int,QColor);
	
	/**
	 * destrutor da figura
	 */
	~Figura() {};
	
	/**
     * muda a cor da figura
	 * @param cor
	 * @return void
	 */
	void setCor(QColor cor);
	
	/**
	 * desenha a figura na tela
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	virtual void Desenha(GLenum) = 0;
	
	/**
	 * desenha a figura quando esta selecionada na tela
	 * @param mode modo da pintura GL_SELECT ou GL_RENDER
	 * @return void
	 */
	virtual void DesenhaSelecionado(GLenum) = 0;
	
	/**
	 * retorna o id da figura
	 * @return int
	 */
	int getId(void);
	
	/**
	 * retorna a cor da poliline
	 * @return QColor
	 */
	QColor getCor();
	
	/**
	 * retorna a classe da figura (polilinha, quadrado, etc ...)
	 */
	int getClasse();
	
	/**
	 * Pega todos pontos de referencia da figura
	 * @return lista de todos os pontos de referencia
	 */
	virtual QList<QPointF> getPontos() = 0;
	
	/**
	 * move um ponto de referencia da posicao de origem, para a posicao de destino
	 * @param origem
	 * @param destino
	 * @return true se o vertice existe
	 * @return false se o vertice nao existe
	 */
	virtual bool moveV(QPointF,QPointF) = 0;
	
	virtual bool moveV(int,QPointF) = 0;
	
	
	
    bool operator== ( const Figura & outra ) const; 
	
};

#endif /*FIGURA_HPP_*/
