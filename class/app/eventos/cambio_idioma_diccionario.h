#ifndef EVENTO_CAMBIO_IDIOMA_DICCIONARIO_H
#define EVENTO_CAMBIO_IDIOMA_DICCIONARIO_H

#include <string>

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_idioma_diccionario:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_idioma_diccionario;}
	std::string		acronimo;
				Evento_cambio_idioma_diccionario(const std::string& s):acronimo(s) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
