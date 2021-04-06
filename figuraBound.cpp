#include "figuraBound.hpp"

FiguraBound::FiguraBound(int id,QColor cor,QPointF centro,QPointF pReferencia) 
: Figura(id,cor)
{
	this->centro = centro;
	this->raio = 0;
	this->centro = centro;
	this->pReferencia = pReferencia;
}

void FiguraBound::MoveC(QPointF destino)
{
	QPointF centroantigo = this->centro;
	this->centro = destino;
	this->setRaio(pReferencia+(destino-centroantigo));
	
}

void FiguraBound::setRaio(QPointF pRef)
{
	
	this->pReferencia = pRef;
	
	float dX = (pRef.x() - this->centro.x());
	float dY = (pRef.y() - this->centro.y());
	float d = dX*dX + dY*dY;
	
	this -> raio =  sqrtf(d); 
	if (this -> raio == 0.0f){
		this->pReferencia = centro + QPointF(100.0f,0.0f);
		this->raio = 10.0f;
	}
  
	
}

bool FiguraBound::moveV(QPointF origem,QPointF destino) {
	
	if ( centro == origem ){
		this->MoveC(destino);
		return true;
	}else if( pReferencia == origem ){
		this->setRaio(destino);
		return true;
	}else{
		return false;
	}

}

bool FiguraBound::moveV(int posicao,QPointF destino) {
	switch(posicao){
		case 0:
			this -> MoveC(destino);
			return true;
			break;
		case 1:
		  this->setRaio(destino);
			return true;
			break;
		
		default :
			return false;
	}

}

void FiguraBound::DesenhaSelecionado(GLenum mode)
{
	this->Desenha(mode);
	if (this -> boundBox  != NULL){
		this->boundBox -> MoveC(this -> centro);
		this->boundBox -> setRaio(this->pReferencia);
		this->boundBox -> Desenha(mode);
	}
}

QList<QPointF> FiguraBound::getPontos() {
  QList<QPointF> pontos;
  pontos << this -> centro;
  pontos << this -> pReferencia;
  
  return pontos;
}
