#include "menu.h"
#include "estados_controladores.h"
#include "../app/recursos.h"
#include "../app/localizacion.h"

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

Controlador_menu::Controlador_menu(DLibH::Log_base& log, const Fuentes& f, const Localizador& l)
	:log(log), fuentes(f), localizador(l), 
	estado_transicion(estados_transicion::entrada),
	siguiente_estado(-1), centrar(true)
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
	if(centrar)
	{
		try
		{
			auto fcentrar=[](DLibV::Representacion_TTF * txt, int x, int w, int flags)
			{
				int fac=txt->acc_posicion().w;
				int px=x+(w /2)-(fac/2);
				txt->establecer_posicion(px, px, 0, 0, flags);
			};

			std::map<std::string, DLibV::Representacion_TTF *> map={
				{"txt_iniciar", nullptr}, {"txt_etiquetas", nullptr}, 
				{"txt_config_ejercicio", nullptr}, {"txt_config_app", nullptr}};

			for(auto& p : map) 
			{
				p.second=static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id(p.first));
				p.second->preparar(pantalla.acc_renderer());
			}

			auto caja_centrar=vista.obtener_por_id("centrar_txt");

			int 	xh=caja_centrar->acc_posicion().x, 
				wh=caja_centrar->acc_posicion().w,
				xv=caja_centrar->acc_posicion().y,
				wv=caja_centrar->acc_posicion().h;    

			fcentrar(map["txt_iniciar"], xh, wh, DLibV::Representacion::FRECT_X);
			fcentrar(map["txt_etiquetas"], xh, wh, DLibV::Representacion::FRECT_X);
			fcentrar(map["txt_config_ejercicio"], xv, wv, DLibV::Representacion::FRECT_Y);
			fcentrar(map["txt_config_app"], xv, wv, DLibV::Representacion::FRECT_Y);

			centrar=false;
		}
		catch(std::exception& e)
		{
			std::string err="Error al despertar controlador menú: ";
			err+=e.what();
			throw std::runtime_error(err);
		}
	}

	vista.volcar(pantalla, camara);
}

void  Controlador_menu::despertar()
{
	try
	{
		log<<"Despertando controlador menú"<<std::endl;
		vista.parsear("data/layout/menu.dnot", "layout");

		//Configurar cámara...
		camara.enfocar_a(0, 0);
		camara.mut_pos_x(vista.const_int("x_camara"));
		camara.mut_pos_y(vista.const_int("y_camara"));
		camara.mut_w_pos(vista.const_int("w_camara"));
		camara.mut_h_pos(vista.const_int("h_camara"));
		camara.mut_enfoque(vista.const_int("w_camara"), vista.const_int("h_camara"));

		std::map<std::string, std::string> trad={ 
			{"txt_iniciar", localizador.obtener(localizacion::menu_iniciar)},
			{"txt_etiquetas", localizador.obtener(localizacion::menu_etiquetas)},
			{"txt_config_ejercicio", localizador.obtener(localizacion::menu_ejercicio)},
			{"txt_config_app", localizador.obtener(localizacion::menu_aplicacion)}};

		for(const auto& p:trad) 
			static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id(p.first))->asignar(p.second);

		siguiente_estado=-1;
		estado_transicion=estados_transicion::entrada;
		centrar=true;
		transicion_entrada(vista, worker_animacion);
		animacion_crece(worker_animacion, 
			*vista.obtener_por_id("cursores"), 
			vista.const_float("factor_cursores"), 
			vista.const_float("tiempo_cursores"));
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
