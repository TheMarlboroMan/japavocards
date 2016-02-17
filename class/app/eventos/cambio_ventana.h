#ifndef EVENTO_CAMBIO_VENTANA_H
#define EVENTO_CAMBIO_VENTANA_H

#include <string>

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_ventana:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_ventana;}
	std::string		medidas;
				Evento_cambio_ventana(const std::string& s):medidas(s) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
