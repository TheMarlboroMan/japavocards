#include "filtro_palabras.h"

using namespace App;

std::vector<Palabra const *> App::filtrar_todas(const std::vector<Palabra>& palabras)
{
	std::vector<Palabra const *> res;
	for(const auto& p : palabras) res.push_back(&p); 
	return res;
}

std::vector<Palabra const *> App::filtrar_sin_etiquetar(const std::vector<Palabra>& palabras)
{
	std::vector<Palabra const *> res;
	for(const auto &p : palabras) 
	{
		if(!p.total_etiquetas()) res.push_back(&p); 
	}
	return res;
}

std::vector<Palabra const *> App::filtrar_etiquetadas(const std::vector<Palabra>& palabras, const std::vector<Etiqueta const *>& etiquetas)
{
	std::vector<Palabra const *> res;
	for(const auto &p : palabras) 
	{
		if(p.total_etiquetas()) 
		{
			for(const auto& et : etiquetas)
			{
				if(p.tiene_etiqueta(*et)) 
				{
					res.push_back(&p); 
					break;
				}
			}
		}
	}
	return res;
}
