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
	enum class tipo
	{
		idioma_repetido,
		idioma_no_existe,
		etiqueta_repetida,
		etiqueta_no_existe,
		palabra_repetida,
		palabra_no_existe,
		error_sintaxis
	}t;

	Lector_excepcion(tipo t, const std::string& s):std::runtime_error(s), t(t) {}
	
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

	//TODO: Funciones de búsqueda que reciban un std function y devuelvan punteros...
	std::vector<Idioma const *>		buscar_idiomas()const;
	std::vector<Etiqueta_bruto const *>	buscar_etiquetas()const;
	std::vector<Palabra_bruto const *>	buscar_palabras()const;

	void			eliminar_idioma(int);
	void			eliminar_etiqueta(const std::string&);
	void			eliminar_palabra(const std::string&);

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
