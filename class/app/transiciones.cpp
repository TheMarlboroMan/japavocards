#include "transiciones.h"

using namespace App;

void App::transicion_entrada(Herramientas_proyecto::Compositor_vista& vista, Worker_animacion& worker_animacion)
{
	auto& item=*(vista.obtener_por_id("bloqueador"));
	auto f=[&item](float delta, std::vector<float>& params) -> bool
	{
		auto& val=params[0];
		val-=delta * 255.f;
		if(val <= 0.0f) val=0.0f;
		item.establecer_alpha(val);

		if(!val)
		{
			item.hacer_invisible();
		}

		return !val;
	};

	worker_animacion.registrar(f, {255.0f});
}

void App::transicion_salida_horizontal(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel, float dest)
{
	auto f=[&camara, dest, vel](float delta, std::vector<float>& params) -> bool
	{
		auto& val=params[0];
		val+=delta * vel;
		camara.mut_x(val);

		if(vel < 0.0f) return val <= dest;
		else if(vel > 0.0f) return val >= dest;
		else return true;
	};

	worker_animacion.registrar(f, {(float)camara.acc_x()});
}

void App::transicion_salida_vertical(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel, float dest)
{
	auto f=[&camara, dest, vel](float delta, std::vector<float>& params) -> bool
	{
		auto& val=params[0];
		val+=delta * vel;
		camara.mut_y(val);
		if(vel < 0.0f) return val <= dest;
		else if(vel > 0.0f) return val >= dest;
		else return true;
	};

	worker_animacion.registrar(f, {(float)camara.acc_y()});
}
