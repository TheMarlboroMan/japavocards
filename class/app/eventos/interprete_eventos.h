#ifndef INTERPRETE_EVENTOS_H
#define INTERPRETE_EVENTOS_H

#include "definiciones.h"

#include "../../framework/eventos.h"

#include "cambio_etiqueta.h"

namespace App
{
namespace Eventos
{

class Interprete_eventos:
	public DFramework::Interprete_eventos_interface
{
	public:

	virtual void		interpretar_evento(const DFramework::Evento_framework_interface&);

	private:

	void			interpretar_evento(const Evento_cambio_etiqueta&);
};


}//Fin namespace eventos.
}//Fin namespace app

#endif
