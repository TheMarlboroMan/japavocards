#include <libDan2.h>
#include <defDanSDL.h>
#include "class/framework/kernel.h"
//#include "class/app/framework_impl/app_kernel_config.h"
//#include "class/app/framework_impl/app_config.h"
//#include "class/controladores/director_estados.h"

//Declaración del log de aplicación en espacio global.
DLibH::Log_base LOG;

int main(int argc, char ** argv)
{
	//Inicializar control de logs.
	LOG.inicializar("logs/info.log");
	LOG.activar();
	DLibH::Log_motor::arrancar("logs/log_motor.log");

	//Inicializar control de argumentos.
	Herramientas_proyecto::Controlador_argumentos CARG(argc, argv);

/*
	if(DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK))
	{


		try
		{
			App::App_kernel_config AKC;

			App::App_config config;
			config.cargar();

			DFramework::Kernel kernel(CARG, AKC, config);

			App::Director_estados APP(kernel, config);
			APP.iniciar(kernel);
		}
		catch(std::exception &e)
		{
			std::cout<<"Saliendo: se atraṕo una excepción : "<<e.what()<<std::endl;
		}
	}

	DLibH::Herramientas_SDL::apagar_SDL();
*/
	
	DLibH::Log_motor::finalizar();
	return 0;
}
