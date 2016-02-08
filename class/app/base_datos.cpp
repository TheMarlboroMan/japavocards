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
