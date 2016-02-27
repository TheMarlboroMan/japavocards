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

void App::transicion_salida_horizontal(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel)
{
	float dest=vel <= 0.0 ? -camara.acc_caja_foco().w : camara.acc_caja_foco().w;

	auto f=[&camara, dest, vel](float delta, std::vector<float>& params) -> bool
	{
		auto& val=params[0];
		val+=delta * vel;
		camara.mut_x(val);

		if(vel) return abs(val) >= abs(dest);
		else return true;
	};

	worker_animacion.registrar(f, {(float)camara.acc_x()});
}

void App::transicion_salida_vertical(Worker_animacion& worker_animacion, DLibV::Camara& camara, float vel)
{
	float dest=vel <= 0.0 ? -camara.acc_caja_foco().h : camara.acc_caja_foco().h;

	auto f=[&camara, dest, vel](float delta, std::vector<float>& params) -> bool
	{
		auto& val=params[0];
		val+=delta * vel;
		camara.mut_y(val);

		if(vel) return abs(val) >= abs(dest);
		else return true;
	};

	worker_animacion.registrar(f, {(float)camara.acc_y()});
}

void App::animacion_crece(Worker_animacion& worker_animacion, DLibV::Representacion& rep, float fac, float vel)
{
	auto f=[&rep](float delta, std::vector<float>& params) -> bool
	{
		auto& vel=params[0]; //Velocidad de crecimiento en px x seg.
		auto& factor_actual=params[1];
		const auto& factor_max=params[2];	//Factor máximo esperado.
		const auto& x=params[3];
		const auto& y=params[4];
		const auto& w=params[5];
		const auto& h=params[6];	

		factor_actual+=delta * vel;

		//Controlar vuelta...
		if(factor_actual > factor_max)
		{
			factor_actual=factor_max;
			vel=-vel;
		}
		else if(factor_actual < 1.0)
		{
			factor_actual=1.0;
			vel=-vel;
		}

		//Aplicar el factor...
		float 	wa=w * factor_actual,
			ha=h * factor_actual;

		rep.establecer_posicion(x - ( (wa - w) / 2.0f), y - ( (ha - h) / 2.0f), wa, ha);
		return false;
	};

	const auto& p=rep.acc_posicion();
	worker_animacion.registrar(f, {vel, 1.0, fac, (float)p.x, (float)p.y, (float)p.w, (float)p.h});
}
