using namespace App;

int main(int argc, char ** argv)
{
	try
	{
		//Crear nuevo documento desde datos correctos...
		std::cout<<"Iniciando carga de documento en disco..."<<std::endl;
		Lector L;
		L.cargar("lector_test_in_ok.dnot");
	
		//Insertar nuevo idioma.
		std::cout<<"Insertando nuevo idioma..."<<std::endl;
		Idioma nuevo_idioma{3, "Francés"};
		L.insertar_idioma(nuevo_idioma);

		//Insertar nueva etiqueta.
		std::cout<<"Insertando nueva etiqueta..."<<std::endl;
		Etiqueta_bruto nueva_etiqueta{"nueva"};
		nueva_etiqueta.nombres[1]="Nueva";
		nueva_etiqueta.nombres[2]="New";
		nueva_etiqueta.nombres[3]="Nouveau";
		L.insertar_etiqueta(nueva_etiqueta);

		//Insertar nueva palabra.
		std::cout<<"Insertando nueva palabra..."<<std::endl;
		Palabra_bruto nueva_palabra{"japones", "romaji"};
		nueva_palabra.etiquetas.push_back(&nueva_etiqueta);
		nueva_palabra.traducciones[1]="Algo";
		nueva_palabra.traducciones[2]="Something";
		nueva_palabra.traducciones[3]="Couseau";
		L.insertar_palabra(nueva_palabra);

		//Eliminar palabra.
		std::cout<<"Eliminando palabra..."<<std::endl;
		//TODO TODO TODO

		//Eliminar etiqueta y retirar de palabras.

		//Eliminar idioma y retirar del resto.	

		//Ejecutar control de cordura de datos (cosas sueltas).

		//Guardar documento resultante.
	}
	catch(std::exception& e)
	{
		std::cout<<"\t[ERROR] - "<<e.what()<<std::endl;
	}
}
