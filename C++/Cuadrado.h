/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#ifndef CUADRADO_H_
#define CUADRADO_H_

#include "Figura.h"

class Cuadrado : public Figura
{
	private:
		double lado;

	public:
		Cuadrado(double lado);

		double area() const;
};


#endif // CUADRADO_H_
