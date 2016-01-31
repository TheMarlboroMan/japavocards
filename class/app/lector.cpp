#include "lector.h"
#include <sstream>
#include <algorithm>

using namespace App;

void Lector::cargar_desde_string(const std::string& s)
{
	std::stringstream ss;
	ss<<s;

	using namespace Herramientas_proyecto;

	Dnot_parser p(ss);
	p();
	cargar(p.acc_token());
	
}

void Lector::cargar(const std::string& ruta)
{
	using namespace Herramientas_proyecto;
	const auto& root=parsear_dnot(ruta);
	cargar(root);
}

void Lector::cargar(const Herramientas_proyecto::Dnot_token& root)
{
	try
	{
		const auto& tok_idiomas=root["idiomas"].acc_lista();
		for(const auto& p : tok_idiomas) insertar_idioma(idioma_desde_token(p));
	
		const auto& tok_etiquetas=root["etiquetas"].acc_lista();
		for(const auto& p : tok_etiquetas) insertar_etiqueta(etiqueta_desde_token(p));
	
		const auto& tok_palabras=root["palabras"].acc_lista();
		for(const auto& p : tok_palabras) insertar_palabra(palabra_desde_token(p));
	}
	catch(Lector_excepcion& e)
	{
		throw e;
	}
	catch(std::exception& e)
	{
		throw Lector_excepcion(Lector_excepcion::tipo::error_sintaxis, e.what());
	}
}

/*
idiomas:[
	{id:1, nombre:"Español"}
	{id:2, nombre:"Inglés"}
]");
*/

Idioma Lector::idioma_desde_token(const Herramientas_proyecto::Dnot_token& tok)
{
	return Idioma{tok["id"], tok["nombre"]};
}

/*
etiquetas:[
	{clave:"colores",nombres:[
		{id:1, nombre:"Colores"},
		{id:2, nombre:"Colors"}
	]},
]
*/

Etiqueta_bruto Lector::etiqueta_desde_token(const Herramientas_proyecto::Dnot_token& tok)
{
	Etiqueta_bruto res{tok["clave"]};

	const auto& lista=tok["nombres"].acc_lista();
	for(const auto& p : lista) 
	{
		int id=p["id"];
		std::string nombre=p["nombre"];

		if(res.nombres.count(id)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_repetido, 
			"Idioma "+std::to_string(id)+" repetido para etiqueta "+res.clave);

		res.nombres[id]=nombre;
	}
	
	return res;
}

/*
palabras:[
	{japones:"somethingsomething", romaji:"somethingromaji",
	etiquetas:["pronombres", "faciles"],
	traducciones:[
		{id:1, traduccion:"Something romaji en idioma 1"},
		{id:2, traduccion:"Something romaji en idioma 2"}]
	},
	{japones:"somethingsomethingother", romaji:"somethingromajiother",
	etiquetas:["frutasyverduras"],
	traducciones:[
		{id:1, traduccion:"Other romaji en idioma 1"},
		{id:2, traduccion:"Other romaji en idioma 2"}]
	},
	{japones:"hagane", romaji:"hagane",
	etiquetas:[],
	traducciones:[
		{id:1, traduccion:"Acero"}
	}
]
*/

Palabra_bruto Lector::palabra_desde_token(const Herramientas_proyecto::Dnot_token& tok)
{

	Palabra_bruto res{tok["japones"], tok["romaji"]};

	const auto& lista_etiquetas=tok["etiquetas"].acc_lista();
	for(const auto& clave : lista_etiquetas) 
	{
		const std::string clave_etiqueta=clave.acc_string();

		if(!etiquetas.count(clave_etiqueta)) throw Lector_excepcion(
				Lector_excepcion::tipo::etiqueta_no_existe,
				"Etiqueta "+clave_etiqueta+" no existe para palabra "+res.romaji);
		const auto& et=etiquetas[clave_etiqueta];

		//Buscar para ver que no está repetida
		if(std::find(std::begin(res.etiquetas), std::end(res.etiquetas), &et)!=std::end(res.etiquetas))
			throw Lector_excepcion(
				Lector_excepcion::tipo::etiqueta_repetida,
				"Etiqueta "+clave_etiqueta+" repetida para palabra "+res.romaji);
		res.etiquetas.push_back(&et);
	}

	const auto& traducciones=tok["traducciones"].acc_lista();
	for(const auto& p : traducciones)
	{
		int id=p["id"];
		if(res.traducciones.count(id)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_repetido,
			"Idioma "+std::to_string(id)+" repetido para palabra "+res.romaji);
		res.traducciones[id]=p["traduccion"].acc_string();
	}

	return res;
}

void Lector::limpiar()
{
	idiomas.clear();
	etiquetas.clear();
	palabras.clear();
}

void Lector::insertar_idioma(const Idioma& I)
{
	if(idiomas.count(I.id)) throw Lector_excepcion(
		Lector_excepcion::tipo::idioma_repetido,
		"Clave de idioma "+std::to_string(I.id)+" repetida");
	idiomas[I.id]=I;
}

void Lector::insertar_etiqueta(const Etiqueta_bruto& E)
{
	if(etiquetas.count(E.clave)) throw Lector_excepcion(
		Lector_excepcion::tipo::etiqueta_repetida,
		"Clave de etiqueta "+E.clave+" repetida");
	for(const auto& p : E.nombres) if(!idiomas.count(p.first)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma "+std::to_string(p.first)+" para etiqueta "+E.clave);		
	etiquetas[E.clave]=E;
}

void Lector::insertar_palabra(const Palabra_bruto& P)
{
	if(palabras.count(P.romaji)) throw Lector_excepcion(
		Lector_excepcion::tipo::palabra_repetida,
		"Clave de palabra "+P.romaji+" repetida");
	for(const auto& e : P.etiquetas) 
		if(!etiquetas.count(e->clave)) throw Lector_excepcion(
			Lector_excepcion::tipo::etiqueta_no_existe,
			"Etiqueta "+e->clave+" no existe para palabra "+P.romaji+".");
	for(const auto& p : P.traducciones) 
		if(!idiomas.count(p.first)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma "+std::to_string(p.first)+" para palabra "+P.romaji);		
	palabras[P.romaji]=P;

}

void Lector::eliminar_idioma(int indice)
{
	if(!idiomas.count(indice)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma con id "+indice);

	for(auto& par : etiquetas)
	{
		auto& e=par.second;
		if(e.nombres.count(indice)) 
			e.nombres.erase(indice);
	}
		
	for(auto& par : palabras)
	{
		auto& p=par.second;
		if(p.traducciones.count(indice))
			p.traducciones.erase(indice);
	}

	idiomas.erase(indice);
}

void Lector::eliminar_etiqueta(const std::string& clave)
{
	if(!etiquetas.count(clave)) throw Lector_excepcion(
			Lector_excepcion::tipo::etiqueta_no_existe,
			"No existe la etiqueta con clave "+clave);
	
	auto& et=etiquetas[clave];
	for(auto& par: palabras)
	{
		auto& p=par.second;
		auto it=std::find(std::begin(p.etiquetas), std::end(p.etiquetas), &et);
		if(it!=std::end(p.etiquetas))
		{
			p.etiquetas.erase(it);
		}
	}		
	etiquetas.erase(clave);
}

void Lector::eliminar_palabra(const std::string& romaji)
{
	if(!palabras.count(romaji)) throw Lector_excepcion(
			Lector_excepcion::tipo::palabra_no_existe,
			"No existe la palabra "+romaji);

	palabras.erase(romaji);
}
