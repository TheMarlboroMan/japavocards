#include "principal.h"

#include <string>
#include <algorithm>

#include "../app/framework_impl/input.h"
#include "estados_controladores.h"

#ifdef WINCOMPIL
/* Localización del parche mingw32... Esto debería estar en otro lado, supongo. */
#include <herramientas/herramientas/herramientas.h>
#endif

using namespace App;

Controlador_principal::Controlador_principal(DLibH::Log_base& log, const Fuentes& f)
	:log(log), fuentes(f), estado(estados::sin_resolver), indice_palabra_actual(0)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));
}

void  Controlador_principal::preloop(DFramework::Input& input, float delta)
{

}

void  Controlador_principal::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	
	if(input.es_input_down(App::Input::escape))
	{
		solicitar_cambio_estado(menu);
	}
	else if(input.es_input_down(App::Input::aceptar))
	{
		switch(estado)
		{
			case estados::sin_resolver:
				mostrar_interface();
				estado=estados::resuelto;

			break;

			case estados::resuelto:
				estado=estados::sin_resolver;
				escoger_nueva_palabra();
				ocultar_interface();
			break;
		}
	}
}

void  Controlador_principal::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_principal::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
}

void  Controlador_principal::despertar()
{
	log<<"Despertando controlador principal"<<std::endl;
	vista.parsear("data/layout/principal.dnot", "layout");

	if(!palabras.size())
	{
		log<<"No hay palabras que mostrar";
		abandonar_aplicacion(); //TODO: Volver al estado anterior... No se ejecutará un ciclo de esta...
		return;
	}

	establecer_textos();
	ocultar_interface();
}

void  Controlador_principal::dormir()
{
	log<<"Durmiendo controlador principal"<<std::endl;
	vista.vaciar_vista();
}

bool Controlador_principal::es_posible_abandonar_estado() const
{
	return true;
}

void Controlador_principal::escoger_nueva_palabra()
{
	++indice_palabra_actual;
	if(indice_palabra_actual >= palabras.size())
	{
		log<<"Fin de lista de palabras... Mezclando y reiniciando..."<<std::endl;
		indice_palabra_actual=0;
		std::random_shuffle(std::begin(palabras), std::end(palabras));
	}

	establecer_textos();
}

void Controlador_principal::mostrar_interface()
{
	vista.obtener_por_id("txt_japones")->hacer_visible();
	vista.obtener_por_id("txt_romaji")->hacer_visible();
	vista.obtener_por_id("txt_traduccion")->hacer_visible();
}

void Controlador_principal::ocultar_interface()
{
	vista.obtener_por_id("txt_japones")->hacer_visible();
	vista.obtener_por_id("txt_romaji")->hacer_invisible();
	vista.obtener_por_id("txt_traduccion")->hacer_invisible();
}

void Controlador_principal::establecer_palabras(std::vector<Palabra const *>&& p)
{
	palabras=std::move(p);
	std::random_shuffle(std::begin(palabras), std::end(palabras));
}

void Controlador_principal::establecer_textos()
{
#ifdef WINCOMPIL
	using namespace parche_mingw;
#else
	using namespace std;
#endif

/*
auto centrar=[](DLibV::Representacion * rep)
	{
		int w=rep->acc_posicion().w;
		int x=(800 - w) / 2;
		rep->establecer_posicion(x, 0, 0, 0, DLibV::Representacion::FRECT_X);
	};
*/

	try
	{
		const std::string contador=to_string(indice_palabra_actual+1)+" / "+to_string(palabras.size());
		const auto& p=*(palabras[indice_palabra_actual]);
		static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id("txt_japones"))->asignar(p.acc_japones());
		static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id("txt_romaji"))->asignar(p.acc_romaji());
		static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id("txt_traduccion"))->asignar(p.acc_traduccion());
		static_cast<DLibV::Representacion_TTF *>(vista.obtener_por_id("txt_cuenta"))->asignar(contador);
	}
	catch(std::exception& e)
	{
		std::string err="Error al establecer textos de controlador principal: ";
		err+=e.what();
		throw std::runtime_error(err);
	}
}