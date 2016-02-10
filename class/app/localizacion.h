#ifndef LOCALIZACION_H
#define LOCALIZACION_H

namespace App
{

struct localizacion
{
	enum config{
		config_japones_a_traduccion=1,
		config_traduccion_a_japones=2,
		config_modo_todas=3,
		config_modo_sin_etiquetar=4,
		config_modo_etiquetadas=5,
		config_limitacion_palabras_si=6, 
		config_limitacion_palabras_no=7,
		config_limitacion_palabras_numero=8  
	};
};

}


#endif
