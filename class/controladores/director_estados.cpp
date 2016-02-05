#include "director_estados.h"
//#include "../app/recursos.h"

using namespace App;

extern DLibH::Log_base LOG;

Director_estados::Director_estados(DFramework::Kernel& kernel, App::App_config& config, DLibH::Log_base& log)
	:Director_estados_interface(t_estados::menu, std::function<bool(int)>([](int v){return v >= menu && v < max_estados;})),
	log(log),
	localizador("data/localizacion/app"),
	base_datos(log)
{
	preparar_video(kernel, config);

	cargar_fuentes();

	recargar_base_datos(config.acc_idioma_base_datos());

	//Cargar cadenas...
	localizador.inicializar(config.acc_idioma_interface());

	//Registrar controladores.
	registrar_controladores(config);

	preparar_palabras();
}

void Director_estados::preparar_video(DFramework::Kernel& kernel, App::App_config& config)
{
	auto& pantalla=kernel.acc_pantalla();

	int wf=config.acc_w_fisica_pantalla(), 
		hf=config.acc_h_fisica_pantalla(),
		wl=config.acc_w_logica_pantalla(),
		hl=config.acc_h_logica_pantalla();

	pantalla.inicializar(wf, hf);
	pantalla.establecer_medidas_logicas(wl, hl);
	pantalla.establecer_modo_ventana(config.acc_modo_pantalla());
}

void Director_estados::recargar_base_datos(const std::string& acronimo)
{
	log<<"Cargando base de datos para idioma "<<acronimo<<std::endl;

	Lector lector;
	lector.cargar("data/app/db.dnot");

	try
	{
		base_datos.cargar(lector, lector.obtener_idioma(acronimo));
	}
	catch(Lector_excepcion &e)
	{
		log<<"\tError al obtener idioma de base de datos : "<<e.what()<<std::endl;
		log<<"\tIntentando cargar idioma por defecto..."<<std::endl;
		base_datos.cargar(lector, lector.obtener_idioma("ES"));
		log<<"\tRecuperación exitosa..."<<std::endl;
	}
}

void Director_estados::registrar_controladores(const App::App_config& config)
{
	//Loool.
	registrar_interprete_eventos(*this);

	controlador_menu.reset(new Controlador_menu(log, fuentes));
	controlador_etiquetas.reset(new Controlador_etiquetas(log, fuentes, base_datos.acc_etiquetas()));
	controlador_principal.reset(new Controlador_principal(log, fuentes));

	registrar_controlador(t_estados::menu, *controlador_menu);
	registrar_controlador(t_estados::etiquetas, *controlador_etiquetas);
	registrar_controlador(t_estados::principal, *controlador_principal);
}

void Director_estados::preparar_cambio_estado(int deseado, int actual)
{
	switch(deseado)
	{
		//TODO: No permitir ir al estado principal si no tiene palabras...
		case t_estados::principal: 
			preparar_palabras();
		break;
	}

	//TODO: Ahora mismo no hay forma de controlar si se puede entrar en un estado o no????
}

/**
* Prepara un vector de punteros a palabras con las palabras escogidas y se los
* pasa al controlador principal, que los reordenará.
*/

void Director_estados::preparar_palabras()
{
	//TODO: Actualizar el modo desde el controlador de etiquetas...
	switch(selector_etiquetas.acc_modo())
	{
		case Selector_etiquetas::modos::todas:
			controlador_principal->establecer_palabras(std::move(filtrar_todas(base_datos.acc_palabras())));
		break;
	
		case Selector_etiquetas::modos::sin_etiquetar:
			controlador_principal->establecer_palabras(std::move(filtrar_sin_etiquetar(base_datos.acc_palabras())));
		break;

		case Selector_etiquetas::modos::etiquetadas:
			if(!selector_etiquetas.size())
			{
				controlador_principal->establecer_palabras(std::move(filtrar_todas(base_datos.acc_palabras())));
			}
			else
			{	
				controlador_principal->establecer_palabras(
					std::move(
						filtrar_etiquetadas(
							base_datos.acc_palabras(), selector_etiquetas.acc_etiquetas())));
			}
		break;
	}	
}

void Director_estados::cargar_fuentes()
{
	fuentes.registrar_fuente("akashi", 20);
	fuentes.registrar_fuente("kanas", 32);
}

/********* Eventos ... ********************************************************/

void Director_estados::interpretar_evento(const DFramework::Evento_framework_interface& ev)
{
	using namespace App::Eventos;

	switch(ev.tipo_evento())
	{
		case cambio_etiqueta: 		interpretar_evento(static_cast<const Evento_cambio_etiqueta&>(ev)); break;
		case cambio_modo_etiqueta: 	interpretar_evento(static_cast<const Evento_cambio_modo_etiqueta&>(ev)); break;
		default:
			log<<"Un evento del tipo "<<ev.tipo_evento()<<" no ha sido interpretado"<<std::endl;
		break;
	}
}

void Director_estados::interpretar_evento(const Eventos::Evento_cambio_etiqueta& ev)
{
	log<<"EVENTO CAMBIO ETIQUETA"<<std::endl;
	selector_etiquetas.intercambiar(ev.e);
	//TODO: Guardar la configuración.
}

void Director_estados::interpretar_evento(const Eventos::Evento_cambio_modo_etiqueta& ev)
{
	log<<"EVENTO CICLO MODO DE ETIQUETAS"<<std::endl;
	selector_etiquetas.ciclar_modo();
	//TODO: Guardar la configuración.
}
