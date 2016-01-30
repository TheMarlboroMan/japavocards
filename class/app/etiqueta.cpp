#include "etiqueta.h"

using namespace App;

Etiqueta::Etiqueta(const std::string& n)
	:nombre(n)
{

}

bool Etiqueta::operator<(const Etiqueta& o) const
{
	return nombre < o.nombre;
}

bool Etiqueta::operator==(const Etiqueta& o) const
{
	return nombre==o.nombre;
}
