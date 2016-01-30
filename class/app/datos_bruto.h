#ifndef DATOS_BRUTO_H
#define DATOS_BRUTO_H

#include <string>
#include <map>
#include <vector>

namespace App
{

struct Idioma
{
	int 				id;
	std::string			nombre;
	bool 		 		operator<(const Idioma&) const;
};

struct Etiqueta_bruto
{
	std::string			clave;
	std::map<int, std::string>	nombres;
	bool 		 		operator<(const Etiqueta_bruto&) const;
	bool				operator==(const Etiqueta_bruto&) const;
};

struct Palabra_bruto
{
	std::string				japones,
						romaji;
	std::map<int, std::string>		traducciones;
	std::vector<Etiqueta_bruto const *>	etiquetas;
	bool 		 			operator<(const Palabra_bruto&) const;
//	bool					operator==(const Palabra_bruto&) const;
};



}

#endif
