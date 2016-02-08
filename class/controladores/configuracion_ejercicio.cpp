#include "configuracion_ejercicio.h"

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"

using namespace App;

Controlador_configuracion_ejercicio::Controlador_configuracion_ejercicio(DLibH::Log_base& l, const Fuentes& f, const Configuracion_ejercicio& c)
	:log(l), fuentes(f)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));
}

void Controlador_configuracion_ejercicio::preloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_ejercicio::loop(DFramework::Input& input, float delta)
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

void Controlador_configuracion_ejercicio::postloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_ejercicio::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
}

void Controlador_configuracion_ejercicio::despertar()
{
	log<<"Despertando controlador configuración ejercicio"<<std::endl;
	vista.parsear("data/layout/configuracion_ejercicio.dnot", "layout");
}

void Controlador_configuracion_ejercicio::dormir()
{
	log<<"Durmiendo controlador configuración ejercicio"<<std::endl;
	vista.vaciar_vista();
}

bool Controlador_configuracion_ejercicio::es_posible_abandonar_estado() const
{
	return true;
}
