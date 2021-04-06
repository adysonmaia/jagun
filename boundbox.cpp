#include "boundbox.hpp"

BoundBox::BoundBox(int id, QColor cor , QPointF centro, QPointF pReferencia,FiguraBound* figura) 
: FiguraBound(id,cor,centro,pReferencia)
{
	this->setRaio(pReferencia);
	this->figuraBound = figura;
	this->boundBox = NULL;
}

BoundBox::~BoundBox()
{
	
}

void BoundBox::Escala(float fator)
{
	
}

void BoundBox::Desenha(GLenum mode)
{
	DesenhaSelecionado(mode);
}

void BoundBox::DesenhaSelecionado(GLenum mode)
{
	float cor[] = {0.5f,0.5f,0.5f};
	float lado = 5;
	
	glEnable(GL_LINE_STIPPLE);
	glPushAttrib(GL_LINE_STIPPLE);
	glColor3fv(cor);
		
	glLineStipple(1,0xF0F);
	glBegin(GL_LINE_LOOP);
		glVertex2f(centro.x() - raio, centro.y() +raio);
		glVertex2f(centro.x() + raio, centro.y() +raio);
		glVertex2f(centro.x() + raio, centro.y() -raio);
		glVertex2f(centro.x() - raio, centro.y() -raio);
	glEnd();
	glPopAttrib();
	glDisable(GL_LINE_STIPPLE);
	
	glRectf(centro.x() -lado, centro.y() - lado, centro.x() + lado, centro.y() + lado);
	glRectf(pReferencia.x() -lado, pReferencia.y() - lado, pReferencia.x() + lado, pReferencia.y() + lado);
}

QList<QPointF> BoundBox::getPontos() {
  QList<QPointF> pontos;
  pontos << this -> centro;
  pontos << this -> pReferencia;
  
  return pontos;
}



