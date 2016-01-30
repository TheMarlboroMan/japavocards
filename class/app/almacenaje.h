#ifndef ALMACENAJE_H
#define ALMACENAJE_H

#include <vector>
#include "palabra.h"
#include "etiqueta.h"

/**
* La clase encargada de guardar y manipular etiquetas y palabras. 
* Tanto las palabras como las etiquetas se guardan en vectores. Se considera
* que el nombre de la etiqueta y el atributo "japones" de la palabra son 
* "claves primarias", por donde se ordenan y que no deben repetirse.
*
* operaciones de inserción y modificación pasarán por comprobar si la unicidad
* de la etiqueta (por nombre) y la palabra (por el atributo "japones") se
* mantiene.* 
*/

namespace App
{

class Almacenaje
{
	public:

	size_t					total_palabras() const;
	size_t					total_etiquetas() const;

	void					insertar_etiqueta(const Etiqueta&);
	void					insertar_palabra(const Palabra&);

	void					eliminar_etiqueta(const Etiqueta&);
	void					eliminar_palabra(const Palabra&);

	const Etiqueta&				obtener_etiqueta(const std::string&);
	Etiqueta&				obtener_etiqueta(const std::string&);

	const Palabra&				obtener_palabra(const std::string&);
	Palabra&				obtener_palabra(const std::string&);

	std::vector<Etiqueta const * const>	buscar_etiquetas(const std::string&) const;
	std::vector<Palabra const * const>	buscar_palabras_japones(const std::string&) const;
	std::vector<Palabra const * const>	buscar_palabras_romaji(const std::string&) const;
	std::vector<Palabra const * const>	buscar_palabras_traduccion(const std::string&) const;
	std::vector<Palabra const * const>	buscar_palabras_etiqueta(const Etiqueta&) const;

	private:

	bool					comprobar_unicidad_palabras(const std::string&) const;
	bool					comprobar_unicidad_etiquetas(const std::string&) const;

	std::vector<Etiqueta>			etiquetas;
	std::vector<Palabra>			palabras;
};

}

#endif
