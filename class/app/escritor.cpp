#include "escritor.h"


void Escritor::guardar(const std::string& ruta, const std::vector<Idioma>& idiomas, const std::vector<Etiqueta_bruto>& etiquetas, const std::vector<Palabra_bruto>& palabras)
{
	Dnot_token::t_mapa raiz;

	Dnot_token::par_mapa mapa;
	mapa["idiomas"]=generar_idiomas();
	mapa["etiquetas"]=generar_etiquetas();
	mapa["palabras"]=generar_palabras();

	raiz.asignar(mapa);
	std::cout<<raiz.serializar()<<std::endl;
}
