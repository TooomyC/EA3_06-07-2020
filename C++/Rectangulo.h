/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include "Figura.h"

class Rectangulo : public Figura
{
	private:
		double A_lado, B_lado;

	public:
		Rectangulo(double A_lado, double B_lado);
		double area() const;
};

#endif // RECTANGULO_H_
