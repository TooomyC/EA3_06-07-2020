/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ESTE ARCHIVO NO DEBE SER ENVIADO                           *//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

#include <iostream>

#include "Figura.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Triangulo.h"

using namespace std;

void funcionMostrar(Figura *p);

int main()
{
    cout << "Esperado: El area de la figura es: 9" << endl << "--------: ";
    Cuadrado *c = new Cuadrado(3);
    funcionMostrar(c);

    cout << endl << "Esperado: El area de la figura es: 20" << endl << "--------: ";
    Figura *r = new Rectangulo(4, 5);
    funcionMostrar(r);

    cout << endl << "Esperado: El area de la figura es: 6" << endl << "--------: ";
    Triangulo t(3, 4);
    funcionMostrar(&t);

    // La siguiente linea no deberìa compilar
    //Figura f();

    cout << endl << "Esperado: Excepcion: Figura invalida" << endl << "--------: ";
    try
    {
        Cuadrado malC(0);
        funcionMostrar(&malC);
        Triangulo *malT = new Triangulo (-1, -5);
        funcionMostrar(malT);
    }
    catch(FiguraInvalidaException &efi)
    {
        cout << "Excepcion: " << efi.what() << endl;
    }

    delete c;
    delete r;

    return 0;

    system("pause()");
}

void funcionMostrar(Figura *p)
{
    cout << "El area de la figura es: " << p->area() << endl;
}
