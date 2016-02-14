#include "configuracion_ejercicio.h"

#include <functional>

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"
#include "../app/localizacion.h"

using namespace App;

Controlador_configuracion_ejercicio::Controlador_configuracion_ejercicio(DLibH::Log_base& l, const Fuentes& f, const Localizador& loc, Configuracion_ejercicio& c)
	:log(l), fuentes(f), localizador(loc), configuracion_ejercicio(c), listado(alto_listado, alto_item_listado), rep_listado(true),
	tiempo_menu(0.0f)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	rep_listado.no_imponer_alpha();

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
		listado.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1);
	}
	else if(hay_cambio(&DFramework::Input::es_input_down, dir))
	{
		menu_down(listado.item_actual(), dir, delta, false);
	}
	else if(hay_cambio(&DFramework::Input::es_input_pulsado, dir))
	{
		menu_down(listado.item_actual(), dir, delta, true);
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
	rep_listado.volcar(pantalla);

	//TODO: ¿Dónde está el selector actual? Lo podríamos pasar tb???
	//Podemos meter esto en otra función o algo así??. Si es posible,
	//podemos omitir parámetros del tipo ancho y alto_item???.

	//Selección actual...
	const int y=y_listado+(listado.linea_actual().y);
	DLibV::Representacion_primitiva_caja seleccion_actual({0, y, ancho_listado, alto_item_listado}, 255, 255, 255);
	seleccion_actual.establecer_alpha(128);
	seleccion_actual.volcar(pantalla);
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
	rep_listado.vaciar_grupo();
}

bool Controlador_configuracion_ejercicio::es_posible_abandonar_estado() const
{
	return true;
}

void Controlador_configuracion_ejercicio::generar_vista_menu()
{
	listado.clear();
	const auto& v=menu_opciones.obtener_claves();
	for(const auto& c : v) listado.insertar({fuentes, c, menu_opciones.nombre_opcion(c)+" : "+menu_opciones.nombre_seleccion(c)});
	generar_vista_listado(listado, rep_listado, x_listado, y_listado);
}

void Controlador_configuracion_ejercicio::crear_menu_opciones()
{
	using namespace Herramientas_proyecto;
	menu_opciones_desde_dnot("data/config/valores.dnot", "config_ejercicio", menu_opciones, menu_opciones_traducciones);

	using traduccion=Menu_opciones<std::string>::struct_traduccion;
	std::vector<traduccion> trad={};
	for(const auto& par : menu_opciones_traducciones) trad.push_back({par.first, localizador.obtener(par.second)});
	menu_opciones.traducir(trad);	
	
	//TODO: asignar valores según configuración de usuario.
}

void Controlador_configuracion_ejercicio::menu_down(item_config_ejercicio& item, int dir, float delta, bool pulsado)
{
	const std::string& clave=item.clave;

	if(clave=="01_K_DIRECCION")
	{
		if(pulsado) return;
		configuracion_ejercicio.ciclar_direccion();
		menu_opciones.asignar_por_valor_templated<std::string>(clave, direccion_a_string(configuracion_ejercicio.acc_direccion()));
	}
	else if(clave=="02_K_MODO_ETIQUETAS")
	{
		if(pulsado) return;
		configuracion_ejercicio.ciclar_modo_etiquetas();
		menu_opciones.asignar_por_valor_templated<std::string>(clave, modo_etiquetas_a_string(configuracion_ejercicio.acc_modo_etiquetas()));
	}
	else if(clave=="03_K_LIMITE_PALABRAS")
	{
		if(pulsado) return;
		configuracion_ejercicio.intercambiar_palabras_limitadas();
		menu_opciones.asignar_por_valor_templated<bool>(clave, configuracion_ejercicio.es_palabras_limitadas());
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

		menu_opciones.asignar_por_valor_int(clave, configuracion_ejercicio.acc_palabras());
	}

	item.texto=menu_opciones.nombre_opcion(clave)+" : "+menu_opciones.nombre_seleccion(clave);
	generar_vista_menu();
	generar_vista_listado(listado, rep_listado, x_listado, y_listado);
}

void Controlador_configuracion_ejercicio::item_config_ejercicio::generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
{
	auto * txt=new DLibV::Representacion_TTF(fuentes.obtener_fuente("akashi", 20), {255, 255, 255, 255}, texto);
	txt->establecer_posicion(x, y);
	rep.insertar_representacion(txt);
}
