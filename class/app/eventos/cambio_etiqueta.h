#ifndef EVENTO_CAMBIO_ETIQUETA_H
#define EVENTO_CAMBIO_ETIQUETA_H

#include <string>

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_etiqueta:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_etiqueta;}
	std::string		clave;
				Evento_cambio_etiqueta(const std::string& s):clave(s) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
