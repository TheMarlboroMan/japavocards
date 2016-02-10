#include "configuracion_ejercicio.h"

#include <functional>

#include "estados_controladores.h"

#include "../app/framework_impl/input.h"
#include "../app/localizacion.h"

using namespace App;

Controlador_configuracion_ejercicio::Controlador_configuracion_ejercicio(DLibH::Log_base& l, const Fuentes& f, const Localizador& loc, Configuracion_ejercicio& c)
	:log(l), fuentes(f), localizador(loc), configuracion_ejercicio(c), listado(alto_listado, alto_item_listado), rep_listado(true)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	rep_listado.no_imponer_alpha();

	generar_menu();
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
		auto& item=list_config[listado.acc_indice_actual()];
		item.iic->al_salir();
		listado.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1);
	}
	else if(hay_cambio(&DFramework::Input::es_input_down, dir))
	{
		auto& item=list_config[listado.acc_indice_actual()];
		item.iic->al_down(dir, delta);
		generar_vista_listado(listado, rep_listado, x_listado, y_listado);
		//TODO: Y los eventos y tal?.
	}
	else if(hay_cambio(&DFramework::Input::es_input_pulsado, dir))
	{
		auto& item=list_config[listado.acc_indice_actual()];
		item.iic->al_pulsar(dir, delta);
		generar_vista_listado(listado, rep_listado, x_listado, y_listado);
		//TODO: Y los eventos y tal?.
	}
	else if(hay_cambio(&DFramework::Input::es_input_up, dir))
	{
		auto& item=list_config[listado.acc_indice_actual()];
		item.iic->al_up();
		//TODO: Y los eventos y tal?.
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
	generar_vista_listado(listado, rep_listado, x_listado, y_listado);
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

/**
* Se declaran varias mini clases y se colocan en el menú...
*/

void Controlador_configuracion_ejercicio::generar_menu()
{
#ifdef WINCOMPIL
using namespace parche_mingw;
#else
using namespace std;
#endif

	using namespace App::Listado_config;

	struct item_config_direccion:public interface_item_config
	{
				item_config_direccion(const DLibV::Fuente_TTF& f, Configuracion_ejercicio& c, const Localizador& l): interface_item_config(f, c, l) {}
		virtual void	al_down(int, float) {config.ciclar_direccion();}
		virtual void 	generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
		{
			auto * txt=new DLibV::Representacion_TTF(fuente, {255, 255, 255, 255}, localizador.obtener(localizar_direccion(config.acc_direccion())));
			txt->establecer_posicion(x, y);
			rep.insertar_representacion(txt);
		}
	};

	struct item_config_modo_etiquetas:public interface_item_config
	{
				item_config_modo_etiquetas(const DLibV::Fuente_TTF& f, Configuracion_ejercicio& c, const Localizador& l): interface_item_config(f, c, l) {}
		virtual void	al_down(int, float) {config.ciclar_modo_etiquetas();}
		virtual void 	generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
		{
			auto * txt=new DLibV::Representacion_TTF(fuente, {255, 255, 255, 255}, localizador.obtener(localizar_modo_etiquetas(config.acc_modo_etiquetas())));
			txt->establecer_posicion(x, y);
			rep.insertar_representacion(txt);
		}
	};

	struct item_config_limite_palabras:public interface_item_config
	{
				item_config_limite_palabras(const DLibV::Fuente_TTF& f, Configuracion_ejercicio& c, const Localizador& l): interface_item_config(f, c, l) {}
		virtual void	al_down(int, float) {config.intercambiar_palabras_limitadas();}
		virtual void 	generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
		{
			int indice=config.es_palabras_limitadas() ? localizacion::config_limitacion_palabras_si : localizacion::config_limitacion_palabras_no;
			auto * txt=new DLibV::Representacion_TTF(fuente, {255, 255, 255, 255}, localizador.obtener(indice));
			txt->establecer_posicion(x, y);
			rep.insertar_representacion(txt);
		}
	};

	struct item_config_numero_palabras:public interface_item_config
	{
		float 		tiempo;

		void		cambio(int dir)
		{
			if(dir > 0) config.sumar_palabras();
			else config.restar_palabras();
		}

				item_config_numero_palabras(const DLibV::Fuente_TTF& f, Configuracion_ejercicio& c, const Localizador& l): interface_item_config(f, c, l), tiempo(0.0f) {}
		virtual void	al_salir() {tiempo=0.0f;}
		virtual void	al_down(int dir, float delta)
		{
			cambio(dir);
			tiempo+=delta;
		}
		virtual void	al_pulsar(int dir, float delta)
		{
			if(tiempo >= 0.5f) cambio(dir);
			else tiempo+=delta;
		}

		virtual void	al_up()	{tiempo=0.0f;}

		virtual void 	generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
		{
			const std::string str=localizador.obtener(localizacion::config_limitacion_palabras_numero)+to_string(config.acc_palabras());
			auto * txt=new DLibV::Representacion_TTF(fuente, {255, 255, 255, 255}, str);
			txt->establecer_posicion(x, y);
			rep.insertar_representacion(txt);
		}
	};

	list_config.push_back(list_configuracion_ejercicio(new item_config_direccion(fuentes.obtener_fuente("akashi", 20), configuracion_ejercicio, localizador)));
	list_config.push_back(list_configuracion_ejercicio(new item_config_modo_etiquetas(fuentes.obtener_fuente("akashi", 20), configuracion_ejercicio, localizador)));
	list_config.push_back(list_configuracion_ejercicio(new item_config_limite_palabras(fuentes.obtener_fuente("akashi", 20), configuracion_ejercicio, localizador)));
	list_config.push_back(list_configuracion_ejercicio(new item_config_numero_palabras(fuentes.obtener_fuente("akashi", 20), configuracion_ejercicio, localizador)));

	listado.clear();
	for(const auto& e : list_config) listado.insertar(e);

}
