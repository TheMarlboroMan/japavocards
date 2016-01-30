#include <iostream>
#include <string>
#include "../class/app/datos_bruto.cpp"
#include "../class/app/lector.cpp"
#include <class/dnot_parser.h>

using namespace App;

void test_error(Lector_excepcion::tipo real, Lector_excepcion::tipo esperado, const std::string& c)
{
	if(real==esperado) std::cout<<"\t[OK] : "<<c<<std::endl;
	else std::cout<<"\t[ERROR] : "<<c<<std::endl;
}

int main(int argc, char ** argv)
{
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
		test_error(e.t, Lector_excepcion::tipo::idioma_repetido, e.what());
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
		test_error(e.t, Lector_excepcion::tipo::etiqueta_repetida, e.what());
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
		test_error(e.t, Lector_excepcion::tipo::idioma_no_existe, e.what());
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
		test_error(e.t, Lector_excepcion::tipo::idioma_repetido, e.what());
	}

	std::cout<<"Cargando error etiqueta repetida para palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"}, {id:2, nombre:\"Inglés\"}], \
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]}],\
palabras:[{japones:\"hagane\", romaji:\"hagane\",etiquetas:[\"colores\", \"colores\"], traducciones: []}]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::etiqueta_repetida, e.what());
	}

	std::cout<<"Cargando error etiqueta inexistente para palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"}, {id:2, nombre:\"Japonés\"}],\
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]}],\
palabras:[{japones:\"hagane\", romaji:\"hagane\",etiquetas:[\"colores\", \"snacks\"], traducciones:[]}]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::etiqueta_no_existe, e.what());
	}

	std::cout<<"Cargando error idioma repetido en definición de palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"},{id:2, nombre:\"Inglés\"}],\
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]}],\
palabras:[{japones:\"hagane\", romaji:\"hagane\",etiquetas:[\"colores\"], traducciones:[{id:1, traduccion:\"Acero\"}, {id:1, traduccion:\"Steel\"}]}]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::idioma_repetido, e.what());
	}

	std::cout<<"Cargando error romaji repetido en definición de palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"}],\
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"}]}],\
palabras:[\
	{japones:\"hagane\", romaji:\"hagane\",etiquetas:[], traducciones:[]},\
	{japones:\"stuff\", romaji:\"hagane\",etiquetas:[], traducciones:[]}\
]");
		L.cargar_desde_string(str);

	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::palabra_repetida, e.what());
	}

	std::cout<<"Cargando error idioma inexistente en definición de palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"},{id:2, nombre:\"Inglés\"}],\
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]}],\
palabras:[\
	{japones:\"hagane\", romaji:\"hagane\",etiquetas:[\"colores\"], traducciones:[{id:1, traduccion:\"Acero\"}, {id:2, traduccion:\"Steel\"}]},\
	{japones:\"stuff\", romaji:\"sosoko\",etiquetas:[], traducciones:[{id:1, traduccion:\"Cosa\"}, {id:3, traduccion:\"Things\"}]},\
]");
		L.cargar_desde_string(str);
	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::idioma_no_existe, e.what());
	}

	std::cout<<"Cargando error etiqueta inexistente al insertar palabra..."<<std::endl;
	try
	{
		Lector L;
		std::string str("\
idiomas:[{id:1, nombre:\"Español\"},{id:2, nombre:\"Inglés\"}],\
etiquetas:[{clave:\"colores\",nombres:[{id:1, nombre:\"Colores\"},{id:2, nombre:\"Colors\"}]}],\
palabras:[\
	{japones:\"hagane\", romaji:\"hagane\",etiquetas:[\"colores\"], traducciones:[{id:1, traduccion:\"Acero\"}, {id:2, traduccion:\"Steel\"}]},\
]");
		L.cargar_desde_string(str);
	 
		Etiqueta_bruto et_nueva{"stuff"};
		Palabra_bruto pl_nueva{"a", "b"};
		pl_nueva.etiquetas.push_back(&et_nueva);
		L.insertar_palabra(pl_nueva);

	}
	catch(Lector_excepcion& e)
	{
		test_error(e.t, Lector_excepcion::tipo::etiqueta_no_existe, e.what());
	}

	try
	{
		//Crear nuevo documento desde datos correctos...
		std::cout<<"Iniciando carga de documento en disco..."<<std::endl;
		Lector L;
		L.cargar("lector_test_in_ok.dnot");
	
		//Insertar nuevo idioma.
		std::cout<<"Insertando nuevo idioma..."<<std::endl;
		Idioma nuevo_idioma{3, "Francés"};
		L.insertar_idioma(nuevo_idioma);

		//Insertar nueva etiqueta.
		std::cout<<"Insertando nueva etiqueta..."<<std::endl;
		Etiqueta_bruto nueva_etiqueta{"nueva"};
		nueva_etiqueta.nombres[1]="Nueva";
		nueva_etiqueta.nombres[2]="New";
		nueva_etiqueta.nombres[3]="Nouveau";
		L.insertar_etiqueta(nueva_etiqueta);

		//Insertar nueva palabra.
		std::cout<<"Insertando nueva palabra..."<<std::endl;
		Palabra_bruto nueva_palabra{"japones", "romaji"};
		nueva_palabra.etiquetas.push_back(&nueva_etiqueta);
		nueva_palabra.traducciones[1]="Algo";
		nueva_palabra.traducciones[2]="Something";
		nueva_palabra.traducciones[3]="Couseau";
		L.insertar_palabra(nueva_palabra);

		//Eliminar palabra.
		std::cout<<"Eliminando palabra..."<<std::endl;
		//TODO TODO TODO

		//Eliminar etiqueta y retirar de palabras.

		//Eliminar idioma y retirar del resto.	

		//Ejecutar control de cordura de datos (cosas sueltas).

		//Guardar documento resultante.
	}
	catch(std::exception& e)
	{
		std::cout<<"\t[ERROR] - "<<e.what()<<std::endl;
	}

	return 0;
}
