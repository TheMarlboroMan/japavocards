#ifndef EVENTO_CAMBIO_DIRECCION_H
#define EVENTO_CAMBIO_DIRECCION_H

#include "definiciones.h"
#include "../../framework/eventos.h"
#include "../configuracion_ejercicio.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_direccion:
	public DFramework::Evento_framework_interface
{
	Configuracion_ejercicio::direcciones	direccion;
	virtual int		tipo_evento() const {return cambio_direccion;}
				Evento_cambio_direccion(Configuracion_ejercicio::direcciones d):direccion(d){}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
