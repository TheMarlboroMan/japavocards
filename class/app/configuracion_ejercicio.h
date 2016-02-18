#ifndef CONFIGURACION_EJERCICIO_H
#define CONFIGURACION_EJERCICIO_H

#include <string>

namespace App
{

class Configuracion_ejercicio
{
	public:

	enum class			direcciones{japones_a_traduccion, traduccion_a_japones};
	enum class 			modos_etiquetas{todas, sin_etiquetar, etiquetadas};

					Configuracion_ejercicio();
	
	bool				es_palabras_limitadas() const {return palabras_limitadas;}
	int				acc_palabras() const {return palabras;}
	modos_etiquetas			acc_modo_etiquetas() const {return modo_etiquetas;}
	direcciones			acc_direccion() const {return direccion;}

	void				mut_limitar_palabras(bool v) {palabras_limitadas=v;}
	void				mut_palabras(int v) {palabras=v;}
	void				mut_direccion(direcciones v) {direccion=v;}
	void				mut_modo_etiquetas(modos_etiquetas v) {modo_etiquetas=v;}

	static const int		min_palabras=5;
	static const int		max_palabras=250;

	private:
	
	bool				palabras_limitadas;
	direcciones			direccion;
	modos_etiquetas			modo_etiquetas;
	int				palabras;
};

void cambiar_cantidad_palabras(int& palabras, int dir);

void ciclar_direccion(Configuracion_ejercicio::direcciones&);
int localizar_direccion(Configuracion_ejercicio::direcciones);
std::string direccion_a_string(Configuracion_ejercicio::direcciones);
Configuracion_ejercicio::direcciones string_a_direccion(const std::string&);

void ciclar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas&, int dir);
int localizar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas);
std::string modo_etiquetas_a_string(Configuracion_ejercicio::modos_etiquetas);
Configuracion_ejercicio::modos_etiquetas string_a_modo_etiquetas(const std::string&);

}

#endif
