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

	void			inicializar();
	void			guardar();	

	void			menu_principal();

	void			menu_idiomas();
	void			listar_idiomas();
	void			buscar_idiomas();
	void			nuevo_idioma();
	void			eliminar_idioma();
	void			modificar_idioma();
	void			mostrar_lista_idiomas(const std::vector<Idioma const *>&);

	void			menu_etiquetas();
	void			listar_etiquetas();
	void			buscar_etiquetas();
	void			nueva_etiqueta();
	void			modificar_etiqueta();
	void			eliminar_etiqueta();

	void			seleccionar_actual();
	char			obtener_entrada_char();
	std::string		obtener_entrada_string();

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

		log_iniciando_backup=1000,
		log_iniciando_guardado=1001


	};

	DLibH::Log_base		log;
	std::string		nombre_fichero;
	Localizador		localizador;
	Lector			lector;
	bool			cambios_guardados;
	int			seleccion_actual;
	std::map<int, std::string>	opciones;
	
};

}

#endif
