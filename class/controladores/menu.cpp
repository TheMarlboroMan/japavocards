#include "menu.h"
#include "estados_controladores.h"
#include "../app/recursos.h"

#include <video/gestores/gestor_texturas.h>

#include <string>

#include "../app/framework_impl/input.h"

/*
#ifdef WINCOMPIL
//Localización del parche mingw32... Esto debería estar en otro lado, supongo.
#include <herramientas/herramientas/herramientas.h>
#endif
*/

using namespace App;

Controlador_menu::Controlador_menu(DLibH::Log_base& log, const Fuentes& f)
	:log(log), fuentes(f)
{
	vista.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));
}

void  Controlador_menu::preloop(DFramework::Input& input, float delta)
{

}

void  Controlador_menu::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(App::Input::escape))
	{
		abandonar_aplicacion();
	}
	
	if(input.es_input_down(App::Input::arriba))
	{
		solicitar_cambio_estado(principal);
	}
	else if(input.es_input_down(App::Input::abajo))
	{
		solicitar_cambio_estado(etiquetas);
	}
	else if(input.es_input_down(App::Input::izquierda))
	{
		solicitar_cambio_estado(config_ejercicio);
	}
	else if(input.es_input_down(App::Input::derecha))
	{
		solicitar_cambio_estado(config_aplicacion);
	}
}

void  Controlador_menu::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_menu::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
}

void  Controlador_menu::despertar()
{
	log<<"Despertando controlador menú"<<std::endl;
	vista.parsear("data/layout/menu.dnot", "layout");
}

void  Controlador_menu::dormir()
{
	log<<"Durmiendo controlador menú"<<std::endl;
	vista.vaciar_vista();
}

bool Controlador_menu::es_posible_abandonar_estado() const
{
	return true;
}
