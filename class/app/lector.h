#ifndef LECTOR_H
#define LECTOR_H

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>

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

	void			insertar_idioma(const Idioma&);
	void			insertar_etiqueta(const Etiqueta_bruto&);
	void			insertar_palabra(const Palabra_bruto&);

	const std::vector<Idioma const *>		acc_idiomas()const;
	const std::vector<Etiqueta_bruto const *>	acc_etiquetas()const;
	const std::vector<Palabra_bruto const *>	acc_palabras()const;

	std::vector<Idioma const *>		buscar_idiomas(std::function<bool(const Idioma&)> f)const {return buscar(idiomas, f);}
	std::vector<Etiqueta_bruto const *>	buscar_etiquetas(std::function<bool(const Etiqueta_bruto&)> f)const {return buscar(etiquetas, f);}
	std::vector<Palabra_bruto const *>	buscar_palabras(std::function<bool(const Palabra_bruto&)> f)const {return buscar(palabras, f);}

	void			eliminar_idioma(int);
	void			eliminar_etiqueta(const std::string&);
	void			eliminar_palabra(const std::string&);

	private:

	void			cargar(const Herramientas_proyecto::Dnot_token&);
	void			limpiar();

	template <typename T, typename K>
	std::vector<T const *> 	buscar(const std::map<K, T>& v, std::function<bool(const T&)> f) const
	{
		std::vector<T const *> res;
		for(const auto& i : v) if(f(i.second)) res.push_back(&i.second);
		std::sort(std::begin(res), std::end(res));
		return res;
	}
	
	Idioma			idioma_desde_token(const Herramientas_proyecto::Dnot_token&);
	Etiqueta_bruto		etiqueta_desde_token(const Herramientas_proyecto::Dnot_token&);
	Palabra_bruto		palabra_desde_token(const Herramientas_proyecto::Dnot_token&);

	std::map<int, Idioma>			idiomas;
	std::map<std::string, Etiqueta_bruto>	etiquetas;
	std::map<std::string, Palabra_bruto>	palabras;
};

}

#endif
