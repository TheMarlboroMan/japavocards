#include "lector.h"
#include <sstream>
#include <algorithm>

using namespace App;

void Lector::cargar_desde_string(const std::string& s, int flags)
{
	std::stringstream ss;
	ss<<s;

	using namespace Herramientas_proyecto;

	Dnot_parser p(ss);
	p();
	cargar(p.acc_token(), flags);
	
}

void Lector::cargar(const std::string& ruta, int flags)
{
	using namespace Herramientas_proyecto;
	const auto& root=parsear_dnot(ruta);
	cargar(root, flags);
}

void Lector::cargar(const Herramientas_proyecto::Dnot_token& root, int flags)
{
	try
	{
		if(flags & cargar_idiomas)
		{
			const auto& tok_idiomas=root["idiomas"].acc_lista();
			for(const auto& p : tok_idiomas) insertar_idioma(idioma_desde_token(p));
		}

		if(flags & cargar_etiquetas)
		{
			const auto& tok_etiquetas=root["etiquetas"].acc_lista();
			for(const auto& p : tok_etiquetas) insertar_etiqueta(etiqueta_desde_token(p));
		}

		if(flags & cargar_palabras)
		{
			const auto& tok_palabras=root["palabras"].acc_lista();
			for(const auto& p : tok_palabras) insertar_palabra(palabra_desde_token(p));
		}
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
	{acronimo:"ES", nombre:"Español"}
	{acronimo:"EN", nombre:"Inglés"}
]");
*/

Idioma Lector::idioma_desde_token(const Herramientas_proyecto::Dnot_token& tok)
{
	return Idioma{tok["acronimo"], tok["nombre"]};
}

/*
etiquetas:[
	{clave:"colores",nombres:[
		{acronimo:"ES", nombre:"Colores"},
		{acronimo:"EN", nombre:"Colors"}
	]},
]
*/

Etiqueta_bruto Lector::etiqueta_desde_token(const Herramientas_proyecto::Dnot_token& tok)
{
	Etiqueta_bruto res{tok["clave"]};

	const auto& lista=tok["nombres"].acc_lista();
	for(const auto& p : lista) 
	{
		std::string acronimo=p["acronimo"];
		std::string nombre=p["nombre"];

		if(res.nombres.count(acronimo)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_repetido, 
			"Idioma "+acronimo+" repetido para etiqueta "+res.clave);

		res.nombres[acronimo]=nombre;
	}
	
	return res;
}

/*
palabras:[
	{japones:"somethingsomething", romaji:"somethingromaji",
	etiquetas:["pronombres", "faciles"],
	traducciones:[
		{acronimo:"ES", traduccion:"Something romaji en idioma 1"},
		{acronimo:"EN", traduccion:"Something romaji en idioma 2"}]
	},
	{japones:"somethingsomethingother", romaji:"somethingromajiother",
	etiquetas:["frutasyverduras"],
	traducciones:[
		{acronimo:"ES", traduccion:"Other romaji en idioma 1"},
		{acronimo:"EN", traduccion:"Other romaji en idioma 2"}]
	},
	{japones:"hagane", romaji:"hagane",
	etiquetas:[],
	traducciones:[
		{acronimo:"ES", traduccion:"Acero"}
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
				"Etiqueta "+clave_etiqueta+" no existe para palabra "+res.japones);
		const auto& et=etiquetas[clave_etiqueta];

		//Buscar para ver que no está repetida
		if(std::find(std::begin(res.etiquetas), std::end(res.etiquetas), &et)!=std::end(res.etiquetas))
			throw Lector_excepcion(
				Lector_excepcion::tipo::etiqueta_repetida,
				"Etiqueta "+clave_etiqueta+" repetida para palabra "+res.japones);
		res.etiquetas.push_back(&et);
	}

	const auto& traducciones=tok["traducciones"].acc_lista();
	for(const auto& p : traducciones)
	{
		std::string acronimo=p["acronimo"];
		if(res.traducciones.count(acronimo)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_repetido,
			"Idioma "+acronimo+" repetido para palabra "+res.japones);
		res.traducciones[acronimo]=p["traduccion"].acc_string();
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
	if(idiomas.count(I.acronimo)) throw Lector_excepcion(
		Lector_excepcion::tipo::idioma_repetido,
		"Clave de idioma "+I.acronimo+" repetida");
	idiomas[I.acronimo]=I;
}

void Lector::insertar_etiqueta(const Etiqueta_bruto& E)
{
	if(etiquetas.count(E.clave)) throw Lector_excepcion(
		Lector_excepcion::tipo::etiqueta_repetida,
		"Clave de etiqueta "+E.clave+" repetida");
	for(const auto& p : E.nombres) if(!idiomas.count(p.first)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma "+p.first+" para etiqueta "+E.clave);		
	etiquetas[E.clave]=E;
}

void Lector::insertar_palabra(const Palabra_bruto& P)
{
	if(palabras.count(P.japones)) throw Lector_excepcion(
		Lector_excepcion::tipo::palabra_repetida,
		"Clave de palabra "+P.japones+" repetida");
	for(const auto& e : P.etiquetas) 
		if(!etiquetas.count(e->clave)) throw Lector_excepcion(
			Lector_excepcion::tipo::etiqueta_no_existe,
			"Etiqueta "+e->clave+" no existe para palabra "+P.japones+".");
	for(const auto& p : P.traducciones) 
		if(!idiomas.count(p.first)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma "+p.first+" para palabra "+P.japones);		
	palabras[P.japones]=P;

}

void Lector::eliminar_idioma(const std::string& indice)
{
	if(!idiomas.count(indice)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma con acrónimo "+indice);

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

void Lector::eliminar_palabra(const std::string& japones)
{
	if(!palabras.count(japones)) throw Lector_excepcion(
			Lector_excepcion::tipo::palabra_no_existe,
			"No existe la palabra "+japones);

	palabras.erase(japones);
}

Idioma&	Lector::obtener_idioma(const std::string& indice)
{
	if(!idiomas.count(indice)) throw Lector_excepcion(
			Lector_excepcion::tipo::idioma_no_existe,
			"No existe el idioma con acrónimo "+indice);

	return idiomas[indice];
}

Etiqueta_bruto& Lector::obtener_etiqueta(const std::string& clave)
{
	if(!etiquetas.count(clave)) throw Lector_excepcion(
			Lector_excepcion::tipo::etiqueta_no_existe,
			"No existe la etiqueta con clave "+clave);

	return etiquetas[clave];
}

Palabra_bruto& Lector::obtener_palabra(const std::string& japones)
{
	if(!palabras.count(japones)) throw Lector_excepcion(
			Lector_excepcion::tipo::palabra_no_existe,
			"No existe la palabra "+japones);

	return palabras[japones];
}

const std::vector<Idioma const *> Lector::acc_idiomas()const
{
	std::vector<Idioma const *> res;
	for(const auto& p : idiomas) res.push_back(&p.second);
	std::sort(std::begin(res), std::end(res));
	return res;
}

const std::vector<Etiqueta_bruto const *> Lector::acc_etiquetas()const
{
	std::vector<Etiqueta_bruto const *> res;
	for(const auto& p : etiquetas) res.push_back(&p.second);
	std::sort(std::begin(res), std::end(res));
	return res;
}

const std::vector<Palabra_bruto const *> Lector::acc_palabras()const
{
	std::vector<Palabra_bruto const *> res;
	for(const auto& p : palabras) res.push_back(&p.second);
	std::sort(std::begin(res), std::end(res));
	return res;
}
