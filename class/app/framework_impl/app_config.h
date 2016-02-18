#ifndef APP_CONFIGURACION_H
#define APP_CONFIGURACION_H

#include "../../framework/configuracion_base.h"

#include <iostream>

namespace App
{

class App_config:
	public DFramework::Configuracion_base
{
	////////////////////////////////
	// Interface pública.

	public:

	bool acc_palabras_limitadas() const {return token_por_ruta(CLAVE_PALABRAS_LIMITADAS);}
	int acc_idioma_interface() const {return token_por_ruta(CLAVE_IDIOMA_INTERFACE);}
	int acc_palabras() const {return token_por_ruta(CLAVE_PALABRAS);}
	std::string acc_idioma_base_datos() const {return token_por_ruta(CLAVE_IDIOMA_BASE_DATOS);}
	std::string acc_modo_etiquetas() const {return token_por_ruta(CLAVE_MODO_ETIQUETAS);}
	std::string acc_direccion() const {return token_por_ruta(CLAVE_DIRECCION);}
	int acc_w_logica_pantalla() const {return token_por_ruta(CLAVE_W_LOGICA_PANTALLA);}
	int acc_h_logica_pantalla() const {return token_por_ruta(CLAVE_H_LOGICA_PANTALLA);}
	int acc_w_fisica_pantalla() const {return token_por_ruta(CLAVE_W_FISICA_PANTALLA);}
	int acc_h_fisica_pantalla() const {return token_por_ruta(CLAVE_H_FISICA_PANTALLA);}
	std::vector<std::string> acc_etiquetas() const;

	void mut_palabras_limitadas(bool p_valor) {configurar(CLAVE_PALABRAS_LIMITADAS, p_valor);}
	void mut_palabras(int p_valor) {configurar(CLAVE_PALABRAS, p_valor);}
	void mut_idioma_interface(int p_valor) {configurar(CLAVE_IDIOMA_INTERFACE, p_valor);}
	void mut_idioma_base_datos(const std::string& p_valor) {configurar(CLAVE_IDIOMA_BASE_DATOS, p_valor);}
	void mut_modo_etiquetas(const std::string& p_valor) {configurar(CLAVE_MODO_ETIQUETAS, p_valor);}
	void mut_direccion(const std::string& p_valor) {configurar(CLAVE_DIRECCION, p_valor);}
	void mut_w_logica_pantalla(int p_valor) {configurar(CLAVE_W_LOGICA_PANTALLA, p_valor);}
	void mut_h_logica_pantalla(int p_valor) {configurar(CLAVE_H_LOGICA_PANTALLA, p_valor);}
	void mut_w_fisica_pantalla(int p_valor) {configurar(CLAVE_W_FISICA_PANTALLA, p_valor);}
	void mut_h_fisica_pantalla(int p_valor) {configurar(CLAVE_H_FISICA_PANTALLA, p_valor);}
	void mut_etiquetas(const std::vector<std::string>&);

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
	static const std::string CLAVE_MODO_ETIQUETAS;
	static const std::string CLAVE_DIRECCION;
	static const std::string CLAVE_PALABRAS;
	static const std::string CLAVE_PALABRAS_LIMITADAS;
	static const std::string CLAVE_ETIQUETAS;

	////////////////////////////////////
	// Implementacion...

	protected: 

	std::string obtener_clave_version_archivo() const {return "config:meta:v";}
	std::string obtener_version_archivo() const {return "1";}
	std::string obtener_clave_modo_pantalla() const {return "config:video:modo_pantalla";}
	std::string obtener_clave_modo_hardware() const {return "config:video:modo_hardware";}
	std::string obtener_clave_pantalla_doble_buffer() const {return "config:video:doble_buffer";}
	std::string obtener_clave_pantalla_anyformat() const {return "config:video:pantalla_anyformat";}
	std::string obtener_clave_volumen_audio() const {return "config:audio:volumen_audio";}
	std::string obtener_clave_volumen_musica() const {return "config:audio:volumen_musica";}
	std::string obtener_clave_audio_ratio() const {return "config:audio:audio_ratio";}
	std::string obtener_clave_audio_buffers() const {return "config:audio:audio_buffers";}
	std::string obtener_clave_audio_salidas() const {return "config:audio:audio_salidas";}
	std::string obtener_clave_audio_canales() const {return "config:audio:audio_canales";}

	///////////////////////////////////
	// Propiedades.

	private:

	std::string obtener_ruta_archivo() const {return "data/config/configuracion.dnot";}
};

}
#endif
