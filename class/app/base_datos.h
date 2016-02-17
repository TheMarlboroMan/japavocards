#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include <string>

#include <herramientas/log_base/log_base.h>

#include "extractor.h"
#include "lector.h"


namespace App
{

class Base_datos
{
	public:

					Base_datos(DLibH::Log_base&);
	void				cargar(const Lector&, const Idioma&);
	const std::vector<Idioma>&	acc_idiomas() const {return datos.idiomas;}
	const std::vector<Etiqueta>&	acc_etiquetas() const {return datos.etiquetas;}
	const std::vector<Palabra>&	acc_palabras() const {return datos.palabras;}

	private:

	DLibH::Log_base&		log;

	Almacenaje			datos;
};

}

#endif
