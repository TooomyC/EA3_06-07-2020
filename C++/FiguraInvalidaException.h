/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/

#ifndef FIGURAINVALIDAEXCEPTION_H_
#define FIGURAINVALIDAEXCEPTION_H_

#include "Figura.h"
#include <exception>

using namespace std;

class FiguraInvalidaException : public exception
{
    public:
        FiguraInvalidaException() : exception () {}

        const char *what () throw() { return "Figura invalida"; };
};

#endif // FIGURAINVALIDAEXCEPTION_H_
