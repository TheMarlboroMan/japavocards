#include "escritor.h"

using namespace App;

void Escritor::generar(
	const std::vector<Idioma const *>& idiomas, 
	const std::vector<Etiqueta_bruto const *>& etiquetas, 
	const std::vector<Palabra_bruto const *>& palabras)
{
	using namespace Herramientas_proyecto;

	Dnot_token::t_mapa mapa;
	mapa["idiomas"]=generar_idiomas(idiomas);
	mapa["etiquetas"]=generar_etiquetas(etiquetas);
	mapa["palabras"]=generar_palabras(palabras);

	Dnot_token raiz;
	raiz.asignar(mapa);

	serializado=raiz.serializar();
}

void Escritor::guardar(const std::string& r) const
{
	if(!serializado.size())
	{
		throw Escritor_exception("No se ha cargado el escritor");
	}

	std::ofstream salida(r);
	salida<<serializado;
}

/*
idiomas:[
	{id:1, nombre:"Español"},
	{id:2, nombre:"Inglés"}
],
*/

Herramientas_proyecto::Dnot_token Escritor::generar_idiomas(const std::vector<Idioma const *>& v)
{
	using namespace Herramientas_proyecto;

	auto crear_idioma=[](const Idioma& I)
	{
		Dnot_token::t_mapa mapa;
		mapa["id"].asignar(I.id);
		mapa["nombre"].asignar(I.nombre);

		Dnot_token obj;
		obj.asignar(mapa);
		return obj;
	};

	Dnot_token::t_vector lista;
	for(const auto& i : v) lista.push_back(crear_idioma(*i));

	Dnot_token res;
	res.asignar(lista);

	return res;
}

/*
etiquetas:[
	{
		clave:"colores",
		nombres:[
			{id:1, nombre:"Colores"},
			{id:2, nombre:"Colors"}]
	}...
],
*/

Herramientas_proyecto::Dnot_token Escritor::generar_etiquetas(const std::vector<Etiqueta_bruto const *>& v) 
{
	using namespace Herramientas_proyecto;

	auto crear_etiqueta=[](const Etiqueta_bruto& e)
	{
		Dnot_token::t_vector nombres;
		for(const auto& n : e.nombres)
		{
			Dnot_token::t_mapa mapa;
			mapa["id"].asignar(n.first);
			mapa["nombre"].asignar(n.second);

			Dnot_token nombre;
			nombre.asignar(mapa);

			nombres.push_back(nombre);
		}

		Dnot_token::t_mapa mapa;
		mapa["clave"].asignar(e.clave);
		mapa["nombres"].asignar(nombres);

		Dnot_token obj;
		obj.asignar(mapa);
		return obj;
	};

	Dnot_token::t_vector lista;
	for(const auto& i : v) lista.push_back(crear_etiqueta(*i));

	Dnot_token res;
	res.asignar(lista);

	return res;
}

/*
palabras:[
	{
		japones:"somethingsomething", romaji:"somethingromaji",
		etiquetas:["pronombres", "faciles"],
		traducciones:[
			{id:1, traduccion:"Something romaji en idioma 1"},
			{id:2, traduccion:"Something romaji en idioma 2"}
		]
	}...
]
*/

Herramientas_proyecto::Dnot_token Escritor::generar_palabras(const std::vector<Palabra_bruto const *>& v)
{
	using namespace Herramientas_proyecto;

	auto crear_nombre=[](const Palabra_bruto& e)
	{
		Dnot_token::t_vector traducciones;
		for(const auto& n : e.traducciones)
		{
			Dnot_token::t_mapa mapa;
			mapa["id"].asignar(n.first);
			mapa["traduccion"].asignar(n.second);

			Dnot_token traduccion;
			traduccion.asignar(mapa);
			traducciones.push_back(traduccion);
		}

		Dnot_token::t_vector etiquetas;
		for(const auto& t : e.etiquetas)
		{
			Dnot_token et;
			et.asignar(t->clave);
			etiquetas.push_back(et);
		}

		Dnot_token::t_mapa mapa;
		mapa["japones"].asignar(e.japones);
		mapa["romaji"].asignar(e.romaji);
		mapa["traducciones"].asignar(traducciones);
		mapa["etiquetas"].asignar(etiquetas);

		Dnot_token obj;
		obj.asignar(mapa);
		return obj;
	};

	Dnot_token::t_vector lista;
	for(const auto& i : v) lista.push_back(crear_nombre(*i));

	Dnot_token res;
	res.asignar(lista);

	return res;
}
