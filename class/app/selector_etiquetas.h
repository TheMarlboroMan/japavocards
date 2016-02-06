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
	
							Selector_etiquetas();

	enum class 					modos{todas, sin_etiquetar, etiquetadas};

	void						ciclar_modo();
	modos						acc_modo() const {return modo;}
	size_t						size() const {return etiquetas.size();}
	void						intercambiar(const Etiqueta& e);
	const std::vector<Etiqueta const *>&		acc_etiquetas() const {return etiquetas;}
	bool						es_seleccionada(const Etiqueta& e);

	private:

	std::vector<Etiqueta const *>			etiquetas;
	modos						modo;
};

void	ciclar_modo(Selector_etiquetas::modos&);
int	localizar_modo(Selector_etiquetas::modos);

}

#endif
