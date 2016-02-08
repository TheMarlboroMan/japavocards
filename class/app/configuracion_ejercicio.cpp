#include "configuracion_ejercicio.h"

#include "localizacion.h"

using namespace App;

Configuracion_ejercicio::Configuracion_ejercicio()
	:palabras_limitadas(false),
	direccion(direcciones::japones_a_traduccion),
	modo_etiquetas(modos_etiquetas::todas),
	palabras(min_palabras)
{

}

void Configuracion_ejercicio::sumar_palabras()
{
	if(palabras+1 <= max_palabras) ++palabras;
}

void Configuracion_ejercicio::restar_palabras()
{
	if(palabras-1 >= min_palabras) --palabras;
}

void Configuracion_ejercicio::ciclar_direccion()
{
	App::ciclar_direccion(direccion);
}

void Configuracion_ejercicio::ciclar_modo_etiquetas()
{
	App::ciclar_modo_etiquetas(modo_etiquetas);
}

void Configuracion_ejercicio::intercambiar_palabras_limitadas()
{
	palabras_limitadas=!palabras_limitadas;
}

void App::ciclar_direccion(Configuracion_ejercicio::direcciones& d)
{
	switch(d)
	{
		case Configuracion_ejercicio::direcciones::japones_a_traduccion: d=Configuracion_ejercicio::direcciones::traduccion_a_japones; break;
		case Configuracion_ejercicio::direcciones::traduccion_a_japones: d=Configuracion_ejercicio::direcciones::japones_a_traduccion; break;
	}
}

int App::localizar_direccion(Configuracion_ejercicio::direcciones d)
{
	switch(d)
	{
		case Configuracion_ejercicio::direcciones::japones_a_traduccion: return localizacion::config_japones_a_traduccion; break;
		case Configuracion_ejercicio::direcciones::traduccion_a_japones: return localizacion::config_traduccion_a_japones; break;
	}

	return 0;
}

void App::ciclar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas& m)
{
	switch(m)
	{
		case Configuracion_ejercicio::modos_etiquetas::todas:		m=Configuracion_ejercicio::modos_etiquetas::etiquetadas; break;
		case Configuracion_ejercicio::modos_etiquetas::etiquetadas:	m=Configuracion_ejercicio::modos_etiquetas::sin_etiquetar; break;
		case Configuracion_ejercicio::modos_etiquetas::sin_etiquetar:	m=Configuracion_ejercicio::modos_etiquetas::todas; break;
	}
}

int App::localizar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas m)
{
	switch(m)
	{
		case Configuracion_ejercicio::modos_etiquetas::todas:		return localizacion::config_modo_todas; break;
		case Configuracion_ejercicio::modos_etiquetas::etiquetadas:	return localizacion::config_modo_etiquetadas; break;
		case Configuracion_ejercicio::modos_etiquetas::sin_etiquetar:	return localizacion::config_modo_sin_etiquetar; break;
	}

	return 0;
}
