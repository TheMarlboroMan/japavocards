#ifndef CLI_H
#define CLI_H

#include <string>
#include <iostream>
#include <map>

#include <herramientas/log_base/log_base.h>


#include <source/ficheros_utilidades.h>

#include "datos_bruto.h"
#include "lector.h"
#include "escritor.h"
#include "localizador.h"

namespace App
{

class CLI
{
	public:

				CLI(const std::string&, int id_idioma=1);

	void			loop();
	
	private:

	struct mostrar_etiqueta
	{
		std::string clave, nombre;
	};

	struct mostrar_palabra
	{
		std::string japones, romaji, traduccion;
	};

	mostrar_etiqueta	info_etiqueta(const Etiqueta_bruto&);
	mostrar_palabra		info_palabra(const Palabra_bruto&);

	void			inicializar();
	void			guardar();	

	void			menu_principal();

	void			menu_sistema();
	void			seleccion_idioma_canonico();

	void			menu_idiomas();
	void			listar_idiomas(std::map<int, std::string>&);
	void			buscar_idiomas(std::map<int, std::string>&);
	void			nuevo_idioma();
	void			eliminar_idioma(Idioma&);
	void			modificar_idioma(Idioma&);
	void			mostrar_lista_idiomas(const std::vector<Idioma const *>&, std::map<int, std::string>&);

	void			menu_etiquetas();
	void			listar_etiquetas(std::map<int, std::string>&);
	void			buscar_etiquetas(std::map<int, std::string>&);
	void			nueva_etiqueta();
	void			modificar_etiqueta(Etiqueta_bruto&);
	void			eliminar_etiqueta(Etiqueta_bruto&);
	void			mostrar_lista_etiquetas(const std::vector<Etiqueta_bruto const *>&, std::map<int, std::string>&);
	void			mostrar_lista_etiquetas(const std::vector<Etiqueta_bruto const *>&, std::map<int, std::string>&, const Palabra_bruto&);

	void			menu_palabras();
	void			listar_palabras(std::map<int, std::string>&);
	void			buscar_palabras(std::map<int, std::string>&);
	void			buscar_palabras_etiqueta(std::map<int, std::string>&);
	void			nueva_palabra();
	void			modificar_palabra(Palabra_bruto&);
	void			etiquetar_palabra(Palabra_bruto&);
	void			eliminar_palabra(Palabra_bruto&);
	void			mostrar_lista_palabras(const std::vector<Palabra_bruto const *>&, std::map<int, std::string>&);

	void			seleccionar_actual(std::map<int, std::string>&);
	char			obtener_entrada_char(bool=false);
	std::string		obtener_entrada_string(bool=false);
	bool			input_string(std::string&, const std::string&);

	typedef	std::map<std::string, std::string> mapa_traducciones;
	bool 			rellenar_mapa_traducciones(int cod, mapa_traducciones& traducciones);
	bool 			rellenar_mapa_traducciones(int cod, mapa_traducciones& traducciones, const mapa_traducciones& originales);

	bool			confirmar_salida();

	enum trans_cli
	{
		cli_menu_principal=1,
		cli_confirmar_salida=2,
		cli_menu_seleccion=3,

		cli_menu_idiomas=30,
		cli_listado_idiomas=31,
		cli_buscar_idiomas=32,
		cli_nuevo_idioma=33,
		cli_idioma_eliminado=34,
		cli_modificar_idioma=35,
		cli_nuevo_idioma_nombre=36,
		cli_nuevo_idioma_acronimo=37,

		cli_menu_etiquetas=50,
		cli_listado_etiquetas=51,
		cli_buscar_etiquetas=52,
		cli_nueva_etiqueta=53,
		cli_nueva_etiqueta_traduccion=54,
		cli_etiqueta_eliminada=55,

		cli_menu_palabras=60,
		cli_listado_palabras=61,
		cli_buscar_palabras=62,
		cli_nueva_palabra_japones=63,
		cli_nueva_palabra_romaji=64,
		cli_nueva_palabra_traduccion=65,
		cli_modificar_palabra_romaji=66,
		cli_palabra_eliminada=67,
		cli_etiquetar_palabra=68,
		cli_etiquetar_palabra_etiquetada=69,
		cli_etiquetar_palabra_eliminada=70,
		cli_buscar_palabras_etiqueta=71,

		cli_inicializar_bienvenida=100,
		cli_inicializar_error_lector=101,
		cli_inicializar_sin_fichero=102,
		cli_inicializar_fichero_escogido=103,

		cli_opcion_incorrecta=200,
		cli_opcion_char=201,
		cli_opcion_string=202,
		cli_resultados_buscador=203,
		cli_fallo_operacion=204,
		cli_guardado_finalizado=205,
		cli_error_seleccion=206,
		cli_seleccion_vacia=207,
		cli_error_seleccion_invalida=208,
		cli_seleccion_actual=209,
		cli_sin_seleccion_actual=210,
		cli_error_eliminar=211,
		cli_sin_traduccion=212,
		cli_accion_cancelada=213,

		cli_menu_sistema=500,
		cli_idioma_canonico=501,

		log_iniciando_backup=1000,
		log_iniciando_guardado=1001


	};

	DLibH::Log_base		log;
	std::string		nombre_fichero;
	Localizador		localizador;
	Lector			lector;
	bool			cambios_guardados;
	int			seleccion_actual;
	std::string		idioma_canonico;	
};

}

#endif
