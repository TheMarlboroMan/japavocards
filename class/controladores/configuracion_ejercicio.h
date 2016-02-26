#ifndef CONTROLADOR_CONFIGURACION_EJERCICIO
#define CONTROLADOR_CONFIGURACION_EJERCICIO

#include <memory>

#include <herramientas/log_base/log_base.h>

#include <class/menu_opciones.h>
#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/framework_impl/app_config.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/configuracion_ejercicio.h"
#include "../app/localizador.h"
#include "../app/definiciones.h"

namespace App
{

/* Descripciones de los varios tipos de items de listado de configuración... 
Necesitamos una clase base para poder meterlas en un vector de punteros. Por
lo demás podemos usar las cosas del generador de listados. La interface de 
listable realmente no vale para nada y sólo mete más ruido: el template
del generador de listados es quien realmente hace el trabajo.
*/

class Controlador_configuracion_ejercicio:
	public DFramework::Controlador_interface
{
	public:

					Controlador_configuracion_ejercicio(DLibH::Log_base&, const Fuentes&, const Localizador&, const Configuracion_ejercicio& c);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	struct item_config_ejercicio:public Listable
	{
		const Fuentes& 		fuentes;
		std::string 		clave, texto;
		virtual void 		generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;

		item_config_ejercicio(const Fuentes& f, const std::string& k, const std::string& t):
			fuentes(f), clave(k), texto(t)
		{}
	};

	void				crear_menu_opciones();
	void				generar_vista_menu();
	void				menu_down(item_config_ejercicio&, int, float, bool);

	DLibH::Log_base&			log;
	const Fuentes&				fuentes;
	const Localizador&			localizador;
	const Configuracion_ejercicio&		configuracion_ejercicio;

	//Propiedades...
	Componente_menu<item_config_ejercicio, std::string>			componente_menu;
	Herramientas_proyecto::Compositor_vista					vista;
	float									tiempo_menu;
};

}

#endif
