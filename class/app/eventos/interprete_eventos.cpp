#include "interprete_eventos.h"
using namespace App::Eventos;

#include "../etiqueta.h"

#include <iostream>

void Interprete_eventos::interpretar_evento(const DFramework::Evento_framework_interface& ev)
{
	switch(ev.tipo_evento())
	{
		case cambio_etiqueta: 	interpretar_evento(static_cast<const Evento_cambio_etiqueta&>(ev)); break;
		default:
//TODO: Inyectar log
//			LOG<<"Un evento del tipo "<<ev.tipo_evento()<<" no ha sido interpretado"<<std::endl;
		break;
	}
}

void Interprete_eventos::interpretar_evento(const Evento_cambio_etiqueta& ev)
{
	std::cout<<ev.e.acc_nombre()<<" "<<ev.e.acc_clave()<<std::endl;
//	config.mut_fondo(ev.ruta_fondo);
//	DLibV::Imagen img(ev.ruta_fondo.c_str(), pantalla.acc_ventana());
//	DLibV::Gestor_texturas::obtener(App::Recursos_graficos::RGT_BACKGROUND)->reemplazar(img);
//	config.grabar();
}
