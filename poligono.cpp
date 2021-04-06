#include "poligono.hpp"

Poligono::Poligono(int id, QColor cor, QPointF centro,QPointF pReferencia, int qtdlados) 
: FiguraBound(id,cor,centro,pReferencia)
{
	this->setRaio(pReferencia);
	this->lados = qtdlados;
	this->classe = poligono;
	this->boundBox = new BoundBox(id,cor,centro,pReferencia,this);
	//cout << "RAIO do poligono: " << this->raio << endl;
	
}

void Poligono::Desenha(GLenum mode)
{
	glColor3f(this->cor.redF(),this->cor.greenF(),this->cor.blueF());
	float angulo = 0;
	float variacao = 360/this->lados;
	float dX = (pReferencia.x() -centro.x() );
	float dY = (pReferencia.y() -centro.y() );
	int qtd = 0;
		
		
	if (mode == GL_SELECT) glLoadName(this->getId());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(centro.x(),centro.y(),0.0f);
		
	if ( dX != 0 ){
		angulo = atan( dY/ dX );
	 
	 	angulo = angulo*180/M_PI;
	  
	 	if (dX < 0 ){
	 		angulo += 180;
	 	}
	  
	}else {
		if (dY > 0 )
			angulo = 90;
		else
			angulo = 270;
	}
	  		
	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_LOOP);
	{
		while(qtd <= this->lados)
		{
			  
			float angRad = angulo*M_PI/180;
			  
			float x = (cos(angRad)*raio);
			float y = (sin(angRad)*raio);
			  
			glVertex2f(x,y);
			angulo += variacao;
			qtd++;
		}	
			
	}
	glEnd();
	glPopMatrix();
}

int Poligono::getLados() 
{
  return( this->lados );
}



