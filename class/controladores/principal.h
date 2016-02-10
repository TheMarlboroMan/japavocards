#ifndef CONTROLADOR_PRINCIPAL_H
#define CONTROLADOR_PRINCIPAL_H

#include <herramientas/log_base/log_base.h>

#include <class/compositor_vista.h>

#include "../framework/controlador_interface.h"

#include "../app/fuentes.h"
#include "../app/palabra.h"
#include "../app/configuracion_ejercicio.h"

namespace App
{

class Controlador_principal:
	public DFramework::Controlador_interface
{
	public:

					Controlador_principal(DLibH::Log_base&, const Fuentes&, Configuracion_ejercicio::direcciones);

	virtual void 			preloop(DFramework::Input& input, float delta);
	virtual void 			loop(DFramework::Input& input, float delta);
	virtual void 			postloop(DFramework::Input& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	virtual void 			despertar();
	virtual void 			dormir();
	virtual bool			es_posible_abandonar_estado() const;

	void				establecer_palabras(std::vector<Palabra const *>&& p);
	void				establecer_direccion(Configuracion_ejercicio::direcciones d) {direccion=d;}

	private:

	enum class estados{
		sin_resolver,
		resuelto
	};

	void					establecer_textos();
	void					mostrar_interface();
	void					ocultar_interface();
	void					escoger_nueva_palabra();

	DLibH::Log_base&			log;
	const Fuentes&				fuentes;

	estados					estado;
	Herramientas_proyecto::Compositor_vista	vista;
	std::vector<Palabra const *> 		palabras;
	size_t					indice_palabra_actual;
	Configuracion_ejercicio::direcciones	direccion;
};

}

#endif
