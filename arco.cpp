#include "arco.hpp"

Arco::Arco(int id, QColor cor, QPointF centro,QPointF pReferencia, float angulo) 
: FiguraBound(id,cor,centro,pReferencia)
{
	this->classe = arco;
	this->setRaio(pReferencia);
		this->angulo = angulo;
		this->boundBox = new BoundBox(id,cor,centro,pReferencia,this);
	
}

void Arco::Desenha(GLenum mode)
{
	glColor3f(this->cor.redF(),this->cor.greenF(),this->cor.blueF());
	float anguloIt = 0;
	//float variacao = 360/36;
	float variacao = 1;
	
	float dX = (pReferencia.x() -centro.x() );
	float dY = (pReferencia.y() -centro.y() );
	
	if (mode == GL_SELECT) glLoadName(this->getId());
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(centro.x(),centro.y(),0.0f);
	
	if ( dX != 0 ){
		anguloIt = atan( dY/ dX );
	 
	 	anguloIt = anguloIt*180/M_PI;
	  if (dX < 0 )
	 		anguloIt += 180;
	  
	} else {
		if (dY > 0 )
			anguloIt = 90;
		else
			anguloIt = 270;
	}
	
	/*if (dX <= 0 ){
		if (dY > 0)
			anguloIt -= 180;
		else
			anguloIt += 180;
	}*/
	
	float qtd = 0;
	
	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_STRIP);
	  
	  while(qtd <= this->angulo)
	  {
		  float angRad = anguloIt*M_PI/180;
		  float x = (cos(angRad)*raio);
			float y = (sin(angRad)*raio);
			  
			glVertex2f(x,y);
			anguloIt += variacao;
			qtd += variacao;
			
	  }
		glVertex2f(0.0,0.0);
	
	glEnd();
	glPopMatrix();

}

float Arco::getAngulo() 
{
  return( this->angulo );
}


