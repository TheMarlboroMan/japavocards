#include "app_config.h"

using namespace App;

const std::string App_config::CLAVE_IDIOMA_INTERFACE="config:app:idioma_interface";
const std::string App_config::CLAVE_IDIOMA_BASE_DATOS="config:app:idioma";
const std::string App_config::CLAVE_MODO_ETIQUETAS="config:app:modo_etiquetas";
const std::string App_config::CLAVE_DIRECCION="config:app:direccion";
const std::string App_config::CLAVE_PALABRAS="config:app:palabras";
const std::string App_config::CLAVE_PALABRAS_LIMITADAS="config:app:palabras_limitadas";
const std::string App_config::CLAVE_W_FISICA_PANTALLA="config:video:w_fisica_ventana";
const std::string App_config::CLAVE_H_FISICA_PANTALLA="config:video:h_fisica_ventana";
const std::string App_config::CLAVE_W_LOGICA_PANTALLA="config:video:w_logica_ventana";
const std::string App_config::CLAVE_H_LOGICA_PANTALLA="config:video:h_logica_ventana";

const bool App_config::PALABRAS_LIMITADAS=false;
const int App_config::IDIOMA_INTERFACE=0;
const int App_config::PALABRAS=5;
const std::string App_config::IDIOMA_BASE_DATOS="ES";
const std::string App_config::MODO_ETIQUETAS="todas";
const std::string App_config::DIRECCION="desde_japones";
const int App_config::W_FISICA_PANTALLA=800;
const int App_config::H_FISICA_PANTALLA=600;
const int App_config::W_LOGICA_PANTALLA=800;
const int App_config::H_LOGICA_PANTALLA=600;

App_config::App_config(): Configuracion_base(obtener_ruta_archivo())
{
	configurar(CLAVE_IDIOMA_INTERFACE, IDIOMA_INTERFACE);
	configurar(CLAVE_IDIOMA_BASE_DATOS, IDIOMA_BASE_DATOS);
	configurar(CLAVE_MODO_ETIQUETAS, MODO_ETIQUETAS);
	configurar(CLAVE_DIRECCION, DIRECCION);
	configurar(CLAVE_PALABRAS, PALABRAS);
	configurar(CLAVE_PALABRAS_LIMITADAS, PALABRAS_LIMITADAS);
	configurar(CLAVE_W_FISICA_PANTALLA, W_FISICA_PANTALLA);
	configurar(CLAVE_H_FISICA_PANTALLA, H_FISICA_PANTALLA);
	configurar(CLAVE_W_LOGICA_PANTALLA, W_LOGICA_PANTALLA);
	configurar(CLAVE_H_LOGICA_PANTALLA, H_LOGICA_PANTALLA);
}
