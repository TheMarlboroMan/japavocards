#include "configuracion_aplicacion.h"

#include <functional>

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"
#include "../app/localizacion.h"

using namespace App;

Controlador_configuracion_aplicacion::Controlador_configuracion_aplicacion(DLibH::Log_base& l, const Fuentes& f, const Localizador& loc)
	:log(l), fuentes(f), localizador(loc)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));
}

void Controlador_configuracion_aplicacion::preloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_aplicacion::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	else if(input.es_input_down(App::Input::escape))
	{
		solicitar_cambio_estado(menu);
	}
}

void Controlador_configuracion_aplicacion::postloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_aplicacion::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
}

void Controlador_configuracion_aplicacion::despertar()
{
	log<<"Despertando controlador configuración aplicación"<<std::endl;
	vista.parsear("data/layout/configuracion_aplicacion.dnot", "layout");
}

void Controlador_configuracion_aplicacion::dormir()
{
	log<<"Durmiendo controlador configuración aplicacion"<<std::endl;
	vista.vaciar_vista();
}

bool Controlador_configuracion_aplicacion::es_posible_abandonar_estado() const
{
	return true;
}
