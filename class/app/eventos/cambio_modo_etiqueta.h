#ifndef EVENTO_CAMBIO_MODO_ETIQUETA_H
#define EVENTO_CAMBIO_MODO_ETIQUETA_H

#include "definiciones.h"
#include "../../framework/eventos.h"

namespace App
{

namespace Eventos
{

// No es necesario que lleve información de ningún tipo.

struct Evento_cambio_modo_etiqueta:
	public DFramework::Evento_framework_interface
{
	virtual int		tipo_evento() const {return cambio_modo_etiqueta;}
				Evento_cambio_modo_etiqueta(){}
};


} //Fin namespace eventos.
} //Fin namespace app.

#endif
