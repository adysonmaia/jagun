#include "figura.hpp"

Figura::Figura(int id,QColor cor)
{
	this->id = id;
	this->cor = cor;
	this->classe = semfigura;
}

int Figura::getId()
{
	return this->id;
}

void Figura::setCor(QColor cor)
{
	this->cor = cor;
}

QColor Figura::getCor()
{
	return this->cor;

}

int Figura::getClasse()
{
	return this->classe;
}

bool Figura::operator== ( const Figura & outra ) const
{
  if(this->id == outra.id) return true;
  else false;  
}
