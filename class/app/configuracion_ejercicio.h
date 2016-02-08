#ifndef CONFIGURACION_EJERCICIO_H
#define CONFIGURACION_EJERCICIO_H

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

	void				intercambiar_palabras_limitadas();
	void				sumar_palabras();
	void				restar_palabras();
	void				ciclar_direccion();
	void				ciclar_modo_etiquetas();

	private:

	static const int		min_palabras=5;
	static const int		max_palabras=250;

	bool				palabras_limitadas;
	direcciones			direccion;
	modos_etiquetas			modo_etiquetas;
	int				palabras;
};

void ciclar_direccion(Configuracion_ejercicio::direcciones&);
int localizar_direccion(Configuracion_ejercicio::direcciones);

void ciclar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas&);
int localizar_modo_etiquetas(Configuracion_ejercicio::modos_etiquetas);

}

#endif
