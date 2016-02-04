#ifndef ETIQUETA_H
#define ETIQUETA_H

#include <string>

namespace App
{

class Etiqueta
{
	public:

					Etiqueta(const std::string&, const std::string&);
	const std::string&		acc_nombre() const {return nombre;}
	const std::string&		acc_clave() const {return clave;}

	bool				operator<(const Etiqueta&) const;
	bool				operator==(const Etiqueta&) const;

	void				sumar_asignacion() {++palabras_asignadas;}
	size_t				acc_asignaciones() const {return palabras_asignadas;}

	private:

	std::string			nombre,
					clave;
	size_t				palabras_asignadas;
};

}

#endif
