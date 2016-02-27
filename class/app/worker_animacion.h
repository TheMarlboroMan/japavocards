#ifndef WORKER_ANIMACION_H
#define WORKER_ANIMACION_H

#include <functional>
#include <vector>

/* 
Cada una de las funciones hace un bind de la función en si y de los argumentos
que necesita.
*/

namespace App
{

class Worker_animacion
{
	public:

	typedef std::vector<float> params;
	typedef std::function<bool(float, params&)> funcion;

	struct parte
	{
		funcion f;
		params p;				
	};
	
	bool			es_activo() const {return funciones.size();} 
	void			registrar(funcion f, params p) {funciones.push_back({f, p});}
	void			turno(float d)
	{
		auto ini=funciones.begin();

		while(ini < funciones.end())
		{
			auto &p=*ini;
			if(p.f(d, p.p))
			{
				ini=funciones.erase(ini);
			}
			++ini;
		}
	}

	void			finalizar() {funciones.clear();}
	size_t			size() const {return funciones.size();}

	private:

	std::vector<parte> funciones;
	
};

}
#endif
