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

Controlador_etiquetas::Controlador_etiquetas(DLibH::Log_base& log, const Fuentes& f, const std::vector<Etiqueta>& ve)
	:log(log), fuentes(f), listado(alto_listado, alto_item_listado), rep_listado(true)
{
	vista.mapear_fuente("akashi20", &fuentes.obtener_fuente("akashi", 20));
	vista.mapear_fuente("kanas32", &fuentes.obtener_fuente("kanas", 32));

	//Preparar listado...
	//TODO: ¿Cómo vamos a marcar las seleccionadas al entrar?.
	listado.mut_margen_h(margen_y);
	rep_listado.no_imponer_alpha();

	for(const auto& e : ve) list_etiquetas.push_back(list_etiqueta(fuentes.obtener_fuente("akashi", 20), &e));

//TODO: a partir del listado de etiquetas crear un menú de templates bool usando las propias claves de las etiquetas.
//ese menú es el que luego podremos ir usando.

	refrescar_listado();
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
		if(listado.cambiar_item(input.es_input_down(App::Input::arriba) ? -1 : 1))
		{
			generar_vista_listado(listado, rep_listado, x_listado, y_listado);
		}
	}
	//TODO: Añadir inputs de avanzar y repetir página para pasar más deprisa.

	else if(input.es_input_down(App::Input::izquierda) ||
		input.es_input_down(App::Input::derecha) ||
		input.es_input_down(App::Input::aceptar))
	{
		auto& item=list_etiquetas[listado.acc_indice_actual()];
		item.intercambiar();
		refrescar_listado();
		generar_vista_listado(listado, rep_listado, x_listado, y_listado);

		auto ev=DFramework::uptr_evento(new Eventos::Evento_cambio_etiqueta(*item.etiqueta));
		enviar_evento(ev);
	}
}

void  Controlador_etiquetas::postloop(DFramework::Input& input, float delta)
{

}

void  Controlador_etiquetas::dibujar(DLibV::Pantalla& pantalla)
{
	vista.volcar(pantalla);
	rep_listado.volcar(pantalla);

	//TODO: Mostrar paginación de etiquetas.

	//TODO: ¿Dónde está el selector actual? Lo podríamos pasar tb???
	//Podemos meter esto en otra función o algo así??. Si es posible,
	//podemos omitir parámetros del tipo ancho y alto_item???.

	//Selección actual...
	const int y=y_listado+(listado.linea_actual().y);
	DLibV::Representacion_primitiva_caja seleccion_actual({0, y, ancho_listado, alto_item_listado}, 255, 255, 255);
	seleccion_actual.establecer_alpha(128);
	seleccion_actual.volcar(pantalla);
}

void  Controlador_etiquetas::despertar()
{
	log<<"Despertando controlador etiquetas"<<std::endl;
	vista.parsear("data/layout/etiquetas.dnot", "layout");
	generar_vista_listado(listado, rep_listado, x_listado, y_listado);
}

void  Controlador_etiquetas::dormir()
{
	log<<"Durmiendo controlador etiquetas"<<std::endl;
	vista.vaciar_vista();
	rep_listado.vaciar_grupo();
}

bool Controlador_etiquetas::es_posible_abandonar_estado() const
{
	return true;
}

/**
* Refresca el contenido del objeto de listado, debemos hacerlo con cada cambio...
*/

void Controlador_etiquetas::refrescar_listado()
{
	listado.clear();
	for(const auto& e : list_etiquetas) listado.insertar(e);
}

list_etiqueta::list_etiqueta(const DLibV::Fuente_TTF& f, Etiqueta const * e)
	:seleccionado(false), fuente(f), etiqueta(e)
{

}

void list_etiqueta::generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const
{
#ifdef WINCOMPIL
using namespace parche_mingw;
#else
using namespace std;
#endif

	std::string texto;
	texto+=seleccionado ? "[*]" : "[ ]";
	texto+=" "+etiqueta->acc_nombre()+" ("+to_string(etiqueta->acc_asignaciones())+")";

	auto * txt=new DLibV::Representacion_TTF(fuente, {255, 255, 255, 255}, texto);
	txt->establecer_posicion(x, y);
	rep.insertar_representacion(txt);
}

bool list_etiqueta::operator<(const list_etiqueta& o)
{
	if(!etiqueta) return true;
	else return etiqueta->acc_nombre() < o.etiqueta->acc_nombre();
}


void list_etiqueta::intercambiar()
{
	seleccionado=!seleccionado;
}
