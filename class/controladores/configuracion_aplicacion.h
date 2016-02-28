#ifndef CONTROLADOR_CONFIGURACION_APLICACION
#define CONTROLADOR_CONFIGURACION_APLICACION

#include <memory>

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>
#include <class/menu_opciones.h>

#include "../framework/controlador_interface.h"

#include "../app/framework_impl/app_config.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/idioma.h"
#include "../app/localizador.h"
#include "../app/definiciones.h"
#include "../app/worker_animacion.h"
#include "../app/transiciones.h"

namespace App
{

class Controlador_configuracion_aplicacion:
	public DFramework::Controlador_interface
{
	public:

					Controlador_configuracion_aplicacion(DLibH::Log_base&, const Fuentes&, const Localizador&, const std::vector<Idioma>&, const App_config&);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	struct item_config_app:public Listable
	{
		const Fuentes& 		fuentes;
		std::string 		clave, texto;
		virtual void 		generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;

		item_config_app(const Fuentes& f, const std::string& k, const std::string& t):
			fuentes(f), clave(k), texto(t)
		{}
	};

	void				input_activo(DFramework::Input& input, float delta);
	void				crear_menu_opciones(const App_config&);
	void				generar_vista_menu();
	void				menu_down(item_config_app&, int, float);
	void				traducir();

	//Referencias.
	DLibH::Log_base&					log;
	const Fuentes&						fuentes;
	const Localizador&					localizador;
	const std::vector<Idioma>&				idiomas;

	//Propiedades...
	DLibV::Camara						camara;
	Componente_menu<item_config_app, std::string>		componente_menu;
	Herramientas_proyecto::Compositor_vista			vista;
	estados_transicion					estado_transicion;
	Worker_animacion					worker_animacion;
};

}

#endif
