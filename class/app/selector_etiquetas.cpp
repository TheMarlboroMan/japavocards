#include "selector_etiquetas.h"
#include <algorithm>

using namespace App;

Selector_etiquetas::Selector_etiquetas()
	:modo(modos::todas)
{

}

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

void Selector_etiquetas::ciclar_modo()
{
	switch(modo)
	{
		case modos::todas: 		modo=modos::sin_etiquetar; break;
		case modos::sin_etiquetar: 	modo=modos::etiquetadas; break;
		case modos::etiquetadas: 	modo=modos::sin_etiquetar; break;
	}
}
