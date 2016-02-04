#ifndef GENERADOR_LISTADOS_H
#define GENERADOR_LISTADOS_H

#include <video/representacion/representacion_agrupada/representacion_agrupada.h>
#include <class/listado_vertical.h>

/**
* Conjunto de helpers para generar listados verticales. Dejamos el algoritmo en 
* generar_vista_listado y creamos la interface Listable que, aunque no hace
* falta, está ahí para implementarla.
*/

namespace App
{
struct Listable
{
	virtual void generar_representacion_listado(DLibV::Representacion_agrupada& rep, int x, int y) const=0;
};

template <typename T>
void generar_vista_listado(Herramientas_proyecto::Listado_vertical<T>& listado, DLibV::Representacion_agrupada& rep, int x_listado, int y_listado)
{
	rep.vaciar_grupo();
	const auto pagina=listado.obtener_pagina();
	for(const auto& itemp : pagina) 
	{
		itemp.item.generar_representacion_listado(rep, x_listado, itemp.y + y_listado);
	}
}

}

#endif
