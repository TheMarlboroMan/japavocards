#ifndef FILTRO_PALABRAS_H
#define FILTRO_PALABRAS_H

/**
* La única responsabilidad de esta clase es recibir un array de palabras y 
* etiquetas y filtrar las palabras. Hará cosas como "todas las palabras",
* "palabras etiquetadas con estas etiquetas" o "palabras" no etiquetadas.
*/

#include <vector>

#include "palabra.h"
#include "etiqueta.h"

namespace App
{

std::vector<Palabra const *> 		filtrar_todas(const std::vector<Palabra>&);
std::vector<Palabra const *>		filtrar_sin_etiquetar(const std::vector<Palabra>&);
std::vector<Palabra const *>		filtrar_etiquetadas(const std::vector<Palabra>&, const std::vector<Etiqueta const *>&);

}

#endif
