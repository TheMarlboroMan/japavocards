#include "idioma.h"

using namespace App;

bool Idioma::operator<(const Idioma& o) const
{
	return acronimo < o.acronimo;
}
