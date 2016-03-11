#include "app_config.h"

using namespace App;

const std::string App_config::CLAVE_IDIOMA_INTERFACE="config:app:idioma_interface";
const std::string App_config::CLAVE_IDIOMA_BASE_DATOS="config:app:idioma";
const std::string App_config::CLAVE_MODO_ETIQUETAS="config:app:modo_etiquetas";
const std::string App_config::CLAVE_DIRECCION="config:app:direccion";
const std::string App_config::CLAVE_PALABRAS="config:app:palabras";
const std::string App_config::CLAVE_ETIQUETAS="config:app:etiquetas";
const std::string App_config::CLAVE_PALABRAS_LIMITADAS="config:app:palabras_limitadas";
const std::string App_config::CLAVE_W_FISICA_PANTALLA="config:video:w_fisica_ventana";
const std::string App_config::CLAVE_H_FISICA_PANTALLA="config:video:h_fisica_ventana";
const std::string App_config::CLAVE_W_LOGICA_PANTALLA="config:video:w_logica_ventana";
const std::string App_config::CLAVE_H_LOGICA_PANTALLA="config:video:h_logica_ventana";

const std::string App_config::CLAVE_INPUT_ACEPTAR="config:input:aceptar";
const std::string App_config::CLAVE_INPUT_ESCAPE="config:input:escape";
const std::string App_config::CLAVE_INPUT_IZQUIERDA="config:input:izquierda";
const std::string App_config::CLAVE_INPUT_DERECHA="config:input:derecha";
const std::string App_config::CLAVE_INPUT_ARRIBA="config:input:arriba";
const std::string App_config::CLAVE_INPUT_ABAJO="config:input:abajo";
const std::string App_config::CLAVE_INPUT_PAG_SIGUIENTE="config:input:pag_siguiente";
const std::string App_config::CLAVE_INPUT_PAG_ANTERIOR="config:input:pag_anterior";

App_config::App_config(): Configuracion_base(obtener_ruta_archivo())
{

}

std::vector<std::string> App_config::acc_etiquetas() const
{
	std::vector<std::string> res;
	const auto& tok=token_por_ruta(CLAVE_ETIQUETAS);
	const auto& v=tok.acc_lista();
	for(const auto& s : v) res.push_back(s.acc_string());
	return res;
}

void App_config::mut_etiquetas(const std::vector<std::string>& e)
{
	using namespace Herramientas_proyecto;
	Dnot_token::t_vector v;
	for(const auto& s : e) v.push_back(Dnot_token(s));
	configurar(CLAVE_ETIQUETAS, v);
}
