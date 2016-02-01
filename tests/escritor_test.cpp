#include <iostream>
#include <string>
#include "../class/app/datos_bruto.cpp"
#include "../class/app/lector.cpp"
#include "../class/app/escritor.cpp"
#include <class/dnot_parser.h>

using namespace App;

int main(int argc, char ** argv)
{
	try
	{
		//Crear nuevo documento desde datos correctos...
		std::cout<<"Iniciando carga de documento en disco..."<<std::endl;
		Lector L;
		L.cargar("escritor_test_in_ok.dnot");

		std::cout<<"Insertando nuevo idioma..."<<std::endl;
		Idioma nuevo_idioma{"FR", "Francés"};
		L.insertar_idioma(nuevo_idioma);

		//Insertar nueva etiqueta.
		std::cout<<"Insertando y buscando nueva etiqueta..."<<std::endl;
		Etiqueta_bruto nueva_etiqueta{"nueva"};
		nueva_etiqueta.nombres["ES"]="Nueva";
		nueva_etiqueta.nombres["EN"]="New";
		nueva_etiqueta.nombres["FR"]="Nouveau";
		L.insertar_etiqueta(nueva_etiqueta);

		//Insertar nueva palabra.
		std::cout<<"Insertando y nueva palabra..."<<std::endl;
		Palabra_bruto nueva_palabra{"japones", "romaji"};
		nueva_palabra.etiquetas.push_back(&nueva_etiqueta);
		nueva_palabra.traducciones["ES"]="Algo";
		nueva_palabra.traducciones["EN"]="Something";
		nueva_palabra.traducciones["FR"]="Couseau";
		L.insertar_palabra(nueva_palabra);
	
		std::cout<<"Iniciando escritura de documento en disco..."<<std::endl;
		Escritor E;
		E.generar(L.acc_idiomas(), L.acc_etiquetas(), L.acc_palabras());
		E.guardar("escritor_test_out.dnot");

	}
	catch(std::exception& e)
	{
		std::cout<<"\t[ERROR] - "<<e.what()<<std::endl;
	}

	return 0;
}
