/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#ifndef FIGURA_H_
#define FIGURA_H_

#include "FiguraInvalidaException.h"

#include <string>

using namespace std;

class Figura
{
	public:
	    virtual ~Figura(); //Destructor

		virtual double area() const = 0;
};


#endif // FIGURA_H_
