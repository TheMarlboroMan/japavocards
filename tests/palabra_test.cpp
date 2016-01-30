#include <iostream>
#include "../class/app/etiqueta.cpp"
#include "../class/app/palabra.cpp"

int main(int argc, char ** argv)
{
	using namespace App;

	Etiqueta		etiqueta_1("Label 1"),
				etiqueta_2("Label 2"),
				etiqueta_3("Label 3"),
				etiqueta_4("Label 4");

	Palabra			palabra_uno("Japones uno", "Romaji uno", "Traducción 1");

	std::cout<<"Se ha creado la palabra: "<<palabra_uno.acc_japones()<<", "<<palabra_uno.acc_romaji()<<", "<<palabra_uno.acc_traduccion()<<std::endl;

	std::cout<<"Insertando etiquetas en palabra..."<<std::endl;
	palabra_uno.insertar_etiqueta(etiqueta_1);
	palabra_uno.insertar_etiqueta(etiqueta_2);
	palabra_uno.insertar_etiqueta(etiqueta_3);
	palabra_uno.insertar_etiqueta(etiqueta_4);

	std::cout<<"Las etiquetas insertadas son: "<<palabra_uno.obtener_string_etiquetas()<<std::endl;

	std::cout<<"Intentando insertar etiqueta repetida..."<<std::endl;
	try
	{
		palabra_uno.insertar_etiqueta(etiqueta_1);
	}
	catch(std::exception& e)
	{
		std::cout<<"Excepción atrapada: "<<e.what()<<std::endl;
	}

	std::cout<<"Eliminando etiquetas de palabra"<<std::endl;
	palabra_uno.eliminar_etiqueta(etiqueta_1);
	palabra_uno.eliminar_etiqueta(etiqueta_2);

	std::cout<<"Las etiquetas restantes son: "<<palabra_uno.obtener_string_etiquetas()<<std::endl;

	std::cout<<"Intentando eliminar etiqueta no insertada..."<<std::endl;
	try
	{
		palabra_uno.eliminar_etiqueta(etiqueta_4);
	}
	catch(std::exception& e)
	{
		std::cout<<"Excepción atrapada: "<<e.what()<<std::endl;
	}

	std::cout<<"Comprobaciones de etiquetado..."<<std::endl;
	if(palabra_uno.tiene_etiqueta(etiqueta_1)) std::cout<<"ERROR: La etiqueta 1 no debe estar disponible"<<std::endl;
	else std::cout<<"La etiqueta 1 no está en la palabra"<<std::endl;

	if(!palabra_uno.tiene_etiqueta(etiqueta_3)) std::cout<<"ERROR: La etiqueta 3 debe estar disponible"<<std::endl;
	else std::cout<<"La etiqueta 3 está en la palabra"<<std::endl;

	std::cout<<"Comprobando restantes..."<<std::endl;
	std::cout<<"Hay "<<palabra_uno.total_etiquetas()<<" etiquetas en la palabra"<<std::endl;

	std::cout<<"Vaciando etiquetas..."<<std::endl;
	palabra_uno.limpiar_etiquetas();
	std::cout<<"Hay "<<palabra_uno.total_etiquetas()<<" etiquetas en la palabra tras el borrado."<<std::endl;

	return 0;

}
