#ifndef TRANSICIONES_H
#define TRANSICIONES_H

#include <video/camara/camara.h>
#include <class/compositor_vista.h>
#include "worker_animacion.h"

namespace App
{
void transicion_entrada(Herramientas_proyecto::Compositor_vista& vista, Worker_animacion& worker_animacion);
void transicion_salida_horizontal(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel, float dest);
void transicion_salida_vertical(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel, float dest);
}

#endif
