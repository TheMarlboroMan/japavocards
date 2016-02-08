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
#include "almacenaje.h"

namespace App
{

class Extractor
{
	public:

					Extractor(const Lector&, const Idioma&, DLibH::Log_base&);

	Almacenaje&&			extraer_almacenaje() {return std::move(almacenaje);}

	private:

	void				procesar_etiquetas();
	void				procesar_palabras();
	void				limpiar();

	const Lector&			lector;
	const Idioma&			idioma;
	DLibH::Log_base&		log;
	
	Almacenaje			almacenaje;
	std::map<std::string, Etiqueta *> mapa_etiquetas;
};

}

#endif
