#include "polilinha.hpp"

Polilinha::Polilinha(int id, QColor cor, QPointF vertice_origem) : Figura(id,cor)
{
	this->vertices.append(vertice_origem);
	this->classe = polilinha;
}

Polilinha::~Polilinha(void)
{
	this->vertices.clear();
}

bool Polilinha::moveV(QPointF origem,QPointF destino)
{
	int posVertice;
	if((posVertice = this->vertices.indexOf(origem)) == -1 ) return false;
	this->vertices.replace(posVertice,destino);
	return true;
}

bool Polilinha::moveV(int posicao,QPointF destino) {
	if ( posicao >= 0 && posicao < this->vertices.size() ){
		this->vertices.replace(posicao,destino);
	}
}

bool Polilinha::adicionaV(QPointF novo_vertice) {
	if ( this->vertices.indexOf(novo_vertice) == -1  ){
		vertices << novo_vertice;
		return true;
		
	}
	return false;
}

bool Polilinha::removeV(QPointF vertice) {
	int pos;
	if ( (pos = this->vertices.indexOf(vertice) ) != -1  ){
		this -> vertices.removeAt(pos);
		return true;
	}
	return false;
}

void Polilinha::Desenha(GLenum mode)
{
	int i;
	glColor3f(this->cor.redF(),this->cor.greenF(),this->cor.blueF());
	//cout << "N vertices: " << this->vertices.size() << endl; 
	if (mode == GL_SELECT) glLoadName(this->getId());
	glBegin(GL_LINE_STRIP);
	{
		for(i = 0 ; i < this->vertices.size() ;i++)
		{
			glVertex2f(this->vertices.at(i).x(),this->vertices.at(i).y());
		}
		
	}
	glEnd();
}

void Polilinha::DesenhaSelecionado(GLenum mode) {
  int i;
  int lado = 4;
  float cor[] = {0.5f,0.5f,0.5f};
	
	this->Desenha(mode);
	glColor3fv(cor);
	for(i = 0 ; i < this->vertices.size() ;i++)
	{
		glRectf(this->vertices.at(i).x() - lado, this->vertices.at(i).y() - lado, this->vertices.at(i).x() + lado, this->vertices.at(i).y() + lado);
	}


}

QList<QPointF> Polilinha::getPontos() {
	return vertices;
}
