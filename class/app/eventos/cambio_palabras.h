#ifndef EVENTO_CAMBIO_PALABRAS_H
#define EVENTO_CAMBIO_PALABRAS_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_palabras:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_palabras;}
	int			palabras;
				Evento_cambio_palabras(int i):palabras(i) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
