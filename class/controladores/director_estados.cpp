#include "director_estados.h"
//#include "../app/recursos.h"

using namespace App;

extern DLibH::Log_base LOG;

Director_estados::Director_estados(DFramework::Kernel& kernel, App::App_config& config, DLibH::Log_base& log)
	:Director_estados_interface(t_estados::PRINCIPAL, std::function<bool(int)>([](int v){return v >= MENU && v < MAX_ESTADOS;})),
	log(log),
	localizador("data/localizacion/app"),
	base_datos(log)
{
	//Preparar pantalla...
	auto& pantalla=kernel.acc_pantalla();

	int wf=config.acc_w_fisica_pantalla(), 
		hf=config.acc_h_fisica_pantalla(),
		wl=config.acc_w_logica_pantalla(),
		hl=config.acc_h_logica_pantalla();

	pantalla.inicializar(wf, hf);
	pantalla.establecer_medidas_logicas(wl, hl);
	pantalla.establecer_modo_ventana(config.acc_modo_pantalla());

	recargar_base_datos(config.acc_idioma_base_datos());

	//Cargar cadenas...
	localizador.inicializar(config.acc_idioma_interface());
	registrar_controladores(config);
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
	//TODO...
}

void Director_estados::preparar_cambio_estado(int deseado, int actual)
{
	//TODO: Si al cambiar de estado va a ocurrir algo, será aquí.
}
