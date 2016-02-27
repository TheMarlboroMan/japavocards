#ifndef GENERADOR_LISTADOS_H
#define GENERADOR_LISTADOS_H

#include <video/representacion/representacion_agrupada/representacion_agrupada.h>
#include <video/representacion/representacion_primitiva/representacion_primitiva_caja/representacion_primitiva_caja.h>
#include <video/pantalla/pantalla.h>
#include <video/camara/camara.h>
#include <class/listado_vertical.h>
#include <class/compositor_vista.h>
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
		itemp.item.generar_representacion_listado(rep, x_listado, itemp.y);
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

	//Esos valores de uno son para evitar divisiones por cero :D.
	Componente_menu(float xl=1, float yl=1, int hi=1, int wl=1, int hl=1)
		:x_listado(xl), y_listado(yl),
		rep_listado(true),
		listado(hl, hi),
		seleccion_actual({(int)x_listado, 0, wl, hi}, 255, 255, 255)

	{
		seleccion_actual.establecer_alpha(128);
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
		actualizar_selector();

	}

	void actualizar_selector()
	{
		const int y=y_listado+(listado.linea_actual().y);
		seleccion_actual.ir_a(x_listado, y);
	}

	void	desmontar()
	{
		rep_listado.vaciar_grupo();
	}

	void	volcar(DLibV::Pantalla& p)
	{
		rep_listado.volcar(p);
		seleccion_actual.volcar(p);
	}

	void	volcar(DLibV::Pantalla& p, DLibV::Camara& c)
	{
		rep_listado.volcar(p, c);
		seleccion_actual.volcar(p, c);
	}

	bool	cambiar_item(int dir)
	{
		bool res=listado.cambiar_item(dir);
		actualizar_selector();
		return res;
	}

	bool	cambiar_pagina(int dir)
	{
		bool res=listado.cambiar_pagina(dir);
		actualizar_selector();
		return res;
	}

	T&	item_actual()
	{
		return listado.item_actual();
	}

	const T&	item_actual() const
	{
		return listado.item_actual();
	}

	size_t		acc_pagina_actual() const
	{
		return listado.acc_pagina_actual();
	}

	size_t		acc_total_paginas() const
	{
		return listado.acc_total_paginas();
	}

	//Mala praxis, pero bueno.
	Herramientas_proyecto::Menu_opciones<S>&		menu()
	{
		return menu_opciones;
	}

	//Doble mala praxis XD!.
	DLibV::Representacion_agrupada&				rep()
	{
		return rep_listado;
	}

	//T-t-t-triple mala praxis XD!.
	DLibV::Representacion_primitiva_caja&			rep_selector()
	{
		return seleccion_actual;
	}

	void establecer_posicion(float x, float y)
	{
		x_listado=x;
		y_listado=y;
		rep_listado.ir_a(x, y);
	}

	void establecer_espacio_listado(float x, float y, float w, float h, float hi)
	{
		establecer_posicion(x, y);
		listado.mut_h_disponible(h);
		listado.mut_h_item(hi);
		seleccion_actual.establecer_posicion(x, y, w, hi);
	}		

	float acc_x_listado() const {return x_listado;}
	float acc_y_listado() const {return y_listado;}

	private:

	float							x_listado,
								y_listado;

	Herramientas_proyecto::Menu_opciones<S>			menu_opciones;
	std::map<std::string, int>				menu_opciones_traducciones;
	DLibV::Representacion_agrupada		 		rep_listado;
	Herramientas_proyecto::Listado_vertical<T>		listado;
	DLibV::Representacion_primitiva_caja 			seleccion_actual;
};

template<typename A, typename B>
void configurar_camara_y_menu(const Herramientas_proyecto::Compositor_vista& vista,
	DLibV::Camara& camara, 
	Componente_menu<A, B>& componente_menu)
{
	//Establecer información de cámara...
	camara.enfocar_a(0,0);
	camara.mut_pos_x(vista.const_int("x_camara"));
	camara.mut_pos_y(vista.const_int("y_camara"));
	camara.mut_w_pos(vista.const_int("w_camara"));
	camara.mut_h_pos(vista.const_int("h_camara"));
	camara.mut_enfoque(vista.const_int("w_camara"), vista.const_int("h_camara"));

	//Restaurando posición original de los elementos del menú... 
	componente_menu.establecer_espacio_listado(vista.const_int("x_listado"), vista.const_int("y_listado"), vista.const_int("w_listado"), vista.const_int("h_listado"), vista.const_int("h_item"));
}

}

#endif
