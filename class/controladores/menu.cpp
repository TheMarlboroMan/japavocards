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
	:log(log), fuentes(f), estado_transicion(estados_transicion::entrada),
	siguiente_estado(-1)
{
	vista.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	vista.mapear_textura("cursores", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_CURSORES));
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

	worker_animacion.turno(delta);

	switch(estado_transicion)
	{
		case estados_transicion::entrada:
			if(worker_animacion.size()==1) 
			{
				estado_transicion=estados_transicion::activo;
			}			
		break;
		case estados_transicion::salida:
			if(worker_animacion.size()==1) 
			{
				solicitar_cambio_estado(siguiente_estado);
				worker_animacion.finalizar();
			}
		break;
		case estados_transicion::activo:
			if(input.es_input_down(App::Input::arriba)) 
			{
				siguiente_estado=principal;
				transicion_salida_vertical(worker_animacion, camara, -600.0);
			}
			else if(input.es_input_down(App::Input::abajo)) 
			{
				siguiente_estado=etiquetas;
				transicion_salida_vertical(worker_animacion, camara, 600.0);
			}
			else if(input.es_input_down(App::Input::izquierda)) 
			{
				siguiente_estado=config_ejercicio;
				transicion_salida_horizontal(worker_animacion, camara, -600.0);
			}
			else if(input.es_input_down(App::Input::derecha)) 
			{
				siguiente_estado=config_aplicacion;
				transicion_salida_horizontal(worker_animacion, camara, 600.0);
			}

			if(siguiente_estado!=-1) estado_transicion=estados_transicion::salida;
		break;
	}
}

void  Controlador_menu::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_menu::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla, camara);
}

void  Controlador_menu::despertar()
{
	log<<"Despertando controlador menú"<<std::endl;
	vista.parsear("data/layout/menu.dnot", "layout");

	try
	{
		//Configurar cámara...
		camara.enfocar_a(0, 0);
		camara.mut_pos_x(vista.const_int("x_camara"));
		camara.mut_pos_y(vista.const_int("y_camara"));
		camara.mut_w_pos(vista.const_int("w_camara"));
		camara.mut_h_pos(vista.const_int("h_camara"));
		camara.mut_enfoque(vista.const_int("w_camara"), vista.const_int("h_camara"));

		siguiente_estado=-1;
		estado_transicion=estados_transicion::entrada;
		transicion_entrada(vista, worker_animacion);
		animacion_crece(worker_animacion, *vista.obtener_por_id("cursores"), 1.1, 0.2);
	}
	catch(std::exception& e)
	{
		std::string err="Error al despertar controlador menú: ";
		err+=e.what();
		throw std::runtime_error(err);
	}
}

void  Controlador_menu::dormir()
{
	log<<"Durmiendo controlador menú"<<std::endl;
	vista.vaciar_vista();
	vista.vaciar_constantes();
}

bool Controlador_menu::es_posible_abandonar_estado() const
{
	return true;
}
