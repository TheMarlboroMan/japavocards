#ifndef EVENTO_CAMBIO_MODO_ETIQUETA_H
#define EVENTO_CAMBIO_MODO_ETIQUETA_H

#include "definiciones.h"
#include "../../framework/eventos.h"
#include "../configuracion_ejercicio.h"

namespace App
{

namespace Eventos
{

struct Evento_cambio_modo_etiqueta:
	public DFramework::Evento_framework_interface
{
	Configuracion_ejercicio::modos_etiquetas	modo;
	virtual int		tipo_evento() const {return cambio_modo_etiqueta;}
				Evento_cambio_modo_etiqueta(Configuracion_ejercicio::modos_etiquetas m):modo(m){}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
