#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include <memory>

#include <herramientas/log_base/log_base.h>

#include "../framework/director_estados_interface.h"

#include "../app/framework_impl/app_config.h"

#include "estados_controladores.h"
#include "menu.h"
#include "etiquetas.h"
#include "principal.h"
/*#include "controlador_grupos.h"
#include "controlador_menu.h"
#include "controlador_opciones.h"
*/

#include "../app/fuentes.h"
#include "../app/lector.h"
#include "../app/base_datos.h"
#include "../app/localizador.h"
#include "../app/filtro_palabras.h"
#include "../app/selector_etiquetas.h"
/*
#include "../app/eventos/interprete_eventos.h"
*/

/*
* El director de estados es la aplicación: los recursos externos al Kernel
* y los métodos propios que no son de los controladores.
*/

namespace App
{

class Director_estados:
	public DFramework::Director_estados_interface
{
	public:

							Director_estados(DFramework::Kernel& kernel, App::App_config& config, DLibH::Log_base&);

	virtual void					preparar_cambio_estado(int deseado, int actual);

	private:

	void						preparar_video(DFramework::Kernel& kernel, App::App_config& config);
	void						cargar_fuentes();
	void						preparar_palabras();
	void						recargar_base_datos(const std::string&);
	void						registrar_controladores(const App::App_config& config);

	DLibH::Log_base&				log;

	std::unique_ptr<Controlador_menu>		controlador_menu;
	std::unique_ptr<Controlador_etiquetas>		controlador_etiquetas;
	std::unique_ptr<Controlador_principal>		controlador_principal;

	Localizador 					localizador;
	Base_datos					base_datos;
	Fuentes						fuentes;

	Selector_etiquetas				selector_etiquetas;
};

}
#endif
