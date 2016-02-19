#include "etiquetas.h"

#include <string>

#include <video/representacion/representacion_primitiva/representacion_primitiva_caja/representacion_primitiva_caja.h>

#include "../app/framework_impl/input.h"
#include "../app/eventos/cambio_etiqueta.h"

#include "estados_controladores.h"


#ifdef WINCOMPIL
//Localización del parche mingw32... Esto debería estar en otro lado, supongo.
#include <herramientas/herramientas/herramientas.h>
#endif


using namespace App;

Controlador_etiquetas::Controlador_etiquetas(DLibH::Log_base& log, const Fuentes& f, const std::vector<Etiqueta>& ve, const std::vector<std::string>& etiquetas_seleccionadas)
	:log(log), fuentes(f), 
	componente_menu(x_listado, y_listado, alto_item_listado, alto_listado)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	//Preparar listado...
//TODO	listado.mut_margen_h(margen_y);
	crear_menu_opciones(ve, etiquetas_seleccionadas);
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
	else if(input.es_input_down(App::Input::abajo) || input.es_input_down(App::Input::arriba))
	{
		bool refrescar=componente_menu.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1);
		if(refrescar) generar_vista_menu();
	}
	//TODO: Añadir inputs de avanzar y repetir página para pasar más deprisa.
	else if(input.es_input_down(App::Input::izquierda) ||
		input.es_input_down(App::Input::derecha) ||
		input.es_input_down(App::Input::aceptar))
	{
		auto& item=componente_menu.item_actual();
		const auto& clave=item.clave;
		componente_menu.menu().rotar_opcion(clave, 1);

		//Refrescar vista de menú...
		//TODO: Función única para esto...
		std::string txt=componente_menu.menu().nombre_opcion(clave)+" : "+std::to_string(componente_menu.menu().valor_bool(clave));
		item.texto=txt;
		componente_menu.regenerar_listado();

		auto ev=DFramework::uptr_evento(new Eventos::Evento_cambio_etiqueta(clave));
		enviar_evento(ev);
	}
}

void  Controlador_etiquetas::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_etiquetas::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
	componente_menu.volcar(pantalla, ancho_listado, alto_item_listado);
}

void  Controlador_etiquetas::despertar()
{
	log<<"Despertando controlador etiquetas"<<std::endl;
	vista.parsear("data/layout/etiquetas.dnot", "layout");
	generar_vista_menu();
}

void  Controlador_etiquetas::dormir()
{
	log<<"Durmiendo controlador etiquetas"<<std::endl;
	vista.vaciar_vista();
	componente_menu.desmontar();
}

bool Controlador_etiquetas::es_posible_abandonar_estado() const
{
	return true;
}

void Controlador_etiquetas::crear_menu_opciones(const std::vector<Etiqueta>& ve, const std::vector<std::string>& etiquetas_seleccionadas)
{
	for(const auto& e : ve) 
	{
		bool marcar=std::find(std::begin(etiquetas_seleccionadas), std::end(etiquetas_seleccionadas), e.acc_clave())!=std::end(etiquetas_seleccionadas);
		componente_menu.menu().insertar_opcion_bool(e.acc_clave(), e.acc_nombre(), marcar);
	}

	//Una vez pasado este punto no hay más referencias a las etiquetas.
}

void Controlador_etiquetas::generar_vista_menu()
{
	auto f=[this](Herramientas_proyecto::Listado_vertical<item_config_etiqueta>& l, Herramientas_proyecto::Menu_opciones<std::string>& m, const std::vector<std::string>& v)
	{
		for(const auto& clave : v) 
		{
			//TODO: Función única para esto.
			std::string txt=componente_menu.menu().nombre_opcion(clave)+" : "+std::to_string(componente_menu.menu().valor_bool(clave));
			l.insertar({fuentes, clave, txt});
		}
	};
	
	componente_menu.montar(f);
}

//Un detalle muy importante es que el item_config_etiqueta no tiene acceso de
//ningún tipo al estado de la etiqueta. Todo el estado debe darse desde fuera.

void Controlador_etiquetas::item_config_etiqueta::generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
{
	auto * txt=new DLibV::Representacion_TTF(fuentes.obtener_fuente("akashi", 20), {255, 255, 255, 255}, texto);
	txt->establecer_posicion(x, y);
	rep.insertar_representacion(txt);
}
