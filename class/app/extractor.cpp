#include "extractor.h"
#include <algorithm>

#include <iostream>

using namespace App;

Extractor::Extractor(const Lector& l, const Idioma& i, DLibH::Log_base& log)
	:lector(l), idioma(i), log(log)
{

	log<<"Iniciando extracción para idioma "<<idioma.acronimo<<std::endl;
	procesar_idiomas();
	procesar_etiquetas();
	procesar_palabras();
	limpiar();
}

void Extractor::procesar_idiomas()
{
	const auto& v=lector.acc_idiomas();
	for(const auto&i : v)
		almacenaje.idiomas.push_back(Idioma{i->acronimo, i->nombre});
}

/*
* Las etiquetas con traducciones al idioma actual se guardan en el vector
* de etiquetas y se referencian en un mapa por la clave original. El mapa
* de referencias se usará a la hora de crear las palabras.
*
* El orden de operaciones es deliberado: primero llenar el vector, luego 
* ordenarlo y luego, cuando estén en sus posiciones finales se genera
* el mapa de referencias a los índices. Si lo hacemos en cualquier otro orden
* fallará a la hora de asignar etiquetas a palabras.
*/

void Extractor::procesar_etiquetas()
{
	const auto& v=lector.acc_etiquetas();
	for(const auto& e : v)
	{
		const std::string& acr=idioma.acronimo;

		if(e->nombres.count(acr))
		{
			almacenaje.etiquetas.push_back(Etiqueta(e->nombres.at(acr), e->clave));
		}
	}

	std::sort(std::begin(almacenaje.etiquetas), std::end(almacenaje.etiquetas));

	for(auto& e : almacenaje.etiquetas) mapa_etiquetas[e.acc_clave()]=&e;

	log<<"Extraidas "<<almacenaje.etiquetas.size()<<" etiquetas con traducción idioma"<<std::endl;
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
					auto& et=*mapa_etiquetas[e->clave];
					et.sumar_asignacion();
					nueva.insertar_etiqueta(et);
				}
			}
			almacenaje.palabras.push_back(nueva);
		}
	}

	log<<"Extraidas "<<almacenaje.palabras.size()<<" palabras con traducción a idioma"<<std::endl;
}

/*
* Eliminar etiquetas sin palabras. Ordena los resultados
*/

void Extractor::limpiar()
{
	size_t actual=almacenaje.etiquetas.size();
	auto it=std::remove_if(	
		std::begin(almacenaje.etiquetas), 
		std::end(almacenaje.etiquetas), 
		[](Etiqueta& e) {return !e.acc_asignaciones();});

	almacenaje.etiquetas.erase(it, std::end(almacenaje.etiquetas));

	size_t limpia=almacenaje.etiquetas.size();
	if(actual!=limpia)
	{
		log<<"Se eliminan "<<(actual-limpia)<<" etiquetas sin asignar"<<std::endl;
	}

	std::sort(std::begin(almacenaje.palabras), std::end(almacenaje.palabras));
}
