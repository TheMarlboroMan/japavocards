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

	enum			carga {cargar_idiomas=1, cargar_etiquetas=2, cargar_palabras=4};

	void			cargar_desde_string(const std::string&, int flags=cargar_idiomas | cargar_etiquetas | cargar_palabras);
	void			cargar(const std::string&, int flags=cargar_idiomas | cargar_etiquetas | cargar_palabras);

	size_t			total_idiomas() const {return idiomas.size();}
	size_t			total_etiquetas() const {return etiquetas.size();}
	size_t			total_palabras() const {return palabras.size();}
//	int			ultima_clave_idioma() const {return idiomas.rbegin()->first;}

	void			insertar_idioma(const Idioma&);
	void			insertar_etiqueta(const Etiqueta_bruto&);
	void			insertar_palabra(const Palabra_bruto&);

	Idioma&			obtener_idioma(const std::string&);
	Etiqueta_bruto&		obtener_etiqueta(const std::string&);
	Palabra_bruto&		obtener_palabra(const std::string&);

	const std::vector<Idioma const *>		acc_idiomas()const;
	const std::vector<Etiqueta_bruto const *>	acc_etiquetas()const;
	const std::vector<Palabra_bruto const *>	acc_palabras()const;

	std::vector<Idioma const *>		buscar_idiomas(std::function<bool(const Idioma&)> f)const {return buscar(idiomas, f);}
	std::vector<Etiqueta_bruto const *>	buscar_etiquetas(std::function<bool(const Etiqueta_bruto&)> f)const {return buscar(etiquetas, f);}
	std::vector<Palabra_bruto const *>	buscar_palabras(std::function<bool(const Palabra_bruto&)> f)const {return buscar(palabras, f);}

	void			eliminar_idioma(const std::string&);
	void			eliminar_etiqueta(const std::string&);
	void			eliminar_palabra(const std::string&);

	private:

	void			cargar(const Herramientas_proyecto::Dnot_token&, int);
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

	std::map<std::string, Idioma>		idiomas;
	std::map<std::string, Etiqueta_bruto>	etiquetas;
	std::map<std::string, Palabra_bruto>	palabras;
};

}

#endif
