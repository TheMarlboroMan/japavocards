#ifndef ETIQUETAS_H
#define ETIQUETAS_H

#include <vector>
#include <functional>

#include <herramientas/log_base/log_base.h>
#include <video/representacion/representacion_agrupada/representacion_agrupada.h>

#include <class/compositor_vista.h>
#include <class/listado_vertical.h>

#include "../framework/controlador_interface.h"

#include "../app/generador_listados.h"
#include "../app/fuentes.h"
#include "../app/etiqueta.h"
#include "../app/selector_etiquetas.h"
#include "../app/definiciones.h"
#include "../app/worker_animacion.h"
#include "../app/transiciones.h"

namespace App
{

class Controlador_etiquetas:
	public DFramework::Controlador_interface
{
	public:

					Controlador_etiquetas(DLibH::Log_base&, const Fuentes&, const std::vector<Etiqueta>&, const std::vector<std::string>&);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	private:

	void							crear_menu_opciones(const std::vector<Etiqueta>&, const std::vector<std::string>&);
	void							generar_vista_menu();
	std::string						valor_para_opcion(const std::string& clave);
	void							input_activo(DFramework::Input& input, float delta);

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
	DLibV::Camara						camara;
	Componente_menu<item_config_etiqueta, std::string>	componente_menu;
	Herramientas_proyecto::Compositor_vista			vista;
	estados_transicion					estado_transicion;
	Worker_animacion					worker_animacion;
};

}

#endif
