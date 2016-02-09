#ifndef CONTROLADOR_CONFIGURACION_EJERCICIO
#define CONTROLADOR_CONFIGURACION_EJERCICIO

#include <memory>

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/configuracion_ejercicio.h"
#include "../app/localizador.h"

namespace App
{

/* Descripciones de los varios tipos de items de listado de configuración... 
Necesitamos una clase base para poder meterlas en un vector de punteros. Por
lo demás podemos usar las cosas del generador de listados. La interface de 
listable realmente no vale para nada y sólo mete más ruido: el template
del generador de listados es quien realmente hace el trabajo.
*/

namespace Listado_config
{
struct interface_item_config:public Listable
{
	const DLibV::Fuente_TTF&	fuente;
	Configuracion_ejercicio&	config;
	const Localizador&		localizador;

					interface_item_config(const DLibV::Fuente_TTF& f, Configuracion_ejercicio& c, const Localizador& l): fuente(f), config(c), localizador(l) {}
	virtual void			al_salir() {}
	virtual void			al_pulsar(int, float) {}
	virtual void			al_down(int, float) {}
	virtual void			al_up() {}
	virtual void 			generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y)const=0;
};

}//Fin namespace listado config.

struct list_configuracion_ejercicio
{
	std::shared_ptr<Listado_config::interface_item_config>	iic;
	list_configuracion_ejercicio(Listado_config::interface_item_config * i): iic(i) {}
	void generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const {iic->generar_representacion_listado(rep, x, y);}
};

class Controlador_configuracion_ejercicio:
	public DFramework::Controlador_interface
{
	public:

					Controlador_configuracion_ejercicio(DLibH::Log_base&, const Fuentes&, const Localizador&, Configuracion_ejercicio& c);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	void					generar_menu();

	DLibH::Log_base&			log;
	const Fuentes&				fuentes;
	const Localizador&			localizador;
	Configuracion_ejercicio&		configuracion_ejercicio;

	//Propiedades...
	std::vector<list_configuracion_ejercicio>				list_config;
	Herramientas_proyecto::Listado_vertical<list_configuracion_ejercicio>	listado;
	DLibV::Representacion_agrupada		 				rep_listado;
	Herramientas_proyecto::Compositor_vista					vista;

	//Constantes...
	static const int 					x_listado=16,
								y_listado=32,
								alto_item_listado=20,
								ancho_listado=300,
								alto_listado=160,
								margen_y=16;
};

}

#endif
