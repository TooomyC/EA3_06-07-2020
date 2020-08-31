/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#include "Triangulo.h"

Triangulo::Triangulo(double base, double altura)
{
    if(base <= 0 || altura <= 0)
        throw FiguraInvalidaException();

    this->base = base;
    this->altura = altura;
}


double Triangulo::area() const
{
	return (this->base * this->altura) / 2;
}
