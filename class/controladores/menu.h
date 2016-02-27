#ifndef ESTADO_MENU_H
#define ESTADO_MENU_H

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/fuentes.h"
#include "../app/definiciones.h"
#include "../app/transiciones.h"
#include "../app/worker_animacion.h"

namespace App
{

class Controlador_menu:
	public DFramework::Controlador_interface
{
	public:

					Controlador_menu(DLibH::Log_base&, const Fuentes&);

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
	DLibV::Camara				camara;
	Worker_animacion			worker_animacion;
	estados_transicion			estado_transicion;
	int					siguiente_estado;
};

}

#endif
