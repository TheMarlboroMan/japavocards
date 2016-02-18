#ifndef DIRECTOR_ESTADOS
#define DIRECTOR_ESTADOS

#include <memory>

#include <herramientas/log_base/log_base.h>

#include "../framework/director_estados_interface.h"
#include "../framework/eventos.h"

#include "../app/framework_impl/app_config.h"

#include "estados_controladores.h"
#include "menu.h"
#include "etiquetas.h"
#include "principal.h"
#include "configuracion_ejercicio.h"
#include "configuracion_aplicacion.h"

#include "../app/fuentes.h"
#include "../app/lector.h"
#include "../app/base_datos.h"
#include "../app/localizador.h"
#include "../app/filtro_palabras.h"
#include "../app/configuracion_ejercicio.h"
#include "../app/selector_etiquetas.h"

#include "../app/eventos/definiciones.h"
#include "../app/eventos/cambio_etiqueta.h"
#include "../app/eventos/cambio_direccion.h"
#include "../app/eventos/cambio_modo_etiqueta.h"
#include "../app/eventos/cambio_idioma_interface.h"
#include "../app/eventos/cambio_idioma_diccionario.h"
#include "../app/eventos/cambio_ventana.h"
#include "../app/eventos/cambio_palabras.h"
#include "../app/eventos/cambio_limitar_palabras.h"

/*
* El director de estados es la aplicación: los recursos externos al Kernel
* y los métodos propios que no son de los controladores.
*
* De forma experimental vamos a hacer que sea también el interprete de los
* eventos.
*/

namespace App
{

class Director_estados:
	public DFramework::Director_estados_interface,
	public DFramework::Interprete_eventos_interface
{
	public:

							Director_estados(DFramework::Kernel& kernel, App::App_config& config, DLibH::Log_base&);

	virtual void					preparar_cambio_estado(int deseado, int actual);
	virtual void					interpretar_evento(const DFramework::Evento_framework_interface&);

	private:

	void						preparar_video(DFramework::Kernel& kernel);
	void						cargar_fuentes();
	void						preparar_palabras();
	void						recargar_base_datos(const std::string&);
	void						registrar_controladores();

	//Eventos...
	void						interpretar_evento(const Eventos::Evento_cambio_etiqueta&);
	void						interpretar_evento(const Eventos::Evento_cambio_modo_etiqueta&);
	void						interpretar_evento(const Eventos::Evento_cambio_idioma_interface&);
	void						interpretar_evento(const Eventos::Evento_cambio_idioma_diccionario&);
	void						interpretar_evento(const Eventos::Evento_cambio_ventana&);
	void						interpretar_evento(const Eventos::Evento_cambio_direccion&);
	void						interpretar_evento(const Eventos::Evento_cambio_palabras&);
	void						interpretar_evento(const Eventos::Evento_cambio_limitar_palabras&);

	App::App_config					config;
	DLibH::Log_base&				log;

	std::unique_ptr<Controlador_menu>		controlador_menu;
	std::unique_ptr<Controlador_etiquetas>		controlador_etiquetas;
	std::unique_ptr<Controlador_principal>		controlador_principal;
	std::unique_ptr<Controlador_configuracion_ejercicio>		controlador_configuracion_ejercicio;
	std::unique_ptr<Controlador_configuracion_aplicacion>		controlador_configuracion_aplicacion;

	Localizador 					localizador;
	Base_datos					base_datos;
	Fuentes						fuentes;
	Configuracion_ejercicio				configuracion_ejercicio;
	Selector_etiquetas				selector_etiquetas;
};

}
#endif
