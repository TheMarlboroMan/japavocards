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
	App::ciclar_modo(modo);
}

void App::ciclar_modo(Selector_etiquetas::modos& modo)
{
	switch(modo)
	{
		case Selector_etiquetas::modos::todas: 		modo=Selector_etiquetas::modos::sin_etiquetar; break;
		case Selector_etiquetas::modos::sin_etiquetar: 	modo=Selector_etiquetas::modos::etiquetadas; break;
		case Selector_etiquetas::modos::etiquetadas: 	modo=Selector_etiquetas::modos::sin_etiquetar; break;
	}
}

int App::localizar_modo(Selector_etiquetas::modos modo)
{
	switch(modo)
	{
		case Selector_etiquetas::modos::todas: 		return 1; break;
		case Selector_etiquetas::modos::sin_etiquetar: 	return 2; break;
		case Selector_etiquetas::modos::etiquetadas: 	return 3; break;
	}

	return 0;
}
