#include "configuracion_ejercicio.h"

#include <functional>

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"
#include "../app/localizacion.h"

using namespace App;

Controlador_configuracion_ejercicio::Controlador_configuracion_ejercicio(DLibH::Log_base& l, const Fuentes& f, const Localizador& loc, Configuracion_ejercicio& c)
	:log(l), fuentes(f), localizador(loc), configuracion_ejercicio(c),
	componente_menu(x_listado, y_listado, alto_item_listado, alto_listado),
	tiempo_menu(0.0f)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	crear_menu_opciones();
}

void Controlador_configuracion_ejercicio::preloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_ejercicio::loop(DFramework::Input& input, float delta)
{
	//std::function<bool(DFramework::Input&, unsigned int)> up=&DFramework::Input::es_input_up;
	auto hay_cambio=[&input](std::function<bool(DFramework::Input&, unsigned int)> f, int& dir)
	{
		bool resultado=f(input, App::Input::izquierda) ||
		f(input, App::Input::derecha) ||
		f(input, App::Input::aceptar);
		if(resultado) dir=f(input, App::Input::izquierda) ? -1 : 1;
		return resultado;
	};

	int dir=0;

	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	else if(input.es_input_down(App::Input::escape))
	{
		solicitar_cambio_estado(menu);
	}
	else if(input.es_input_down(App::Input::abajo) || input.es_input_down(App::Input::arriba))
	{
		tiempo_menu=0.0f;
		componente_menu.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1);
	}
	else if(hay_cambio(&DFramework::Input::es_input_down, dir))
	{
		menu_down(componente_menu.item_actual(), dir, delta, false);
	}
	else if(hay_cambio(&DFramework::Input::es_input_pulsado, dir))
	{
		menu_down(componente_menu.item_actual(), dir, delta, true);
	}
	else if(hay_cambio(&DFramework::Input::es_input_up, dir))
	{
		tiempo_menu=0.0f;
	}
}

void Controlador_configuracion_ejercicio::postloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_ejercicio::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
	componente_menu.volcar(pantalla, ancho_listado, alto_item_listado);
}

void Controlador_configuracion_ejercicio::despertar()
{
	log<<"Despertando controlador configuración ejercicio"<<std::endl;
	vista.parsear("data/layout/configuracion_ejercicio.dnot", "layout");	
	generar_vista_menu();
}

void Controlador_configuracion_ejercicio::dormir()
{
	log<<"Durmiendo controlador configuración ejercicio"<<std::endl;
	vista.vaciar_vista();
	componente_menu.desmontar();
}

bool Controlador_configuracion_ejercicio::es_posible_abandonar_estado() const
{
	return true;
}

void Controlador_configuracion_ejercicio::generar_vista_menu()
{
	componente_menu.traducir_menu_opciones(localizador);

	auto f=[this](Herramientas_proyecto::Listado_vertical<item_config_ejercicio>& l, Herramientas_proyecto::Menu_opciones<std::string>& m, const std::vector<std::string>& v)
	{
		for(const auto& c : v) l.insertar({fuentes, c, m.nombre_opcion(c)+" : "+m.nombre_seleccion(c)});
	};
	
	componente_menu.montar(f);
}

void Controlador_configuracion_ejercicio::crear_menu_opciones()
{
	componente_menu.crear_menu_opciones("data/config/valores.dnot", "config_ejercicio", localizador);

	//TODO: asignar valores según configuración de usuario.
}

void Controlador_configuracion_ejercicio::menu_down(item_config_ejercicio& item, int dir, float delta, bool pulsado)
{
	const std::string& clave=item.clave;

	if(clave=="01_K_DIRECCION")
	{
		if(pulsado) return;
		configuracion_ejercicio.ciclar_direccion();
		componente_menu.menu().asignar_por_valor_templated<std::string>(clave, direccion_a_string(configuracion_ejercicio.acc_direccion()));
	}
	else if(clave=="02_K_MODO_ETIQUETAS")
	{
		if(pulsado) return;
		configuracion_ejercicio.ciclar_modo_etiquetas();
		componente_menu.menu().asignar_por_valor_templated<std::string>(clave, modo_etiquetas_a_string(configuracion_ejercicio.acc_modo_etiquetas()));
	}
	else if(clave=="03_K_LIMITE_PALABRAS")
	{
		if(pulsado) return;
		configuracion_ejercicio.intercambiar_palabras_limitadas();
		componente_menu.menu().asignar_por_valor_templated<bool>(clave, configuracion_ejercicio.es_palabras_limitadas());
	}
	else if(clave=="04_K_NUMERO_PALABRAS")
	{
		if(pulsado && tiempo_menu < 0.5f)
		{
			tiempo_menu+=delta;
			return;
		}
		
		if(dir > 0) configuracion_ejercicio.sumar_palabras();
		else configuracion_ejercicio.restar_palabras();

		componente_menu.menu().asignar_por_valor_int(clave, configuracion_ejercicio.acc_palabras());
	}

	item.texto=componente_menu.menu().nombre_opcion(clave)+" : "+componente_menu.menu().nombre_seleccion(clave);
	generar_vista_menu();
	componente_menu.regenerar_listado();
}

void Controlador_configuracion_ejercicio::item_config_ejercicio::generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
{
	auto * txt=new DLibV::Representacion_TTF(fuentes.obtener_fuente("akashi", 20), {255, 255, 255, 255}, texto);
	txt->establecer_posicion(x, y);
	rep.insertar_representacion(txt);
}
