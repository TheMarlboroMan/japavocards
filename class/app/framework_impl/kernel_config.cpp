#include "kernel_config.h"
#include <SDL2/SDL.h>
#include "input.h"

using namespace App;

Kernel_config::Kernel_config(const App_config& cfg)
	:config(cfg)
{

}

std::vector<std::string> Kernel_config::obtener_entradas_audio() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/audio.txt"));
}

std::vector<std::string> Kernel_config::obtener_entradas_musica() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/musica.txt"));
}

std::vector<std::string> Kernel_config::obtener_entradas_texturas() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/texturas.txt"));
}

std::vector<std::string> Kernel_config::obtener_entradas_superficies() const
{
	return obtener_entradas_desde_ruta(std::string("data/recursos/superficies.txt"));
}

DFramework::Info_ventana Kernel_config::obtener_info_ventana() const
{
	return DFramework::Info_ventana{600, 200, 600, 200, "JapaVoCards :D!!!", true};
}

std::vector<DFramework::Par_input> Kernel_config::obtener_pares_input() const
{
	using namespace DFramework;

	std::vector<Par_input> res{
		Par_input{Par_input::tipos::teclado, Input::escape, config.acc_input_escape()},
		Par_input{Par_input::tipos::teclado, Input::aceptar, config.acc_input_aceptar()},
		Par_input{Par_input::tipos::teclado, Input::izquierda, config.acc_input_izquierda()},
		Par_input{Par_input::tipos::teclado, Input::derecha, config.acc_input_derecha()},
		Par_input{Par_input::tipos::teclado, Input::arriba, config.acc_input_arriba()},
		Par_input{Par_input::tipos::teclado, Input::abajo, config.acc_input_abajo()},
		Par_input{Par_input::tipos::teclado, Input::pag_siguiente, config.acc_input_pagina_siguiente()},
		Par_input{Par_input::tipos::teclado, Input::pag_anterior, config.acc_input_pagina_anterior()}};

	return res;
}
