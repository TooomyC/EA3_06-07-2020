/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#include "Rectangulo.h"

Rectangulo::Rectangulo(double A_lado,double B_lado)
{
    if(A_lado <= 0 || B_lado <= 0)
        throw FiguraInvalidaException();

    this->A_lado = A_lado;
    this->B_lado = B_lado;
}


double Rectangulo::area() const
{
	return this->A_lado * this->B_lado;
}
