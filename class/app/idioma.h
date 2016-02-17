#ifndef IDIOMA_H
#define IDIOMA_H

#include <string>

namespace App
{

struct Idioma
{
	std::string			acronimo,
					nombre;
	bool 		 		operator<(const Idioma&) const;
};

}
#endif
