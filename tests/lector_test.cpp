#include <iostream>
#include <string>
#include "../class/app/datos_bruto.cpp"
#include "../class/app/lector.cpp"

int main(int argc, char ** argv)
{
	using namespace App;

	std::cout<<"Cargando errores de idioma..."<<std::endl;
	try
	{
		Lector L;
		std::string str("idiomas:[\
	{id:1, nombre:\"Español\"},\
	{id:2, nombre:\"Inglés\"},\
	{id:1, nombre:\"Inglés\"}\
]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<"\t[OK] - Atrapada excepcion: "<<e.what()<<std::endl;
	}

	std::cout<<"Cargando error clave repetida para etiqueta..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[\
	{id:1, nombre:\"Español\"},\
	{id:2, nombre:\"Inglés\"}\
],\
etiquetas:[\
	{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]},\
	{clave:\"colores\",nombres:[{id:1, nombre:\"Cosa\"},{id:2, nombre:\"Thing\"}]}\
]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<"\t[OK] - Atrapada excepcion: "<<e.what()<<std::endl;
	}
	
	std::cout<<"Cargando error idioma no existe para etiqueta..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[\
	{id:1, nombre:\"Español\"},\
	{id:2, nombre:\"Inglés\"}\
],\
etiquetas:[\
	{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]},\
	{clave:\"cosas\",nombres:[{id:1, nombre:\"Cosa\"},{id:3, nombre:\"Thing\"}]}\
]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<"\t[OK] - Atrapada excepcion: "<<e.what()<<std::endl;
	}

	std::cout<<"Cargando error idioma repetido para etiqueta..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[\
	{id:1, nombre:\"Español\"},\
	{id:2, nombre:\"Inglés\"}\
],\
etiquetas:[\
	{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]},\
	{clave:\"cosas\",nombres:[{id:1, nombre:\"Cosa\"},{id:1, nombre:\"Thing\"}]}\
]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<"\t[OK] - Atrapada excepcion: "<<e.what()<<std::endl;
	}

	//TODO: Testear error etiqueta repetida en definición de palabra.
	//TODO: Testear error idioma repetido en definición de palabra.
	//TODO: Testear error romaji repetido en definición de palabra.
	//TODO: Testear error etiqueta inexistente al insertar palabra.
	//TODO: Testear error idioma inexistente al insertar palabra.

	return 0;
}
