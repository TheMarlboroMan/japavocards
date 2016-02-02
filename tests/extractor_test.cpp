#include <iostream>
#include <string>
#include "../class/app/extractor.cpp"
#include "../class/app/lector.cpp"
#include "../class/app/datos_bruto.cpp"
#include "../class/app/palabra.cpp"
#include "../class/app/etiqueta.cpp"
#include <class/dnot_parser.h>
#include <herramientas/log_base/log_base.h>

using namespace App;

int main(int argc, char ** argv)
{
		std::string str("idiomas:[\
	{acronimo:\"ES\", nombre:\"Español\"},\
	{acronimo:\"EN\", nombre:\"Inglés\"}\
],\
etiquetas:[\
	{clave:\"bilingue\",nombres:[\
		{acronimo:\"ES\", nombre:\"Bilingue\"},\
		{acronimo:\"EN\", nombre:\"Bilingual\"}]\
	},\
	{clave:\"english\",nombres:[\
		{acronimo:\"EN\", nombre:\"English only\"}]\
	},\
	{clave:\"espanol\",nombres:[\
		{acronimo:\"ES\", nombre:\"Sólo español\"}]\
	},\
	{clave:\"espanol2\",nombres:[\
		{acronimo:\"ES\", nombre:\"Sólo español 2 que no se asigna\"}]\
	},\
	{clave:\"sin_usar\",nombres:[\
		{acronimo:\"ES\", nombre:\"Sin usar\"},\
		{acronimo:\"EN\", nombre:\"Unused\"}]\
	}\
],\
palabras:[\
	{\
		japones:\"completa\", romaji:\"completa\",\
		etiquetas:[\"bilingue\", \"english\", \"espanol\"],\
		traducciones:[\
			{acronimo:\"ES\", traduccion:\"Completa\"},\
			{acronimo:\"EN\", traduccion:\"Complete\"}]\
	},\
	{\
		japones:\"soloespanol\", romaji:\"soloespanol\",\
		etiquetas:[\"espanol\"],\
		traducciones:[\
			{acronimo:\"ES\", traduccion:\"Sólo español\"}]\
	},\
	{\
		japones:\"enlishonly\", romaji:\"enlishonly\",\
		etiquetas:[\"english\"],\
		traducciones:[\
			{acronimo:\"EN\", traduccion:\"English only\"}]\
	},\
	{\
		japones:\"unlabeled\", romaji:\"unlabeled\",\
		etiquetas:[],\
		traducciones:[\
			{acronimo:\"ES\", traduccion:\"Sin etiquetar\"},\
			{acronimo:\"EN\", traduccion:\"Unlabeled\"}]\
	}\
]");

	std::cout<<"Cargando lector..."<<std::endl;
	try
	{
		DLibH::Log_base log("log_extractor_test.log");

		Lector L;
		L.cargar_desde_string(str);
		
		const auto& v=L.acc_idiomas();
		for(const auto& i : v)
		{
			std::cout<<"- Iniciando extractor para "<<i->nombre<<"..."<<std::endl;
			Extractor e(L, *i, log);

			const auto vet=std::move(e.extraer_etiquetas());
			std::cout<<"Se extraen "<<vet.size()<<" etiquetas."<<std::endl;
			for(const auto& e : vet) std::cout<<"\t"<<e.acc_nombre()<<std::endl;

			const auto vpa=std::move(e.extraer_palabras());
			std::cout<<"Se extraen "<<vpa.size()<<" palabras."<<std::endl;
			for(const auto& p : vpa)
				std::cout<<"\t"<<p.acc_japones()<<" "<<p.acc_romaji()<<" "<<p.acc_traduccion()<<" ["<<p.obtener_string_etiquetas()<<"]"<<std::endl;
		}
	}
	catch(std::runtime_error& e)
	{
		std::cout<<"ERROR: "<<e.what()<<std::endl;
	}
	return 0;
}
