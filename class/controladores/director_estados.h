#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include <memory>

#include <herramientas/log_base/log_base.h>

#include "../framework/director_estados_interface.h"

#include "../app/framework_impl/app_config.h"

#include "estados_controladores.h"
/*#include "controlador_grupos.h"
#include "controlador_menu.h"
#include "controlador_opciones.h"
#include "controlador_principal.h"
*/

#include "../app/lector.h"
#include "../app/base_datos.h"
#include "../app/localizador.h"
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

	void						recargar_base_datos(const std::string&);
	void						registrar_controladores(const App::App_config& config);

	DLibH::Log_base&				log;	

	Localizador 					localizador;
	Base_datos					base_datos;
};

}
#endif
