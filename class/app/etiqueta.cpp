#include "etiqueta.h"

using namespace App;

Etiqueta::Etiqueta(const std::string& n, const std::string& c)
	:nombre(n), clave(c), palabras_asignadas(0)
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
