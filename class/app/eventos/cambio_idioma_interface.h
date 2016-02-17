#ifndef EVENTO_CAMBIO_IDIOMA_INTERFACE_H
#define EVENTO_CAMBIO_IDIOMA_INTERFACE_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_idioma_interface:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_idioma_interface;}
	int			idioma;
				Evento_cambio_idioma_interface(int i):idioma(i) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
