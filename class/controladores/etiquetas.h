#ifndef ETIQUETAS_H
#define ETIQUETAS_H

#include <vector>

#include <herramientas/log_base/log_base.h>
#include <video/representacion/representacion_agrupada/representacion_agrupada.h>

#include <class/compositor_vista.h>
#include <class/listado_vertical.h>

#include "../framework/controlador_interface.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/etiqueta.h"
#include "../app/selector_etiquetas.h"

namespace App
{

struct list_etiqueta
	:public Listable
{

	bool 				seleccionado;
	const DLibV::Fuente_TTF&	fuente;
	Etiqueta const *		etiqueta;

					list_etiqueta(const DLibV::Fuente_TTF& f, Etiqueta const * e);
	bool				operator<(const list_etiqueta& o);
	void				intercambiar();
	void 				generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;
};

class Controlador_etiquetas:
	public DFramework::Controlador_interface
{
	public:

					Controlador_etiquetas(DLibH::Log_base&, const Fuentes&, const std::vector<Etiqueta>&);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	void							refrescar_listado();

	//Referencias...
	DLibH::Log_base&					log;
	const Fuentes&						fuentes;

	struct item_config_etiqueta:public Listable
	{
		const Fuentes& 		fuentes;
		std::string 		clave, texto;
		virtual void 		generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const;

		item_config_etiqueta(const Fuentes& f, const std::string& k, const std::string& t):
			fuentes(f), clave(k), texto(t)
		{}
	};

	//Propiedades...
	Componente_menu<item_config_etiqueta, std::string>	componente_menu;
	std::vector<list_etiqueta>				list_etiquetas;
	Herramientas_proyecto::Listado_vertical<list_etiqueta>	listado;
	DLibV::Representacion_agrupada		 		rep_listado;
	Herramientas_proyecto::Compositor_vista			vista;

	//Constantes...
	static const int 					x_listado=16,
								y_listado=32,
								alto_item_listado=20,
								ancho_listado=300,
								alto_listado=160,
								margen_y=16;

};

}

#endif
