#ifndef ESCRITOR_H
#define ESCRITOR_H

#include <map>
#include <string>
#include <vector>

#include <class/dnot_parser.h>

#include "datos_bruto.h"

namespace App
{

class Escritor
{
	public:

	void		guardar(const std::string& ruta, const std::vector<Idioma>& idiomas, const std::vector<Etiqueta_bruto>& etiquetas, const std::vector<Palabra_bruto>& palabras);


	private:
};

}

#endif
