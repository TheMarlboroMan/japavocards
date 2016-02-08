#ifndef CONTROLADOR_CONFIGURACION_EJERCICIO
#define CONTROLADOR_CONFIGURACION_EJERCICIO

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/fuentes.h"
#include "../app/configuracion_ejercicio.h"

namespace App
{
class Controlador_configuracion_ejercicio:
	public DFramework::Controlador_interface
{
	public:

					Controlador_configuracion_ejercicio(DLibH::Log_base&, const Fuentes&, const Configuracion_ejercicio& c);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	DLibH::Log_base&			log;
	const Fuentes&				fuentes;

	Herramientas_proyecto::Compositor_vista	vista;
};

}

#endif
