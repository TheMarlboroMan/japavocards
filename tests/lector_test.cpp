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
		std::cout<<"Insertando y buscando nuevo idioma..."<<std::endl;
		Idioma nuevo_idioma{3, "Francés"};
		L.insertar_idioma(nuevo_idioma);

		//Testear búsqueda de nuevo idioma.
		auto resultado_busqueda_idiomas=L.buscar_idiomas([](const Idioma& I) {return I.nombre[0]=='F';});
		if(resultado_busqueda_idiomas.size()!=1) throw std::runtime_error("Falla tamaño búsqueda idiomas");
		if(resultado_busqueda_idiomas[0]->id!=3 ||
			resultado_busqueda_idiomas[0]->nombre!="Francés") throw std::runtime_error("Fallan datos búsqueda idiomas");
		std::cout<<"\t[OK] - Busqueda correcta"<<std::endl;

		//Insertar nueva etiqueta.
		std::cout<<"Insertando y buscando nueva etiqueta..."<<std::endl;
		Etiqueta_bruto nueva_etiqueta{"nueva"};
		nueva_etiqueta.nombres[1]="Nueva";
		nueva_etiqueta.nombres[2]="New";
		nueva_etiqueta.nombres[3]="Nouveau";
		L.insertar_etiqueta(nueva_etiqueta);

		//Testear búsqueda de nueva etiqueta.
		auto resultado_busqueda_etiqueta=L.buscar_etiquetas([](const Etiqueta_bruto& E){return E.clave=="nueva";});
		if(resultado_busqueda_etiqueta.size()!=1) throw std::runtime_error("Falla tamaño búsqueda etiquetas simple");
		if(resultado_busqueda_etiqueta[0]->clave!="nueva" ||
			resultado_busqueda_etiqueta[0]->nombres.at(1)!="Nueva" ||
			resultado_busqueda_etiqueta[0]->nombres.at(2)!="New" ||
			resultado_busqueda_etiqueta[0]->nombres.at(3)!="Nouveau") throw std::runtime_error("Fallan datos búsqueda etiquetas simple");
		std::cout<<"\t[OK] - Busqueda correcta"<<std::endl;

		//Insertar nueva palabra.
		std::cout<<"Insertando y buscando nueva palabra..."<<std::endl;
		Palabra_bruto nueva_palabra{"japones", "romaji"};
		nueva_palabra.etiquetas.push_back(&nueva_etiqueta);
		nueva_palabra.traducciones[1]="Algo";
		nueva_palabra.traducciones[2]="Something";
		nueva_palabra.traducciones[3]="Couseau";
		L.insertar_palabra(nueva_palabra);

		auto f_palabra=[&nueva_etiqueta](const Palabra_bruto& P)
		{
			if(P.japones!="japones") return false;
			if(P.romaji!="romaji") return false;
			if(!P.etiquetas.size() || P.etiquetas[0]!=&nueva_etiqueta) return false;
			if(P.traducciones.at(1)!="Algo") return false;
			return true;
		};
		auto resultado_busqueda_palabra=L.buscar_palabras(f_palabra);
		if(resultado_busqueda_palabra.size()!=1) throw std::runtime_error("Falla búsqueda de palabras.");
		std::cout<<"\t[OK] - Busqueda correcta"<<std::endl;

		//Testear búsqueda de etiquetas compleja...
		std::cout<<"Ejecutando búsqueda etiqueta compleja..."<<std::endl;
		auto f_compleja=[](const Etiqueta_bruto& E)
		{
			for(const auto& n : E.nombres) 
				if(n.second.size() && n.second.at(0)=='F') return true;
			return false;
		};

		auto resultado_busqueda_etiqueta_compleja=L.buscar_etiquetas(f_compleja);
		if(resultado_busqueda_etiqueta_compleja.size()!=2) throw std::runtime_error("Falla tamaño búsqueda etiquetas compleja");
		std::cout<<"\t[OK] - Busqueda correcta"<<std::endl;

		std::cout<<"Ejecutando búsqueda sin resultados..."<<std::endl;
		auto f_etiqueta=[](const Etiqueta_bruto& E){return E.clave=="no_existe";};
		auto resultado_busqueda_etiqueta_sin_resultados=L.buscar_etiquetas(f_etiqueta);
		if(resultado_busqueda_etiqueta_sin_resultados.size()) throw std::runtime_error("Falla búsqueda sin resultados.");
		std::cout<<"\t[OK] - Busqueda correcta"<<std::endl;

		//Eliminar palabra.
		std::cout<<"Eliminando y buscando palabra..."<<std::endl;
		L.eliminar_palabra("somethingromaji");
		auto res_buscar_palabra_eliminada=L.buscar_palabras([](const Palabra_bruto& P){return P.romaji=="somethingromaji";});
		if(res_buscar_palabra_eliminada.size()) throw std::runtime_error("Falla búsqueda de palabra eliminada");

		try
		{
			L.eliminar_palabra("somethingromajiother");
		}
		catch(Lector_excepcion& e)
		{
			test_error(e.t, Lector_excepcion::tipo::palabra_no_existe, e.what());
		}

		//Eliminar etiqueta.
		std::cout<<"Eliminando y buscando etiqueta..."<<std::endl;
		L.eliminar_etiqueta("frutasyverduras");
		auto res_buscar_etiqueta_eliminada=L.buscar_etiquetas([](const Etiqueta_bruto& P){return P.clave=="frutasyverduras";});
		if(res_buscar_etiqueta_eliminada.size()) throw std::runtime_error("Falla búsqueda de etiqueta eliminada");

		try
		{
			L.eliminar_etiqueta("frutasyverduras");
		}
		catch(Lector_excepcion& e)
		{
			test_error(e.t, Lector_excepcion::tipo::etiqueta_no_existe, e.what());
		}		

		auto palabra_que_tenia_etiqueta_borrada=L.buscar_palabras([](const Palabra_bruto& P){return P.romaji=="momo";});
		if(palabra_que_tenia_etiqueta_borrada.size()!=1 ||
			palabra_que_tenia_etiqueta_borrada[0]->etiquetas.size()) throw std::runtime_error("Falla propagación de etiqueta borrada");
	
		//Eliminar idioma y retirar del resto.
		std::cout<<"Eliminando y buscando idioma..."<<std::endl;
		L.eliminar_idioma(2);
		auto res_busqueda_idioma_borrado=L.buscar_idiomas([](const Idioma& I){return I.id==2;});
		if(res_busqueda_idioma_borrado.size()) throw std::runtime_error("Falla eliminado de idioma");

		try
		{
			L.eliminar_idioma(2);
		}
		catch(Lector_excepcion& e)
		{
			test_error(e.t, Lector_excepcion::tipo::idioma_no_existe, e.what());
		}


		auto comprobar_idioma_borrado_en_etiquetas=L.buscar_etiquetas([](const Etiqueta_bruto& E){return E.nombres.count(2);});
		if(comprobar_idioma_borrado_en_etiquetas.size()) throw std::runtime_error("Fallo propagado borrado idioma en etiquetas");

		auto comprobar_idioma_borrado_en_palabras=L.buscar_palabras([](const Palabra_bruto& P){return P.traducciones.count(2);});
		if(comprobar_idioma_borrado_en_palabras.size()) throw std::runtime_error("Fallo propagado borrado idioma en palabras");
	}
	catch(std::exception& e)
	{
		std::cout<<"\t[ERROR] - "<<e.what()<<std::endl;
	}

	return 0;
}
