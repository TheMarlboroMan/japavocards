#include "selector_etiquetas.h"
#include <algorithm>

using namespace App;

void Selector_etiquetas::intercambiar(const Etiqueta& e)
{
	auto it=std::find(std::begin(etiquetas), std::end(etiquetas), &e);
	if(it==std::end(etiquetas))
	{
		etiquetas.push_back(&e);
		std::sort(std::begin(etiquetas), std::end(etiquetas));
	}
	else
	{
		etiquetas.erase(it);
	}
}

bool Selector_etiquetas::es_seleccionada(const Etiqueta& e)
{
	return std::find(std::begin(etiquetas), std::end(etiquetas), &e)!=std::end(etiquetas);
}
