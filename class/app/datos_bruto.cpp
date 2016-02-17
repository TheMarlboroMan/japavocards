#include "datos_bruto.h"

using namespace App;

bool Etiqueta_bruto::operator<(const Etiqueta_bruto& o) const
{
	return clave < o.clave;
}

bool Etiqueta_bruto::operator==(const Etiqueta_bruto& o) const
{
	return clave==o.clave;
}

bool Palabra_bruto::operator<(const Palabra_bruto& o) const
{
	return romaji < o.romaji;
}
