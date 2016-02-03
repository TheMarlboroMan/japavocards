#ifndef APP_CONFIGURACION_H
#define APP_CONFIGURACION_H

#include "../../framework/configuracion_base.h"

namespace App
{

class App_config:
	public DFramework::Configuracion_base
{
	////////////////////////////////
	// Interface pública.

	public:

	int acc_idioma_interface() const {return std::atoi(valor_configuracion(CLAVE_IDIOMA_INTERFACE).c_str());}
	std::string acc_idioma_base_datos() const {return valor_configuracion(CLAVE_IDIOMA_BASE_DATOS);}
	int acc_w_logica_pantalla() const {return std::atoi(valor_configuracion(CLAVE_W_LOGICA_PANTALLA).c_str());}
	int acc_h_logica_pantalla() const {return std::atoi(valor_configuracion(CLAVE_H_LOGICA_PANTALLA).c_str());}
	int acc_w_fisica_pantalla() const {return std::atoi(valor_configuracion(CLAVE_W_FISICA_PANTALLA).c_str());}
	int acc_h_fisica_pantalla() const {return std::atoi(valor_configuracion(CLAVE_H_FISICA_PANTALLA).c_str());}

	void mut_idioma_interface(int p_valor) {configurar(CLAVE_IDIOMA_INTERFACE, p_valor);}
	void mut_idioma_base_datos(const std::string& p_valor) {configurar(CLAVE_IDIOMA_BASE_DATOS, p_valor);}
	void mut_w_logica_pantalla(int p_valor) {configurar(CLAVE_W_LOGICA_PANTALLA, p_valor);}
	void mut_h_logica_pantalla(int p_valor) {configurar(CLAVE_H_LOGICA_PANTALLA, p_valor);}
	void mut_w_fisica_pantalla(int p_valor) {configurar(CLAVE_W_FISICA_PANTALLA, p_valor);}
	void mut_h_fisica_pantalla(int p_valor) {configurar(CLAVE_H_FISICA_PANTALLA, p_valor);}

	App_config();

	private:
	
	////////////////////////////////////
	// Definiciones...

	static const std::string CLAVE_IDIOMA_INTERFACE;
	static const std::string CLAVE_IDIOMA_BASE_DATOS;
	static const std::string CLAVE_W_LOGICA_PANTALLA;
	static const std::string CLAVE_H_LOGICA_PANTALLA;
	static const std::string CLAVE_W_FISICA_PANTALLA;
	static const std::string CLAVE_H_FISICA_PANTALLA;

	static const std::string IDIOMA_INTERFACE;
	static const std::string IDIOMA_BASE_DATOS;
	static const std::string W_FISICA_PANTALLA;
	static const std::string H_FISICA_PANTALLA;
	static const std::string W_LOGICA_PANTALLA;
	static const std::string H_LOGICA_PANTALLA;

	////////////////////////////////////
	// Implementacion...

	protected: 

	std::string obtener_clave_version_archivo() const {return "v";}
	std::string obtener_version_archivo() const {return "1";}
	std::string obtener_clave_modo_pantalla() const {return "modo_pantalla";}
	std::string obtener_clave_modo_hardware() const {return "modo_hardware";}
	std::string obtener_clave_pantalla_doble_buffer() const {return "doble_buffer";}
	std::string obtener_clave_pantalla_anyformat() const {return "pantalla_anyformat";}
	std::string obtener_clave_volumen_audio() const {return "volumen_audio";}
	std::string obtener_clave_volumen_musica() const {return "volumen_musica";}
	std::string obtener_clave_audio_ratio() const {return "audio_ratio";}
	std::string obtener_clave_audio_buffers() const {return "audio_buffers";}
	std::string obtener_clave_audio_salidas() const {return "audio_salidas";}
	std::string obtener_clave_audio_canales() const {return "audio_canales";}
	int valor_modo_pantalla_defecto() const {return 0;}
	int valor_modo_hardware_defecto() const {return 1;}
	int valor_pantalla_doble_buffer_defecto() const {return 1;}
	int valor_pantalla_anyformat_defecto() const {return 1;}
	int valor_volumen_audio_defecto() const {return 64;}
	int valor_volumen_musica_defecto() const {return 64;}
	int valor_audio_ratio_defecto() const {return 44100;}
	int valor_audio_salidas_defecto() const {return 2;}
	int valor_audio_buffers_defecto() const {return 1024;}
	int valor_audio_canales_defecto() const {return 8;}

	///////////////////////////////////
	// Propiedades.

	private:

	std::string obtener_ruta_archivo() const {return "data/config/configuracion.dat";}
	char obtener_separador_archivo() const {return ':';}
	char obtener_comentario_archivo() const {return '#';}
};

}
#endif
