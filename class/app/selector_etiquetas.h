#ifndef SELECTOR_ETIQUETAS_H
#define SELECTOR_ETIQUETAS_H

#include <vector>
#include "etiqueta.h"

/**
* La única finalidad de esta clase es mantener un vector de etiquetas.
*/

namespace App
{

class Selector_etiquetas
{
	public:
	
	size_t						size() const {return etiquetas.size();}
	void						intercambiar(const Etiqueta& e);
	const std::vector<Etiqueta const *>&		acc_etiquetas() const {return etiquetas;}
	bool						es_seleccionada(const Etiqueta& e);

	private:

	std::vector<Etiqueta const *>			etiquetas;
};
}

#endif
