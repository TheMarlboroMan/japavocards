#ifndef GENERADOR_LISTADOS_H
#define GENERADOR_LISTADOS_H

#include <video/representacion/representacion_agrupada/representacion_agrupada.h>
#include <video/representacion/representacion_primitiva/representacion_primitiva_caja/representacion_primitiva_caja.h>
#include <video/pantalla/pantalla.h>
#include <class/listado_vertical.h>
#include <class/menu_opciones.h>
#include <base/localizador_base.h>

#include <functional>

/**
* Conjunto de helpers para generar listados verticales. Dejamos el algoritmo en 
* generar_vista_listado y creamos la interface Listable que, aunque no hace
* falta, está ahí para implementarla.
*/

namespace App
{
struct Listable
{
	virtual void generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const=0;
};

template <typename T>
void generar_vista_listado(Herramientas_proyecto::Listado_vertical<T>& listado, DLibV::Representacion_agrupada& rep, int x_listado, int y_listado)
{
	rep.vaciar_grupo();
	const auto pagina=listado.obtener_pagina();
	for(const auto& itemp : pagina) 
	{
		itemp.item.generar_representacion_listado(rep, x_listado, itemp.y + y_listado);
	}
}

/**
* Template que genera un menú de opciones. En un principio preparado para menús
* de opciones alimentados por un dnot, pero se podría usar para crear menús
* de opciones manuales.
*/

template<typename T, typename S>
class Componente_menu
{
	public:

	Componente_menu(int xl, int yl, int hi, int hl)
		:x_listado(xl), y_listado(yl),
		rep_listado(true),
		listado(hl, hi)		
	{
		rep_listado.no_imponer_alpha();
	}

	void	crear_menu_opciones(const std::string& ruta, const std::string& clave, const Herramientas_proyecto::Localizador_base& localizador)
	{
		using namespace Herramientas_proyecto;
		menu_opciones_desde_dnot(ruta, clave, menu_opciones, menu_opciones_traducciones);
		traducir_menu_opciones(localizador);
	}

	void	traducir_menu_opciones(const Herramientas_proyecto::Localizador_base& localizador)
	{
		using namespace Herramientas_proyecto;
		using traduccion=Menu_opciones<std::string>::struct_traduccion;
		std::vector<traduccion> trad={};
		for(const auto& par : menu_opciones_traducciones) trad.push_back({par.first, localizador.obtener(par.second)});
		menu_opciones.traducir(trad);	
	}

	//La función recibe una función sin valor de retorno. Sus valores de
	//entrada son un listado vertical del tipo T, el menú de opciones
	//subyacente y un vector de claves del menú. Se espera que ese vector
	//se use para rellenar el listado.

	void	montar(std::function<void(Herramientas_proyecto::Listado_vertical<T>&, Herramientas_proyecto::Menu_opciones<S>&, const std::vector<S>&)> f)
	{
		listado.clear();
		const auto& v=menu_opciones.obtener_claves();
		f(listado, menu_opciones, v);
		regenerar_listado();
	}

	void	regenerar_listado()
	{
		generar_vista_listado(listado, rep_listado, x_listado, y_listado);
	}

	void	desmontar()
	{
		rep_listado.vaciar_grupo();
	}

	void	volcar(DLibV::Pantalla& p, int ancho_listado, int alto_item_listado)
	{
		rep_listado.volcar(p);

		const int y=y_listado+(listado.linea_actual().y);
		DLibV::Representacion_primitiva_caja seleccion_actual({0, y, ancho_listado, alto_item_listado}, 255, 255, 255);
		seleccion_actual.establecer_alpha(128);
		seleccion_actual.volcar(p);
	}

	bool	cambiar_item(int dir)
	{
		return listado.cambiar_item(dir);
	}

	T&	item_actual()
	{
		return listado.item_actual();
	}

	const T&	item_actual() const
	{
		return listado.item_actual();
	}

	//Mala praxis, pero bueno.
	Herramientas_proyecto::Menu_opciones<S>&		menu()
	{
		return menu_opciones;
	}

	private:

	int 							x_listado,
								y_listado;

	Herramientas_proyecto::Menu_opciones<S>			menu_opciones;
	std::map<std::string, int>				menu_opciones_traducciones;
	DLibV::Representacion_agrupada		 		rep_listado;
	Herramientas_proyecto::Listado_vertical<T>		listado;
};

}

#endif
