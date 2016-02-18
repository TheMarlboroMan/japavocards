#include "configuracion_ejercicio.h"

#include "localizacion.h"

using namespace App;

const std::string str_desde_japones="desde_japones";
const std::string str_a_japones="a_japones";
const std::string str_todas="todas";
const std::string str_etiquetadas="etiquetadas";
const std::string str_sin_etiquetar="sin_etiquetar";

Configuracion_ejercicio::Configuracion_ejercicio()
	:palabras_limitadas(true),
	direccion(direcciones::japones_a_traduccion),
	modo_etiquetas(modos_etiquetas::todas),
	palabras(min_palabras)
{

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

void App::ciclar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas& m, int dir)
{
	if(dir > 0)
	{
		switch(m)
		{
			case Configuracion_ejercicio::modos_etiquetas::todas:		m=Configuracion_ejercicio::modos_etiquetas::etiquetadas; break;
			case Configuracion_ejercicio::modos_etiquetas::etiquetadas:	m=Configuracion_ejercicio::modos_etiquetas::sin_etiquetar; break;
			case Configuracion_ejercicio::modos_etiquetas::sin_etiquetar:	m=Configuracion_ejercicio::modos_etiquetas::todas; break;
		}
	}
	else
	{
		switch(m)
		{
			case Configuracion_ejercicio::modos_etiquetas::todas:		m=Configuracion_ejercicio::modos_etiquetas::sin_etiquetar; break;
			case Configuracion_ejercicio::modos_etiquetas::etiquetadas:	m=Configuracion_ejercicio::modos_etiquetas::todas; break;
			case Configuracion_ejercicio::modos_etiquetas::sin_etiquetar:	m=Configuracion_ejercicio::modos_etiquetas::etiquetadas; break;
		}
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

std::string App::direccion_a_string(Configuracion_ejercicio::direcciones d)
{
	switch(d)
	{
		case Configuracion_ejercicio::direcciones::japones_a_traduccion: return str_desde_japones; break;
		case Configuracion_ejercicio::direcciones::traduccion_a_japones: return str_a_japones; break;
	}

	return "";
}

Configuracion_ejercicio::direcciones App::string_a_direccion(const std::string& c)
{
	if(c==str_desde_japones) return Configuracion_ejercicio::direcciones::japones_a_traduccion;
	else return Configuracion_ejercicio::direcciones::traduccion_a_japones;
}

std::string App::modo_etiquetas_a_string(Configuracion_ejercicio::modos_etiquetas m)
{
	switch(m)
	{
		case Configuracion_ejercicio::modos_etiquetas::todas:		return str_todas; break;
		case Configuracion_ejercicio::modos_etiquetas::etiquetadas:	return str_etiquetadas; break;
		case Configuracion_ejercicio::modos_etiquetas::sin_etiquetar:	return str_sin_etiquetar; break;
	}

	return "";
}

Configuracion_ejercicio::modos_etiquetas App::string_a_modo_etiquetas(const std::string& c)
{
	if(c==str_todas) return Configuracion_ejercicio::modos_etiquetas::todas;
	else if(c==str_etiquetadas) return Configuracion_ejercicio::modos_etiquetas::etiquetadas;
	else return Configuracion_ejercicio::modos_etiquetas::sin_etiquetar;
}

void App::cambiar_cantidad_palabras(int& palabras, int dir)
{
	palabras+=dir;

	if(palabras > Configuracion_ejercicio::max_palabras) palabras=Configuracion_ejercicio::max_palabras;
	else if(palabras < Configuracion_ejercicio::min_palabras) palabras=Configuracion_ejercicio::min_palabras;
}
