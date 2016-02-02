#include "cli.h"

using namespace App;

const std::string CLI::ruta_configuracion_cli="data/app/cli_config.dnot";
const std::string CLI::ruta_opciones_cli="data/app/cli_data.dnot";
const std::string CLI::marcado="*";
const std::string CLI::no_marcado="-";

CLI::CLI(const std::string& nf)
	:log("logs/cli.log"), nombre_fichero(nf),
	localizador("data/localizacion/cli"),
	cambios_guardados(true),
	seleccion_actual(""), idioma_canonico(""),
	id_idioma_interface(0)
{
	inicializar();
	inicializar_configuracion();
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

void CLI::inicializar_configuracion()
{
	try
	{
		using namespace Herramientas_proyecto;

		//Cargar información dinámica de configuración...
		const auto& root_data=parsear_dnot(ruta_opciones_cli.c_str());		
		const auto& idiomas=root_data["cli_valores"]["idiomas"].acc_lista();
		for(const auto& i : idiomas) 
		{
			int id=i["id"];
			const std::string nombre=i["nombre"];
			mapa_idiomas[id]=nombre;
		}

		//Establecer valores de configuración.
		const auto& root_config=parsear_dnot(ruta_configuracion_cli.c_str());
		const auto& config=root_config["cli_config"];
		id_idioma_interface=config["id_idioma"];

		//Intentamos instanciar el idioma que se indica en el fichero de configuración.
		//Si falla no habremos tocado nada...
		const std::string str_idioma_canonico=config["idioma_canonico"];
		const auto& idioma=lector.obtener_idioma(str_idioma_canonico);
		idioma_canonico=idioma.acronimo;
	}
	catch(std::exception& e)
	{
		log<<"Error en carga de configuración. Se iniciarán valores por defecto - : "<<e.what()<<std::endl;
		std::cout<<localizador.obtener(cli_error_carga_configuracion)<<std::endl;	
	}

	localizador.inicializar(id_idioma_interface);

	//Último intento de asignar un idioma canónico...
	if(!idioma_canonico.size() && lector.total_idiomas())
	{
		idioma_canonico=lector.acc_idiomas()[0]->acronimo;
	}
}

void CLI::guardar_configuracion()
{
	log<<localizador.obtener(cli_guardando_configuracion)<<std::endl;

	using namespace Herramientas_proyecto;

	Dnot_token::t_mapa mapa_config;
	mapa_config["id_idioma"]=Dnot_token(id_idioma_interface);
	mapa_config["idioma_canonico"]=Dnot_token(idioma_canonico);

	Dnot_token config;
	config.asignar(mapa_config);

	Dnot_token::t_mapa mapa_root;
	mapa_root["cli_config"]=config;

	Dnot_token root;
	root.asignar(mapa_root);

	std::ofstream salida(ruta_configuracion_cli.c_str());
	salida<<root.serializar();
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
			case 't': menu_etiquetas(); break;
			case 'w': menu_palabras(); break;
			case 'y': menu_sistema(); break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
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

/******************************************************************************/

void CLI::menu_idiomas()
{
	std::map<int, std::string> opciones;

	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_idiomas);

		if(seleccion_actual.size())
		{
			try
			{			
				const auto& i=lector.obtener_idioma(seleccion_actual);
				std::cout<<std::endl<<std::endl<<localizador.obtener(cli_seleccion_actual)<<i.nombre<<std::endl;
			}
			catch(Lector_excepcion& e)
			{
				seleccion_actual="";
			}
		}

		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': return; break;
			case 'l': listar_idiomas(opciones); break;
			case 'f': buscar_idiomas(opciones); break;
			case 'n': nuevo_idioma(); break;
			case 'c': seleccionar_actual(opciones); break;
			case 'e': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else
					modificar_idioma(lector.obtener_idioma(seleccion_actual)); 
			break;
			case 'd': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else
					eliminar_idioma(lector.obtener_idioma(seleccion_actual)); 
			break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::listar_idiomas(std::map<int, std::string>& opciones)
{
	std::cout<<localizador.obtener(cli_listado_idiomas);
	const auto& v=lector.acc_idiomas();
	mostrar_lista_idiomas(v, opciones);
}

void CLI::buscar_idiomas(std::map<int, std::string>& opciones)
{
	std::string buscar;

	if(input_string(buscar, localizador.obtener(cli_buscar_idiomas) ) )
	{
		const auto& v=lector.buscar_idiomas([&buscar](const Idioma& I) {return I.nombre.find(buscar)!=std::string::npos;});
		std::cout<<localizador.obtener(cli_resultados_buscador)<<v.size()<<std::endl;
		mostrar_lista_idiomas(v, opciones);
	}
}

void CLI::mostrar_lista_idiomas(const std::vector<Idioma const *>& v, std::map<int, std::string>& opciones)
{
	opciones.clear();
	int opcion=1;

	for(const auto& i : v)
	{
		const auto& I=*i;
		opciones[opcion]=I.acronimo;
		std::cout<<"["<<opcion<<"] : "<<I.nombre<<" ("<<I.acronimo<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl;
}

void CLI::modificar_idioma(Idioma& I)
{
	std::string nombre;
	if(input_string(nombre, localizador.obtener(cli_modificar_idioma)))
	{
		I.nombre=nombre;
		cambios_guardados=false;
	}
}

void CLI::eliminar_idioma(Idioma& I)
{
	const std::string acr=I.acronimo;
	lector.eliminar_idioma(acr);
	std::cout<<localizador.obtener(cli_idioma_eliminado)<<std::endl;
	cambios_guardados=false;

	if(idioma_canonico==acr) idioma_canonico="";
	seleccion_actual="";
}

void CLI::nuevo_idioma()
{
	std::cout<<localizador.obtener(cli_nuevo_idioma);
	std::string nombre, acronimo;

	if(input_string(nombre, localizador.obtener(cli_nuevo_idioma_nombre)) &&
		input_string(acronimo, localizador.obtener(cli_nuevo_idioma_acronimo) ) )
	{
		try
		{
			Idioma idioma{acronimo, nombre};
			lector.insertar_idioma(idioma);
			cambios_guardados=false;
			if(!idioma_canonico.size()) idioma_canonico=acronimo;
			seleccion_actual=acronimo;
		}
		catch(Lector_excepcion& e)
		{
			std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
		}
	}
}

/******************************************************************************/

void CLI::menu_etiquetas()
{
	std::map<int, std::string> opciones;

	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_etiquetas);

		if(seleccion_actual.size())
		{
			try
			{
				const auto& info=info_etiqueta(lector.obtener_etiqueta(seleccion_actual));
				std::cout<<std::endl<<std::endl<<localizador.obtener(cli_seleccion_actual)<<info.nombre<<" ["<<info.clave<<"]"<<std::endl;
			}
			catch(Lector_excepcion& e)
			{
				seleccion_actual="";
			}
		}

		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': return; break;
			case 'l': listar_etiquetas(opciones); break;
			case 'f': buscar_etiquetas(opciones); break;
			case 'n': nueva_etiqueta(); break;
			case 'c': seleccionar_actual(opciones); break;
			case 'e': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else 
					modificar_etiqueta(lector.obtener_etiqueta(seleccion_actual)); 
			break;
			case 'd': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else 
					eliminar_etiqueta(lector.obtener_etiqueta(seleccion_actual)); 
			break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::listar_etiquetas(std::map<int, std::string>& opciones)
{
	std::cout<<localizador.obtener(cli_listado_etiquetas);
	const auto& v=lector.acc_etiquetas();
	mostrar_lista_etiquetas(v, opciones);
}

void CLI::buscar_etiquetas(std::map<int, std::string>& opciones)
{
	std::string buscar;

	if(input_string(buscar, localizador.obtener(cli_buscar_etiquetas) ) )
	{
		const auto& v=lector.buscar_etiquetas([&buscar](const Etiqueta_bruto& E) 
		{
			for(const auto& n : E.nombres)
				if(n.second.find(buscar)!=std::string::npos) return true;

			return false;
		});
		std::cout<<localizador.obtener(cli_resultados_buscador)<<v.size()<<std::endl;
		mostrar_lista_etiquetas(v, opciones);
	}
}

void CLI::nueva_etiqueta()
{
	std::string clave;

	if(input_string(clave, localizador.obtener(cli_nueva_etiqueta)))
	{
		mapa_traducciones traducciones;

		if(rellenar_mapa_traducciones(cli_nueva_etiqueta_traduccion, traducciones))
		{	
			try
			{
				Etiqueta_bruto etiqueta{clave};
				for(const auto& p : traducciones) if(p.second!="-") etiqueta.nombres[p.first]=p.second;
				lector.insertar_etiqueta(etiqueta);
				cambios_guardados=false;
				seleccion_actual=clave;
			}
			catch(Lector_excepcion& e)
			{
				std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
			}
		}
	}
}

void CLI::modificar_etiqueta(Etiqueta_bruto& E)
{
	mapa_traducciones traducciones;
	if(rellenar_mapa_traducciones(cli_nueva_etiqueta_traduccion, traducciones, E.nombres))
	{
		try
		{
			for(const auto& p : traducciones) if(p.second!="-") E.nombres[p.first]=p.second;
			cambios_guardados=false;
		}
		catch(Lector_excepcion& e)
		{
			std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
		}
	}
}

void CLI::eliminar_etiqueta(Etiqueta_bruto& E)
{
	lector.eliminar_etiqueta(E.clave);
	std::cout<<localizador.obtener(cli_etiqueta_eliminada)<<std::endl;
	cambios_guardados=false;
	seleccion_actual="";
}

void CLI::mostrar_lista_etiquetas(const std::vector<Etiqueta_bruto const *>& v, std::map<int, std::string>& opciones)
{
	opciones.clear();
	int opcion=1;

	for(const auto& i : v)
	{
		const auto& info=info_etiqueta(*i);
		opciones[opcion]=i->clave;
		std::cout<<"["<<opcion<<"] : "<<info.nombre<<" ("<<info.clave<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl;
}
 
void CLI::mostrar_lista_etiquetas(const std::vector<Etiqueta_bruto const *>& v, std::map<int, std::string>& opciones, const Palabra_bruto& P)
{
	opciones.clear();
	int opcion=1;

	for(const auto& i : v)
	{
		const std::string marca=std::find(std::begin(P.etiquetas), std::end(P.etiquetas), i)!=std::end(P.etiquetas) ? marcado : no_marcado;

		const auto& info=info_etiqueta(*i);
		opciones[opcion]=i->clave;
		std::cout<<"["<<opcion<<"] : ["<<marca<<"] "<<info.nombre<<" ("<<info.clave<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl;
}

void CLI::mostrar_lista_etiquetas(const std::vector<Etiqueta_bruto const *>& v, std::map<int, std::string>& opciones, const std::vector<Etiqueta_bruto const *>& autoetiquetado)
{
	opciones.clear();
	int opcion=1;
	size_t total=0;

	for(const auto& i : v)
	{
		auto it=std::find(std::begin(autoetiquetado), std::end(autoetiquetado), i);

		const std::string marca=it!=std::end(autoetiquetado) ? marcado : no_marcado;
		if(it!=std::end(autoetiquetado)) ++total;

		const auto& info=info_etiqueta(*i);
		opciones[opcion]=i->clave;
		std::cout<<"["<<opcion<<"] : ["<<marca<<"] "<<info.nombre<<" ("<<info.clave<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl<<localizador.obtener(cli_total_autoetiquetado)<<total<<std::endl;
}

/******************************************************************************/

void CLI::menu_palabras()
{
	std::map<int, std::string> opciones;
	std::vector<Etiqueta_bruto const *> autoetiquetas;


	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_palabras);

		if(seleccion_actual.size())
		{
			try
			{
				const auto& info=info_palabra(lector.obtener_palabra(seleccion_actual));
				std::cout<<std::endl<<std::endl<<localizador.obtener(cli_seleccion_actual)<<info.traduccion<<" ["<<info.japones<<" - "<<info.romaji<<"]"<<std::endl;
			}
			catch(Lector_excepcion& e)
			{
				seleccion_actual="";
			}
		}

		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': return; break;
			case 'l': listar_palabras(opciones); break;
			case 'f': buscar_palabras(opciones); break;
			case 'q': buscar_palabras_etiqueta(opciones); break;
			case 'n': nueva_palabra(autoetiquetas); break;
			case 'c': seleccionar_actual(opciones); break;
			case 'e': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else
					modificar_palabra(lector.obtener_palabra(seleccion_actual)); 
			break;
			case 't': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else 
					etiquetar_palabra(lector.obtener_palabra(seleccion_actual)); 
			break;
			case 'd': 
				if(!seleccion_actual.size())
					std::cout<<localizador.obtener(cli_sin_seleccion_actual)<<std::endl;
				else 
					eliminar_palabra(lector.obtener_palabra(seleccion_actual)); 
			break;
			case 'a': seleccion_autoetiquetado_palabras(autoetiquetas); break;				
			break;
			case 's': guardar(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::seleccion_autoetiquetado_palabras(std::vector<Etiqueta_bruto const *>& autoetiquetado)
{
	//Mostrar listado de etiquetas, 
	std::map<int, std::string> opciones_et;
	const auto& v=lector.acc_etiquetas();

	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_autoetiquetado)<<std::endl;
		mostrar_lista_etiquetas(v, opciones_et, autoetiquetado);

		std::string input;
		if(!input_string(input, ""))
		{
			return;
		}
		else
		{
			try
			{
				int s=std::stoi(input);
				if(!s) 
				{
					return;
				}		
				if(opciones_et.count(s)) 
				{
					const auto& et=lector.obtener_etiqueta(opciones_et[s]);
					const auto it=std::find(std::begin(autoetiquetado), std::end(autoetiquetado), &et);

					if(it == std::end(autoetiquetado))
					{
						autoetiquetado.push_back(&et);
						std::cout<<localizador.obtener(cli_autoetiquetado_insertado)<<std::endl;
					}
					else
					{
						autoetiquetado.erase(it);
						std::cout<<localizador.obtener(cli_autoetiquetado_retirado)<<std::endl;
					}

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

void CLI::listar_palabras(std::map<int, std::string>& opciones)
{
	std::cout<<localizador.obtener(cli_listado_palabras);
	const auto& v=lector.acc_palabras();
	mostrar_lista_palabras(v, opciones);
}

void CLI::buscar_palabras(std::map<int, std::string>& opciones)
{
	std::string buscar;
	if(input_string(buscar, localizador.obtener(cli_buscar_palabras) ) )
	{
		const auto& v=lector.buscar_palabras([&buscar](const Palabra_bruto& P) 
		{
			if(P.romaji.find(buscar)!=std::string::npos) return true;
			for(const auto& p : P.traducciones) 
				if(p.second.find(buscar)!=std::string::npos) return true;

			return false;
		});
		std::cout<<localizador.obtener(cli_resultados_buscador)<<v.size()<<std::endl;
		mostrar_lista_palabras(v, opciones);
	}
}

void CLI::buscar_palabras_etiqueta(std::map<int, std::string>& opciones)
{
	//Mostrar primero menú de etiquetas...

	std::map<int, std::string> opciones_et;
	int etiqueta_seleccionada=0;

	while(true)
	{
		std::cout<<localizador.obtener(cli_buscar_palabras_etiqueta);
		const auto& v=lector.acc_etiquetas();
		mostrar_lista_etiquetas(v, opciones_et);

		std::string input;
		if(input_string(input, ""))
		{
			try
			{
				int s=std::stoi(input);
				if(!s)
				{
					return;
				}
				if(opciones_et.count(s)) 
				{
					etiqueta_seleccionada=s;
					break;
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

	//Y ahora hacer la búsqueda...
	const auto& E=lector.obtener_etiqueta(opciones_et[etiqueta_seleccionada]);
	const auto& v=lector.buscar_palabras([&E](const Palabra_bruto& P) 
		{
			return std::find(std::begin(P.etiquetas), std::end(P.etiquetas), &E)!=std::end(P.etiquetas);
		});

	std::cout<<localizador.obtener(cli_resultados_buscador)<<v.size()<<std::endl;
	mostrar_lista_palabras(v, opciones);
}


void CLI::nueva_palabra(const std::vector<Etiqueta_bruto const *>& autoetiquetas)
{
	std::string japones, romaji;

	if(autoetiquetas.size())
	{
		std::cout<<localizador.obtener(cli_autoetiquetas_activas)<<std::endl;
		for(const auto& e : autoetiquetas)
		{
			const auto& info=info_etiqueta(*e);
			std::cout<<info.nombre<<" ";
		}

		std::cout<<std::endl;
	}

	if(input_string(japones, localizador.obtener(cli_nueva_palabra_japones))
		&& input_string(romaji, localizador.obtener(cli_nueva_palabra_romaji)))
	{
		mapa_traducciones traducciones;
		if(rellenar_mapa_traducciones(cli_nueva_palabra_traduccion, traducciones))
		{	
			try
			{
				Palabra_bruto palabra{japones, romaji};
				for(const auto& p : traducciones) if(p.second!="-") palabra.traducciones[p.first]=p.second;
				for(const auto& e : autoetiquetas) palabra.etiquetas.push_back(e);
				lector.insertar_palabra(palabra);

				cambios_guardados=false;
				seleccion_actual=japones;
			}
			catch(Lector_excepcion& e)
			{
				std::cout<<localizador.obtener(cli_fallo_operacion)<<" - "<<e.what()<<std::endl;
			}
		}
	}
}

void CLI::modificar_palabra(Palabra_bruto& P)
{
	mapa_traducciones traducciones;
	std::string romaji;

	if(input_string(romaji, localizador.obtener(cli_modificar_palabra_romaji)+" ("+P.romaji+")")
		&& rellenar_mapa_traducciones(cli_nueva_etiqueta_traduccion, traducciones, P.traducciones))
	{
		if(romaji!="-") P.romaji=romaji;
		for(const auto& p : traducciones) if(p.second!="-") P.traducciones[p.first]=p.second;
		cambios_guardados=false;
	}
}

void CLI::etiquetar_palabra(Palabra_bruto& P)
{
	std::map<int, std::string> opciones;

	while(true)
	{
		std::cout<<localizador.obtener(cli_etiquetar_palabra);
		const auto& v=lector.acc_etiquetas();
		mostrar_lista_etiquetas(v, opciones, P);

		std::string input;
		if(input_string(input, ""))
		{
			try
			{
				int s=std::stoi(input);
				if(!s)
				{
					return;
				}
				if(opciones.count(s)) 
				{
					const auto& etiqueta=lector.obtener_etiqueta(opciones[s]);
					auto it=std::find(std::begin(P.etiquetas), std::end(P.etiquetas), &etiqueta);
					if(it==std::end(P.etiquetas))
					{
	 					P.etiquetas.push_back(&etiqueta);
						std::cout<<localizador.obtener(cli_etiquetar_palabra_etiquetada)<<std::endl;
					}
					else
					{
	 					P.etiquetas.erase(it);
						std::cout<<localizador.obtener(cli_etiquetar_palabra_eliminada)<<std::endl;
					}
					cambios_guardados=false;
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

void CLI::eliminar_palabra(Palabra_bruto& P)
{
	lector.eliminar_palabra(P.japones);
	std::cout<<localizador.obtener(cli_palabra_eliminada)<<std::endl;
	cambios_guardados=false;
	seleccion_actual="";
}

void CLI::mostrar_lista_palabras(const std::vector<Palabra_bruto const *>& v, std::map<int, std::string>& opciones)
{
	opciones.clear();
	int opcion=1;

	for(const auto& i : v)
	{
		const auto& info=info_palabra(*i);
		opciones[opcion]=i->japones;
		std::cout<<"["<<opcion<<"] : "<<info.traduccion<<" ("<<info.japones<<" - "<<info.romaji<<")"<<std::endl;
		++opcion;
	}

	std::cout<<std::endl;
}

/******************************************************************************/

void CLI::menu_sistema()
{
	std::map<int, std::string> opciones;

	while(true)
	{
		std::cout<<localizador.obtener(cli_menu_sistema);

		char opcion=obtener_entrada_char();
		switch(opcion)
		{
			case '0': return; break;
			case 'l': seleccion_idioma_canonico(); break;
			case 'i': seleccion_idioma_interface(); break;
			default: 
				std::cout<<localizador.obtener(cli_opcion_incorrecta)<<std::endl;
			break;
		}
	}
}

void CLI::seleccion_idioma_canonico()
{
	std::map<int, std::string> opciones;

	while(true)
	{
		std::cout<<localizador.obtener(cli_idioma_canonico);
		mostrar_lista_idiomas(lector.acc_idiomas(), opciones);

		std::string input;
		if(input_string(input, ""))
		{
			try
			{
				int s=std::stoi(input);
				if(!s)
				{
					return;
				}
				if(opciones.count(s)) 
				{
					idioma_canonico=opciones[s];
					guardar_configuracion();
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

void CLI::seleccion_idioma_interface()
{
	while(true)
	{
		std::cout<<localizador.obtener(cli_idioma_interface);
		
		for(const auto& p : mapa_idiomas)
			std::cout<<"["<<p.first<<"] - "<<p.second<<std::endl;

		std::string input;
		if(input_string(input, ""))
		{
			try
			{
				int s=std::stoi(input);
				if(mapa_idiomas.count(s)) 
				{
					id_idioma_interface=s;
					guardar_configuracion();
					localizador.inicializar(id_idioma_interface);
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

/******************************************************************************/

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

char CLI::obtener_entrada_char(bool permitir_vacio)
{
	while(true)
	{
		std::cout<<"\n>>";
		std::string input;
		std::getline(std::cin, input);
		if(input.size()==1) return input[0];
		else if(!input.size() && permitir_vacio) return '\0';
		else std::cout<<localizador.obtener(cli_opcion_char)<<std::endl;
	}
}

std::string CLI::obtener_entrada_string(bool permitir_vacio)
{
	while(true)
	{
		std::cout<<"\n>>";
		std::string input;
		std::getline(std::cin, input);
		if(input.size()) return input;
		else if(!input.size() && permitir_vacio) return "";
		else std::cout<<localizador.obtener(cli_opcion_string)<<std::endl;
	}
}

void CLI::seleccionar_actual(std::map<int, std::string>& opciones)
{
	if(!opciones.size())
	{
		std::cout<<localizador.obtener(cli_seleccion_vacia)<<std::endl;
		return;
	}
	
	while(true)
	{
		std::string input;
		if(input_string(input, localizador.obtener(cli_menu_seleccion)))
		{
			try
			{
				int s=std::stoi(input);
	
				if(opciones.count(s)) 
				{
					seleccion_actual=opciones[s];
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

CLI::mostrar_etiqueta CLI::info_etiqueta(const Etiqueta_bruto& et)
{
	const std::string nombre=et.nombres.count(idioma_canonico) ? 
		et.nombres.at(idioma_canonico) : 
		localizador.obtener(cli_sin_traduccion);
	return mostrar_etiqueta{et.clave, nombre};

}

CLI::mostrar_palabra CLI::info_palabra(const Palabra_bruto& p)
{
	const std::string traduccion=p.traducciones.count(idioma_canonico) ? 
		p.traducciones.at(idioma_canonico) : 
		localizador.obtener(cli_sin_traduccion);
	return mostrar_palabra{p.japones, p.romaji, traduccion};
}

bool CLI::input_string(std::string& in, const std::string& msj)
{
	std::cout<<msj<<std::endl;
	in=obtener_entrada_string(true);

	if(in.size()) 
	{
		return true;
	}
	else
	{
		std::cout<<localizador.obtener(cli_accion_cancelada)<<std::endl;
		return false;
	}
}

bool CLI::rellenar_mapa_traducciones(int cod, std::map<std::string, std::string>& traducciones)
{
	const auto& v=lector.acc_idiomas();
	for(const auto& i : v)
	{
		const std::string& acr=i->acronimo;
		traducciones[acr]="-";
		if(!input_string(traducciones.at(acr), acr+localizador.obtener(cli_nueva_etiqueta_traduccion)))
			return false;
	}

	return true;
}

bool CLI::rellenar_mapa_traducciones(int cod, mapa_traducciones& traducciones, const mapa_traducciones& originales)
{
	const auto& v=lector.acc_idiomas();
	for(const auto& i : v) 
	{
		const std::string& acr=i->acronimo;
		traducciones[acr]="-";
		std::string original=originales.count(acr) ? originales.at(acr) : localizador.obtener(cli_sin_traduccion);
		if(!input_string(traducciones.at(acr), acr+localizador.obtener(cli_nueva_etiqueta_traduccion)+" ("+original+")"))
			return false;
	}

	return true;
}
