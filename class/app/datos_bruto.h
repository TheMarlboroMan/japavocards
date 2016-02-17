#ifndef DATOS_BRUTO_H
#define DATOS_BRUTO_H

#include <string>
#include <map>
#include <vector>
#include "idioma.h"

namespace App
{

struct Etiqueta_bruto
{
	std::string				clave;
	std::map<std::string, std::string>	nombres;
	bool 		 		operator<(const Etiqueta_bruto&) const;
	bool				operator==(const Etiqueta_bruto&) const;
};

struct Palabra_bruto
{
	std::string				japones,	//Clave.
						romaji;
	std::map<std::string, std::string>	traducciones;
	std::vector<Etiqueta_bruto const *>	etiquetas;
	bool 		 			operator<(const Palabra_bruto&) const;
//	bool					operator==(const Palabra_bruto&) const;
};



}

#endif
