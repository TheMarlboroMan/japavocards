#include "extractor.h"
#include <algorithm>

using namespace App;

Extractor::Extractor(const Lector& l, const Idioma& i, DLibH::Log_base& log)
	:lector(l), idioma(i), log(log)
{

	log<<"Iniciando extracción para idioma "<<idioma.acronimo<<std::endl;
	procesar_etiquetas();
	procesar_palabras();
	limpiar();
}

/*
* Las etiquetas con traducciones al idioma actual se guardan en el vector
* de etiquetas y se referencian en un mapa por la clave original. El mapa
* de referencias se usará a la hora de crear las palabras.
*/

void Extractor::procesar_etiquetas()
{
	const auto& v=lector.acc_etiquetas();
	for(const auto& e : v)
	{
		const std::string& acr=idioma.acronimo;

		if(e->nombres.count(acr))
		{
			etiquetas.push_back(Etiqueta(e->nombres.at(acr)));
			mapa_etiquetas[acr]=&etiquetas.back();
		}
	}

	log<<"Extraidas "<<etiquetas.size()<<" etiquetas con traducción idioma"<<std::endl;
}

void Extractor::procesar_palabras()
{
	const auto& v=lector.acc_palabras();
	for(const auto& p : v)
	{
		if(p->traducciones.count(idioma.acronimo))
		{
			Palabra nueva(p->japones, p->romaji, p->traducciones.at(idioma.acronimo));
			for(const auto& e : p->etiquetas)
			{
				if(mapa_etiquetas.count(e->clave))
				{
					auto& et=mapa_etiquetas[e->clave];
					et->sumar_asignacion();
					nueva.insertar_etiqueta(*et);
				}
			}
			palabras.push_back(nueva);
		}
	}

	log<<"Extraidas "<<palabras.size()<<" palabras con traducción a idioma"<<std::endl;
}

/*
* Eliminar etiquetas sin palabras. Ordena los resultados
*/

void Extractor::limpiar()
{
	size_t actual=etiquetas.size();
	auto it=std::remove_if(
		std::begin(etiquetas), 
		std::end(etiquetas), 
		[](Etiqueta& e) {return !e.acc_asignaciones();});
	
	etiquetas.erase(it, std::end(etiquetas));

	size_t limpia=etiquetas.size();
	if(actual!=limpia)
	{
		log<<"Se eliminan "<<(actual-limpia)<<" etiquetas sin asignar"<<std::endl;
	}

	std::sort(std::begin(etiquetas), std::end(etiquetas));
	std::sort(std::begin(palabras), std::end(palabras));
}
