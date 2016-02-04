#ifndef EVENTO_CAMBIO_ETIQUETA_H
#define EVENTO_CAMBIO_ETIQUETA_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

class Etiqueta;

namespace Eventos
{

struct Evento_cambio_etiqueta:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_etiqueta;}
	const Etiqueta&		e;
				Evento_cambio_etiqueta(const Etiqueta& e):e(e) {}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
