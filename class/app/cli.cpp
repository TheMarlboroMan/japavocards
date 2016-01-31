#include "cli.h"

using namespace App;

CLI::CLI(const std::string& nf, int id_idioma)
	:log("logs/cli.log"), nombre_fichero(nf),
	localizador("data/localizacion/cli"),
	cambios_guardados(true),
	seleccion_actual(0)
{
	localizador.inicializar(id_idioma);
	inicializar();
}

void CLI::inicializar()
{
	std::cout<<localizador.obtener(cli_inicializar_bienvenida)<<std::endl;

	//Comprobar existencia de fichero.
	if(Herramientas_proyecto::existe_fichero(nombre_fichero))
	{
		try
		{
			lector.cargar(nombre_fichero);
		}
		catch(std::exception& e)
		{
			std::cout<<localizador.obtener(cli_inicializar_error_lector)<<std::endl;
		}
	}
	else
	{
		std::cout<<localizador.obtener(cli_inicializar_sin_fichero)<<std::endl;
	}

	std::cout<<localizador.obtener(cli_inicializar_fichero_escogido)<<nombre_fichero<<std::endl;
}

void CLI::loop()
{
	menu_principal();
}

void CLI::menu_principal()
{
	bool salir=false;
	while(!salir)
	{
		std::cout<<localizador.obtener(cli_menu_principal);
		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': salir=confirmar_salida(); break;
			case 'i': menu_idiomas(); break;
			case 'l': /*TODO */break;
			case 'w': /*TODO */break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::menu_idiomas()
{
	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_idiomas);

		if(seleccion_actual)
		{
			int clave=std::stoi(opciones[seleccion_actual]);
			const auto& v=lector.buscar_idiomas([clave](const Idioma& I){return I.id==clave;});
			if(v.size())
			{
				std::cout<<localizador.obtener(cli_seleccion_actual)<<v[0]->nombre<<std::endl;
			}
			else
			{
				seleccion_actual=0;
			}
		}

		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': return; break;
			case 'l': listar_idiomas(); break;
			case 'f': buscar_idiomas(); break;
			case 'n': nuevo_idioma(); break;
			case 'c': seleccionar_actual(); break;
			case 'e': modificar_idioma(); break;
			case 'd': eliminar_idioma(); break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}

	opciones.clear();
}

bool CLI::confirmar_salida()
{
	if(cambios_guardados) return true;
	while(true)
	{
		std::cout<<localizador.obtener(cli_confirmar_salida);
		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case 'y': return true; break;
			case 'n': return false; break;
			default:
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::listar_idiomas()
{
	std::cout<<localizador.obtener(cli_listado_idiomas);

	const auto& v=lector.buscar_idiomas([](const Idioma& I) {return true;});
	mostrar_lista_idiomas(v);
}

void CLI::buscar_idiomas()
{
	std::cout<<localizador.obtener(cli_buscar_idiomas);
	std::string buscar=obtener_entrada_string();

	const auto& v=lector.buscar_idiomas([&buscar](const Idioma& I) {return I.nombre.find(buscar)!=std::string::npos;});
	std::cout<<localizador.obtener(cli_resultados_buscador)<<v.size()<<std::endl;
	mostrar_lista_idiomas(v);
}

void CLI::mostrar_lista_idiomas(const std::vector<Idioma const *>& v)
{
	opciones.clear();
	int opcion=1;

	for(const auto& i : v)
	{
		const auto& I=*i;
		opciones[opcion]=std::to_string(I.id);
		std::cout<<"["<<opcion<<"] : "<<I.nombre<<" ("<<I.id<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl;
}

void CLI::modificar_idioma()
{
	std::cout<<localizador.obtener(cli_modificar_idioma);
	std::string nombre=obtener_entrada_string();

	try
	{
		int clave=std::stoi(opciones[seleccion_actual]);
		auto& I=lector.obtener_idioma(clave);
		I.nombre=nombre;
		cambios_guardados=false;
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
	}
}

void CLI::eliminar_idioma()
{
	if(!seleccion_actual)
	{
		std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
	}
	
	try
	{
		int clave=std::stoi(opciones[seleccion_actual]);
		lector.eliminar_idioma(clave);
		std::cout<<localizador.obtener(cli_idioma_eliminado)<<std::endl;
		cambios_guardados=false;
		seleccion_actual=0;
	}
	catch(std::exception& e)
	{
		std::cout<<localizador.obtener(cli_error_eliminar)<<e.what()<<std::endl;
	}
}

void CLI::nuevo_idioma()
{
	std::cout<<localizador.obtener(cli_nuevo_idioma);
	std::string nombre=obtener_entrada_string();

	try
	{
		Idioma idioma{(int)lector.ultima_clave_idioma()+1, nombre};
		lector.insertar_idioma(idioma);
		cambios_guardados=false;
	}
	catch(Lector_excepcion& e)
	{
		std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
	}
}

void CLI::guardar()
{
	std::string nombre_copia=nombre_fichero+"."+std::to_string(time(NULL))+".bak";

	log<<localizador.obtener(log_iniciando_backup)<<nombre_copia;
	std::ofstream copia(nombre_copia);
	copia<<Herramientas_proyecto::volcar_fichero(nombre_fichero);
	copia.close();

	log<<localizador.obtener(log_iniciando_guardado)<<nombre_copia;
	Escritor E;
	E.generar(lector.acc_idiomas(), lector.acc_etiquetas(), lector.acc_palabras());
	E.guardar(nombre_fichero);

	cambios_guardados=true;
	std::cout<<localizador.obtener(cli_guardado_finalizado)<<std::endl;
}

char CLI::obtener_entrada_char()
{
	while(true)
	{
		std::cout<<">>";
		std::string input;
		std::getline(std::cin, input);
		if(input.size()==1) return input[0];
		else std::cout<<localizador.obtener(cli_opcion_char)<<std::endl;
	}
}

std::string CLI::obtener_entrada_string()
{
	while(true)
	{
		std::cout<<">>";
		std::string input;
		std::getline(std::cin, input);
		if(input.size()) return input;
		else std::cout<<localizador.obtener(cli_opcion_string)<<std::endl;
	}
}

void CLI::seleccionar_actual()
{
	std::cout<<localizador.obtener(cli_menu_seleccion)<<std::endl;

	if(!opciones.size())
	{
		std::cout<<localizador.obtener(cli_seleccion_vacia)<<std::endl;
		return;
	}
	
	while(true)
	{
		std::cout<<">>";
		std::string input;
		std::getline(std::cin, input);
		if(!input.size()) 
		{
			seleccion_actual=0;
			return;
		}
		else 
		{
			try
			{
				int s=std::stoi(input);
	
				if(opciones.count(s)) 
				{
					seleccion_actual=s;
					return;
				}
				else
				{
					std::cout<<localizador.obtener(cli_error_seleccion)<<std::endl;
				}
			}
			catch(std::exception& e)
			{
				std::cout<<localizador.obtener(cli_error_seleccion_invalida)<<std::endl;
			}
		}
	}
}
