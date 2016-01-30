#include "palabra.h"
#include <algorithm>

using namespace App;

Palabra::Palabra(const std::string& j, const std::string& r, const std::string& t)
	:japones(j), romaji(r), traduccion(t)
{

}

std::string Palabra::obtener_string_etiquetas() const
{
	std::string res;
	for(const auto& e : etiquetas) res+=e->acc_nombre()+", ";
	if(res.size()) res=res.substr(0, res.size()-2);
	return res;
}

void Palabra::insertar_etiqueta(const Etiqueta& e)
{
	if(tiene_etiqueta(e))
	{
		throw std::runtime_error("La etiqueta "+e.acc_nombre()+" ya existe para asignarla a la palabra");
	}

	etiquetas.push_back(&e);
}

void Palabra::eliminar_etiqueta(const Etiqueta& e)
{

	auto it=std::find(std::begin(etiquetas), std::end(etiquetas), &e);
	if(it==std::end(etiquetas))
	{
		throw std::runtime_error("La etiqueta "+e.acc_nombre()+" no existe para eliminarla de la palabra");
	}

	etiquetas.erase(it);
}

void Palabra::limpiar_etiquetas()
{
	etiquetas.clear();
}

bool Palabra::tiene_etiqueta(const Etiqueta& e) const
{
	if(!etiquetas.size()) return false;

	auto it=std::find(std::begin(etiquetas), std::end(etiquetas), &e);
	return it!=std::end(etiquetas);
}
