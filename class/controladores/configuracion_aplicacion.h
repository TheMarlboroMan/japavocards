#ifndef CONTROLADOR_CONFIGURACION_APLICACION
#define CONTROLADOR_CONFIGURACION_APLICACION

#include <memory>

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/localizador.h"

namespace App
{

class Controlador_configuracion_aplicacion:
	public DFramework::Controlador_interface
{
	public:

					Controlador_configuracion_aplicacion(DLibH::Log_base&, const Fuentes&, const Localizador&);

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
	const Localizador&			localizador;

	//Propiedades...
	Herramientas_proyecto::Compositor_vista					vista;
};

}

#endif
