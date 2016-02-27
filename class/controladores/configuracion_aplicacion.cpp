#include "configuracion_aplicacion.h"

#include <functional>

#include <video/gestores/gestor_texturas.h>

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"
#include "../app/localizacion.h"
#include "../app/eventos/cambio_idioma_interface.h"
#include "../app/eventos/cambio_idioma_diccionario.h"
#include "../app/eventos/cambio_ventana.h"
#include "../app/recursos.h"

#ifdef WINCOMPIL
/* Localización del parche mingw32... Esto debería estar en otro lado, supongo. */
#include <herramientas/herramientas/herramientas.h>
#endif

using namespace App;

Controlador_configuracion_aplicacion::Controlador_configuracion_aplicacion(DLibH::Log_base& l, const Fuentes& f, const Localizador& loc, const std::vector<Idioma>& i, const App_config& config)
	:log(l), fuentes(f), localizador(loc), idiomas(i),
	camara(),
	componente_menu(),
	estado_transicion(estados_transicion::activo)
{
	vista.mapear_textura("background", DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND));
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	crear_menu_opciones(config);
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
	else
	{
		switch(estado_transicion)
		{
			case estados_transicion::activo:
				input_activo(input, delta);
			break;
			case estados_transicion::entrada:
				if(worker_animacion.es_activo()) worker_animacion.turno(delta);
				else estado_transicion=estados_transicion::activo;
			break;
			case estados_transicion::salida:
				if(worker_animacion.es_activo()) worker_animacion.turno(delta);
				else solicitar_cambio_estado(menu);
			break;
		}
	}
}

void Controlador_configuracion_aplicacion::input_activo(DFramework::Input& input, float delta)
{
	auto hay_cambio=[&input](std::function<bool(DFramework::Input&, unsigned int)> f, int& dir)
	{
		bool resultado=f(input, App::Input::izquierda) ||
		f(input, App::Input::derecha) ||
		f(input, App::Input::aceptar);
		if(resultado) dir=f(input, App::Input::izquierda) ? -1 : 1;
		return resultado;
	};

	int dir=0;

	if(input.es_input_down(App::Input::escape))
	{
		estado_transicion=estados_transicion::salida;
		transicion_salida_horizontal(worker_animacion, camara, -600.f);
	}
	else if(input.es_input_down(App::Input::abajo) || input.es_input_down(App::Input::arriba))
	{
		componente_menu.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1);
	}
	else if(hay_cambio(&DFramework::Input::es_input_down, dir))
	{
		menu_down(componente_menu.item_actual(), dir, delta);
	}
}

void Controlador_configuracion_aplicacion::postloop(DFramework::Input& input, float delta)
{

}

void Controlador_configuracion_aplicacion::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla, camara);
}

void Controlador_configuracion_aplicacion::despertar()
{
	//TODO: try...
	log<<"Despertando controlador configuración aplicación"<<std::endl;
	vista.registrar_externa("listado", componente_menu.rep());
	vista.registrar_externa("selector", componente_menu.rep_selector());
	vista.parsear("data/layout/configuracion_aplicacion.dnot", "layout");

	configurar_camara_y_menu(vista, camara, componente_menu);
	generar_vista_menu();
	estado_transicion=estados_transicion::entrada;
	transicion_entrada(vista, worker_animacion);
}

void Controlador_configuracion_aplicacion::dormir()
{
	log<<"Durmiendo controlador configuración aplicacion"<<std::endl;
	vista.vaciar_vista();
	vista.vaciar_constantes();
	componente_menu.desmontar();
}

bool Controlador_configuracion_aplicacion::es_posible_abandonar_estado() const
{
	return true;
}

/////////////////////////////

void Controlador_configuracion_aplicacion::crear_menu_opciones(const App_config& config)
{
	componente_menu.crear_menu_opciones("data/config/valores.dnot", "config_app", localizador);

	for(const auto& i : idiomas)
		componente_menu.menu().insertar_seleccion_templated<std::string>("03_K_IDIOMA_DICCIONARIO", i.acronimo, i.nombre, i.acronimo);

#ifdef WINCOMPIL
using namespace parche_mingw;
#else
using namespace std;
#endif

	const std::string str_ventana=to_string(config.acc_w_fisica_pantalla())+"x"+to_string(config.acc_h_fisica_pantalla());
	componente_menu.menu().asignar_por_valor_templated<std::string>("01_K_TAM_VENTANA", str_ventana);
	componente_menu.menu().asignar_por_valor_templated<int>("02_K_IDIOMA_INTERFACE", config.acc_idioma_interface());
	componente_menu.menu().asignar_por_valor_templated<std::string>("03_K_IDIOMA_DICCIONARIO", config.acc_idioma_base_datos());
}

void Controlador_configuracion_aplicacion::generar_vista_menu()
{
	componente_menu.traducir_menu_opciones(localizador);

	auto f=[this](Herramientas_proyecto::Listado_vertical<item_config_app>& l, Herramientas_proyecto::Menu_opciones<std::string>& m, const std::vector<std::string>& v)
	{
		for(const auto& c : v) l.insertar({fuentes, c, m.nombre_opcion(c)+" : "+m.nombre_seleccion(c)});
	};
	
	componente_menu.montar(f);
}

void Controlador_configuracion_aplicacion::menu_down(item_config_app& item, int dir, float delta)
{
	const std::string& clave=item.clave;

	if(clave=="01_K_TAM_VENTANA")
	{
		componente_menu.menu().rotar_opcion(clave, dir);
		const std::string tam=componente_menu.menu().valor_templated<std::string>(clave);
		auto ev=DFramework::uptr_evento(new Eventos::Evento_cambio_ventana(tam));
		enviar_evento(ev);
		//TODO: Mostrar ventana de "Se aplicará al reiniciar.
	}
	else if(clave=="02_K_IDIOMA_INTERFACE")
	{
		componente_menu.menu().rotar_opcion(clave, dir);
		int id_idioma=componente_menu.menu().valor_templated<int>(clave);
		auto ev=DFramework::uptr_evento(new Eventos::Evento_cambio_idioma_interface(id_idioma));
		enviar_evento(ev);

		//Forzar traducción del menú.
		componente_menu.traducir_menu_opciones(localizador);
	}
	else if(clave=="03_K_IDIOMA_DICCIONARIO")
	{
		componente_menu.menu().rotar_opcion(clave, dir);
		const std::string acronimo=componente_menu.menu().valor_templated<std::string>(clave);
		auto ev=DFramework::uptr_evento(new Eventos::Evento_cambio_idioma_diccionario(acronimo));
		enviar_evento(ev);
	}

	//Refrescar la nueva vista del menú...
	item.texto=componente_menu.menu().nombre_opcion(clave)+" : "+componente_menu.menu().nombre_seleccion(clave);
	generar_vista_menu();
	componente_menu.regenerar_listado();
}

/////////////////////////////

void Controlador_configuracion_aplicacion::item_config_app::generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
{
	auto * txt=new DLibV::Representacion_TTF(fuentes.obtener_fuente("akashi", 20), {255, 255, 255, 255}, texto);
	txt->establecer_posicion(x, y);
	rep.insertar_representacion(txt);
}
