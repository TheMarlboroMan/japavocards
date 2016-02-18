#ifndef EVENTO_CAMBIO_LIMITAR_PALABRAS_H
#define EVENTO_CAMBIO_LIMITAR_PALABRAS_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_limitar_palabras:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_limitar_palabras;}
	bool			limitar;
				Evento_cambio_limitar_palabras(bool l):limitar(l) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
