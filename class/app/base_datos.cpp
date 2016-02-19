#include "base_datos.h"

using namespace App;

Base_datos::Base_datos(DLibH::Log_base& l)
	:log(l)
{

}

void Base_datos::cargar(const Lector& lector, const Idioma& idioma)
{
	Extractor e(lector, idioma, log);
	datos=std::move(e.extraer_almacenaje());
}

const Etiqueta& Base_datos::etiqueta_por_clave(const std::string& clave)
{
	auto it=std::find_if(std::begin(datos.etiquetas), std::end(datos.etiquetas), [&clave](const Etiqueta& e){
		return e.acc_clave()==clave;
	});

	if(it==std::end(datos.etiquetas))
	{
		throw std::runtime_error("Imposible localizar etiqueta con clave "+clave);
	}

	return *it;
}
