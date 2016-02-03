#include "app_config.h"

using namespace App;

const std::string App_config::CLAVE_IDIOMA_INTERFACE="idioma_interface";
const std::string App_config::CLAVE_IDIOMA_BASE_DATOS="idioma_interface";
const std::string App_config::CLAVE_W_FISICA_PANTALLA="w_fisica_ventana";
const std::string App_config::CLAVE_H_FISICA_PANTALLA="h_fisica_ventana";
const std::string App_config::CLAVE_W_LOGICA_PANTALLA="w_logica_ventana";
const std::string App_config::CLAVE_H_LOGICA_PANTALLA="h_logica_ventana";

const std::string App_config::IDIOMA_INTERFACE="0";
const std::string App_config::IDIOMA_BASE_DATOS="ES";
const std::string App_config::W_FISICA_PANTALLA="800";
const std::string App_config::H_FISICA_PANTALLA="600";
const std::string App_config::W_LOGICA_PANTALLA="800";
const std::string App_config::H_LOGICA_PANTALLA="600";

App_config::App_config(): Configuracion_base(obtener_ruta_archivo(), obtener_separador_archivo(), obtener_comentario_archivo())
{
	configurar(CLAVE_IDIOMA_INTERFACE, IDIOMA_INTERFACE);
	configurar(CLAVE_IDIOMA_BASE_DATOS, IDIOMA_BASE_DATOS);
	configurar(CLAVE_W_FISICA_PANTALLA, W_FISICA_PANTALLA);
	configurar(CLAVE_H_FISICA_PANTALLA, H_FISICA_PANTALLA);
	configurar(CLAVE_W_LOGICA_PANTALLA, W_LOGICA_PANTALLA);
	configurar(CLAVE_H_LOGICA_PANTALLA, H_LOGICA_PANTALLA);
}
