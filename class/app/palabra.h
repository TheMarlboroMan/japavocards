#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include <vector>
#include <stdexcept>

#include "etiqueta.h"

/**
* La palabra instanciada tiene una única traducción en el idioma del que haya
* salido.
*/

namespace App
{

class Palabra
{
	public:

					Palabra(const std::string&, const std::string&, const std::string&);

	const std::string&		acc_japones() const {return japones;}
	const std::string&		acc_romaji() const {return romaji;}
	const std::string&		acc_traduccion() const {return traduccion;}
	std::string			obtener_string_etiquetas() const;

	bool				tiene_etiqueta(const Etiqueta& e) const;

	void				mut_japones(const std::string& v) {japones=v;}
	void				mut_romaji(const std::string& v) {romaji=v;}
	void				mut_traduccion(const std::string& v) {traduccion=v;}

	void				insertar_etiqueta(const Etiqueta& e);
	void				eliminar_etiqueta(const Etiqueta& e);
	void				limpiar_etiquetas();
	size_t				total_etiquetas() const {return etiquetas.size();}

	bool				operator==(const Palabra&) const; //Este operador se define por que el valor "japones" sea el mismo!!!!.
	bool				operator<(const Palabra&) const;

	private:

	std::string					japones,
							romaji,
							traduccion;
	std::vector<Etiqueta const *>			etiquetas;
};

}


#endif
