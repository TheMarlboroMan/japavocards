#ifndef LECTOR_H
#define LECTOR_H

#include <map>
#include <string>
#include <stdexcept>

#include <class/dnot_parser.h>

#include "datos_bruto.h"

namespace App
{

struct Lector_excepcion:
	public std::runtime_error
{
	Lector_excepcion(const std::string& s):std::runtime_error(s) {}
};

class Lector
{
	public:

	void			cargar_desde_string(const std::string&);
	void			cargar(const std::string&);
	void			guardar(const std::string&);

	void			insertar_idioma(const Idioma&);
	void			insertar_etiqueta(const Etiqueta_bruto&);
	void			insertar_palabra(const Palabra_bruto&);

	private:

	void			cargar(const Herramientas_proyecto::Dnot_token&);
	void			limpiar();

	Idioma			idioma_desde_token(const Herramientas_proyecto::Dnot_token&);
	Etiqueta_bruto		etiqueta_desde_token(const Herramientas_proyecto::Dnot_token&);
	Palabra_bruto		palabra_desde_token(const Herramientas_proyecto::Dnot_token&);

	std::map<int, Idioma>			idiomas;
	std::map<std::string, Etiqueta_bruto>	etiquetas;
	std::map<std::string, Palabra_bruto>	palabras;
};

}

#endif
