#ifndef CONTROLADOR_CONFIGURACION_EJERCICIO
#define CONTROLADOR_CONFIGURACION_EJERCICIO

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/configuracion_ejercicio.h"

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
struct interface_item_config
{
	const DLibV::Fuente_TTF&	fuente;
	Configuracion_ejercicion&	config;

					interface_item_config(const DLibV::Fuente_TTF&, Configuracion_ejercicio&);
	virtual void			al_salir()=0;
	virtual void			al_pulsar(int)=0;
	virtual void			al_down(int)=0;
};

struct item_config_direccion:
	public interface_item_config,
	public Listable
{
					item_config_direccion(const DLibV::Fuente_TTF&, Configuracion_ejercicio&);
	virtual void			al_salir();
	virtual void			al_pulsar(int);
	virtual void			al_down(int);
	virtual void 			generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;
};

struct item_config_modo_etiquetas:
	public interface_item_config,
	public Listable
{
					item_config_modo_etiquetas(const DLibV::Fuente_TTF&, Configuracion_ejercicio&);
	virtual void			al_salir();
	virtual void			al_pulsar(int);
	virtual void			al_down(int);
	virtual void 			generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;
};

struct item_config_numero_palabras:
	public interface_item_config,
	public Listable
{
					item_config_numero_palabras(const DLibV::Fuente_TTF&, Configuracion_ejercicio&);
	virtual void			al_salir();
	virtual void			al_pulsar(int);
	virtual void			al_down(int);
	virtual void 			generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;
};

struct item_config_limite_palabras:
	public interface_item_config,
	public Listable
{
					item_config_limite_palabras(const DLibV::Fuente_TTF&, Configuracion_ejercicio&);
	virtual void			al_salir();
	virtual void			al_pulsar(int);
	virtual void			al_down(int);
	virtual void 			generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;
};


}//Fin namespace listado config.

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
