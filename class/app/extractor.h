#ifndef EXTRACTOR_H
#define EXTRACTOR_H

/**
* El extractor saca toda la información de un lector en el idioma escogido.
* Esta información está lista para pasarla de un lado a otro. Básicamente
* pasa la información del formato "Crudo" al formato "Refinado".
*/

#include <vector>
#include <map>
#include <string>

#include <herramientas/log_base/log_base.h>

#include "datos_bruto.h"
#include "lector.h"
#include "etiqueta.h"
#include "palabra.h"

namespace App
{

class Extractor
{
	public:

					Extractor(const Lector&, const Idioma&, DLibH::Log_base&);

	std::vector<Etiqueta>&&		extraer_etiquetas() {return std::move(etiquetas);}
	std::vector<Palabra>&&		extraer_palabras() {return std::move(palabras);}

	private:

	void				procesar_etiquetas();
	void				procesar_palabras();
	void				limpiar();

	const Lector&			lector;
	const Idioma&			idioma;
	DLibH::Log_base&		log;
	std::vector<Etiqueta>		etiquetas;
	std::vector<Palabra>		palabras;
	std::map<std::string, Etiqueta *> mapa_etiquetas;
};

}

#endif
