#include "etiquetas.h"
#include "estados_controladores.h"

#include <string>

#include "../app/framework_impl/input.h"

/*
#ifdef WINCOMPIL
//Localización del parche mingw32... Esto debería estar en otro lado, supongo.
#include <herramientas/herramientas/herramientas.h>
#endif
*/

using namespace App;

Controlador_etiquetas::Controlador_etiquetas(DLibH::Log_base& log, const Fuentes& f)
	:log(log), fuentes(f)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));
}

void  Controlador_etiquetas::preloop(DFramework::Input& input, float delta)
{

}

void  Controlador_etiquetas::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	
	if(input.es_input_down(App::Input::escape))
	{
		solicitar_cambio_estado(menu);
	}
}

void  Controlador_etiquetas::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_etiquetas::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
}

void  Controlador_etiquetas::despertar()
{
	log<<"Despertando controlador etiquetas"<<std::endl;
	vista.parsear("data/layout/etiquetas.dnot", "layout");
}

void  Controlador_etiquetas::dormir()
{
	log<<"Durmiendo controlador etiquetas"<<std::endl;
	vista.vaciar_vista();
}

bool Controlador_etiquetas::es_posible_abandonar_estado() const
{
	return true;
}
