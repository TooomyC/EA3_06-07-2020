/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#include "Cuadrado.h"

Cuadrado::Cuadrado(double lado)
{
    if(lado <= 0)
        throw FiguraInvalidaException();

   this->lado = lado;
}

double Cuadrado::area() const
{
	return this->lado * this->lado;
}
