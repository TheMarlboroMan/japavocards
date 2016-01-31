#ifndef ESCRITOR_H
#define ESCRITOR_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include <class/dnot_token.h>

#include "datos_bruto.h"

namespace App
{

struct Escritor_exception:
	public std::runtime_error
{
	Escritor_exception(const std::string& s):std::runtime_error(s) {}
};

class Escritor
{
	public:

	void		generar(const std::vector<Idioma const *>&, 
				const std::vector<Etiqueta_bruto const *>&, 
				const std::vector<Palabra_bruto const *>&);

	void		guardar(const std::string&) const;

	private:

	std::string				serializado;

	Herramientas_proyecto::Dnot_token	generar_idiomas(const std::vector<Idioma const *>&);
	Herramientas_proyecto::Dnot_token	generar_etiquetas(const std::vector<Etiqueta_bruto const *>&);
	Herramientas_proyecto::Dnot_token	generar_palabras(const std::vector<Palabra_bruto const *>&);
};

}

#endif
