#ifndef ALMACENAJE_H
#define ALMACENAJE_H

#include <vector>
#include "palabra.h"
#include "etiqueta.h"

/**
* Estructura que contiene un vector de palabras y otro de etiquetas.
*/

namespace App
{

struct Almacenaje
{
	public:

	std::vector<Etiqueta>			etiquetas;
	std::vector<Palabra>			palabras;
};

}

#endif
