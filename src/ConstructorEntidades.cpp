/*
 * ConstructorEntidades.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#define MODULO 'PARSEADOR JSON'
#include "ConstructorEntidades.h"
#include "debug.h"

namespace std
{

ConstructorEntidades::ConstructorEntidades(int limiteAncho, int limiteAlto, Logger *log)
: generadorId(0), limiteAncho(limiteAncho), limiteAlto(limiteAlto), entidades()
{
	this->log = log;
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
}

ConstructorEntidades::~ConstructorEntidades()
{
	list<Entidad*>::iterator pos;
	for(pos = entidades.begin();pos != entidades.end();pos++){
		delete (*pos);
	}
	entidades.clear();
}

int ConstructorEntidades::generarId()
{
	return ++generadorId;
}

SDL_Renderer* ConstructorEntidades::getRenderizador(){
		return renderizador;
}

void ConstructorEntidades::setRenderizador(SDL_Renderer* Renderizador) {
   this->renderizador = Renderizador;
}


void ConstructorEntidades::cargarEntidades(list<jentidades> jEntidades, SDL_Renderer *renderizador)
{
	list<jentidades>::iterator pos;
	int id;
	std::string color;
	int ancho, alto;
	int coordX, coordY, indexZ;
	std::string rutaImagen;
	int radio;

	this->log->addLogMessage("[CARGA DE ENTIDADES] Iniciado.", 2);


	for(pos = jEntidades.begin();pos != jEntidades.end();pos++)
	{
		if(((*pos).gettipo() == "rectangulo") || ((*pos).gettipo() == "cuadrado"))
		{
			//id = (*pos).getid();
			id = (*pos).getid();
			color = (*pos).getcolor();
			ancho = (*pos).getDim()->getvalor1();
			alto = (*pos).getDim()->getvalor2();

			coordX = (*pos).getcoorx();
			//debug(1, "ConstructorEntidades::cargarEntidades", "Cordenada X %d\n", coordX);
			coordY = (*pos).getcoory();
			//debug(1, "ConstructorEntidades::cargarEntidades", "Cordenada Y %d\n", coordY);

			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(ancho, 0, MAX_ANCHO);
			validar(alto, 0, MAX_ALTO);

			if ((*pos).gettipo() == "cuadrado")
			{
				validarCuadrado(ancho, alto);
			}

			if ((*pos).getruta() == "images/Anillas.png"){
				//coordX = 0;
				//ancho = (*pos).getDim()->getvalor1();
				//int espacio = ancho + 10;

				cout<<"LLEGA"<<endl;

				srand(time(NULL));
				int cantidadAnillas = (rand() % 4) + 1;


				// cout<<"####CANTIDADANILLAS###"<<endl;
				// cout<<cantidadAnillas<<endl;

				debug(1, "ConstructorEntidades::cargarEntidadesssssssssssssssssssssssssssssssssssss", "Cordenada X %d\n", (*pos).getcoorx());
				debug(1, "ConstructorEntidades::cargarEntidades", "Cordenada Y %d\n", (*pos).getcoory());

				for(int i=0;i<cantidadAnillas;i++){
					//id = (*pos).getid();
					id = generarId();
					color = (*pos).getcolor();
					ancho = (*pos).getDim()->getvalor1();
					alto = (*pos).getDim()->getvalor2();
					//coordX = /*i * (*pos).getcoorx() +*/ coordX + (*pos).getcoorx() + (i*5);
					//coordX = coordX + espacio;
					coordX = i* 200 + (*pos).getcoorx() ;
					coordY = (*pos).getcoory();
					rutaImagen = (*pos).getruta();
					indexZ = (*pos).getindex();


					//Anillos* anillo = new Anillos(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log/*,vista->obtenerRender()*/);

					//this->anillos.push_back(anillo);
					//  this->cargarImagenesAnillas(renderizador);

					//entidades.push_back(anillo);
			    }

			}
			else if ((*pos).getruta() == "images/Bonus.png")
			{
				generarBonus(ancho, alto, color, rutaImagen, indexZ);
			}
			else
			{
				Rectangulo *rectangulo = new Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
				entidades.push_back(rectangulo);
				this->log->setModulo("CONSTRUCTOR ENTIDADES");
				this->log->addLogMessage("[CARGAR ENTIDADES] Rectangulo->"+rectangulo->toString(), 3);
			}
		}
		else if((*pos).gettipo() == "circulo")
		{
			//id = (*pos).getid();
			id = generarId();
			color = (*pos).getcolor();
			radio = (*pos).getDim()->getvalor1();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(radio, 0, MAX_RADIO);

			Circulo *circulo = new Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			entidades.push_back(circulo);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR ENTIDADES] Circulo->"+circulo->toString(), 3);
		}
	}

	cargarImagenes(renderizador);
	ordenarSegunIndexZ();

	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGA DE ENTIDADES] Terminado.\n", 2);
	this->setRenderizador(renderizador);
}

void ConstructorEntidades::cargarEntidadesCliente(list<jentidades> jEntidades, SDL_Renderer *renderizador)
{
	//Carga una entidad de cada una en un mapa para luego poder construir lo que le manda el servidor a partir de esas
	list<jentidades>::iterator pos;
	int id;
	std::string color;
	int ancho, alto;
	int coordX, coordY, indexZ;
	std::string rutaImagen;
	int radio;

	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGA DE ENTIDADES] Iniciado.", 2);


	for(pos = jEntidades.begin();pos != jEntidades.end();pos++)
	{
		if(((*pos).gettipo() == "rectangulo") || ((*pos).gettipo() == "cuadrado"))
		{
			id = (*pos).getid();
			color = (*pos).getcolor();
			ancho = (*pos).getDim()->getvalor1();
			alto = (*pos).getDim()->getvalor2();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(ancho, 0, MAX_ANCHO);
			validar(alto, 0, MAX_ALTO);

			if ((*pos).gettipo() == "cuadrado")
			{
				validarCuadrado(ancho, alto);
			}

			//if ((*pos).getruta() == "images/Anillas.png")
			//{
				//Lo agrega al generadorEntidades para luego poder sacarle la informacion para crearlos
				//Anillos* unAnillo = new Anillos(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log/*,vista->obtenerRender()*/);
		//		generadorEntidades[ANILLOS] = unAnillo;
			//	this->log->addLogMessage("[CARGAR ENTIDADES] Anillo", 3);
			//}

			else if ((*pos).getruta() == "images/Bonus.png")
			{
				//Los agrega al generadorEntidades para luego poder sacarle la informacion para crearlos
				Bonus* unBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, coordX, coordY, indexZ, log, Bonus::ESCUDO);
				generadorEntidades[BONUS_ESCUDO] = unBonus;
				this->log->addLogMessage("[CARGAR ENTIDADES] Bonus Escudo", 3);

				unBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, coordX, coordY, indexZ, log, Bonus::RING);
				generadorEntidades[BONUS_RING] = unBonus;
				this->log->addLogMessage("[CARGAR ENTIDADES] Bonus Anillos", 3);

				unBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, coordX, coordY, indexZ, log, Bonus::INVENCIBILIDAD);
				generadorEntidades[BONUS_INVENCIBILIDAD] = unBonus;
				this->log->addLogMessage("[CARGAR ENTIDADES] Bonus Invencibilidad", 3);
			}
			else
			{
				//No lo agrega al generadorEntidades
				//Pero lo pone en la lista de entidades asi la dibuja y no depende del servidor
				Rectangulo *rectangulo = new Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
				entidades.push_back(rectangulo);
				this->log->setModulo("CONSTRUCTOR ENTIDADES");
				this->log->addLogMessage("[CARGAR ENTIDADES] Rectangulo->"+rectangulo->toString(), 3);
			}
			//Agregar mas rectangulos...
			//Agregar entidades que dependen del servidor al generadorEntidades (uno solo)
			//O agregar entidades que no dependan a la lista de entidades
		}
		else if((*pos).gettipo() == "circulo")
		{
			id = (*pos).getid();
			color = (*pos).getcolor();
			radio = (*pos).getDim()->getvalor1();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(radio, 0, MAX_RADIO);

			Circulo *circulo = new Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			entidades.push_back(circulo);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR ENTIDADES] Circulo->"+circulo->toString(), 3);
		}
	}

	cargarImagenes(renderizador);
	ordenarSegunIndexZ();

	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGA DE ENTIDADES] Terminado.\n", 2);
	this->setRenderizador(renderizador);
}

void ConstructorEntidades::inicializarImagenes(SDL_Renderer *renderizador)
{
	cargarImagenes(renderizador);
	ordenarSegunIndexZ();
}

Logger *ConstructorEntidades::getLog() const
{
	return log;
}

void ConstructorEntidades::setLog(Logger *log)
{
	this->log = log;
}

void ConstructorEntidades::cargarImagenes(SDL_Renderer *renderizador)
{
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGAR IMAGENES] Iniciado.",2);
	list<Entidad*>::iterator pos;

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->tieneRutaImagen())
		{
			(*pos)->cargarImagen(renderizador, log);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR IMAGENES] Imagen cargada en ruta: "+(*pos)->getRutaImagen(),3);
		}
	}
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGAR IMAGENES] Terminado.",2);


}

void ConstructorEntidades::cargarImagenesAnillas(SDL_Renderer *renderizador)
{
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGAR IMAGENES] Iniciado.",2);
	list<Anillos*>::iterator pos;
   // cout<<anillos.size()<<endl;
	for(pos = anillos.begin(); pos != anillos.end(); pos++)
	{
	  if ((*pos)->tieneRutaImagen())
		{

			(*pos)->cargarImagen(renderizador, log);
				this->log->setModulo("CONSTRUCTOR ENTIDADES");
				this->log->addLogMessage("[CARGAR IMAGENES] Imagen cargada en ruta: "+(*pos)->getRutaImagen(),3);
			}
		}
		this->log->setModulo("CONSTRUCTOR ENTIDADES");
		this->log->addLogMessage("[CARGAR IMAGENES] Terminado.",2);
}
void ConstructorEntidades::mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ)
{
	list<Entidad*>::iterator pos;
	//this->log->addLogMessage("[MOSTRAR IMAGENES] Iniciado",2);
	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->indexZes(indexZ))
		{
			(*pos)->dibujar(renderizador, camara);
		}
	}

	//this->log->addLogMessage("[MOSTRAR IMAGENES] Terminado",2);
}

void ConstructorEntidades::mostrarAnillas(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ){
	list<Anillos*>::iterator pos;

	for(pos = anillos.begin();pos != anillos.end(); pos++)
	{
		if ((*pos)->indexZes(indexZ))
			{
			  (*pos)->dibujar(renderizador, camara);
			}
	}
}

bool compararIndexZ(const Entidad *primera, const Entidad *segunda)
{
	return primera->indexZMenorA(segunda);
}

void ConstructorEntidades::ordenarSegunIndexZ()
{
	entidades.sort(compararIndexZ);
}

void ConstructorEntidades::validarDatosNumericos(int &id, int &coordX, int &coordY, int &indexZ)
{
	this->log->addLogMessage("[VALIDAR DATOS NUMERICOS] Iniciado.",2);

	validar(id, 0, MAX_ID);
	validar(coordX, 0, MAX_COORDX);
	validar(coordY, 0, MAX_COORDY);
	validar(indexZ, 0, MAX_INDEXZ);

	this->log->addLogMessage("[VALIDAR DATOS NUMERICOS] Terminado.",2);
}

void ConstructorEntidades::validar(int &numero, int minimo, int maximo)
{
	if (numero < minimo)
	{
		numero = (-numero);
	}
	else if (numero > maximo)
	{
		numero = maximo;
	}
}

void ConstructorEntidades::validarCuadrado(int &ancho, int &alto)
{
	//El cuadrado es de dimensiones ancho x ancho
	if (ancho != alto)
	{
		alto = ancho;
	}
}

void ConstructorEntidades::agregarEntidadCliente(std::string nombre, int id, int x, int y)
{
	if (nombre.compare(BONUS_RING) == 0)
	{
		Bonus* creadorBonus = (Bonus*)generadorEntidades.at(BONUS_RING); //Saca un bonus pasa sacarle la informacion

		Bonus* unBonus = new Bonus(creadorBonus->obtenerAncho(), creadorBonus->obtenerAlto(),
			id, creadorBonus->getNombreColor(), creadorBonus->getRutaImagen(),
			x, y, creadorBonus->getIndexZ(), log, Bonus::RING);

		entidades.push_back(unBonus);
	}
	else if (nombre.compare(BONUS_ESCUDO) == 0)
	{
		Bonus* creadorBonus = (Bonus*)generadorEntidades.at(BONUS_ESCUDO); //Saca un bonus pasa sacarle la informacion

		Bonus* unBonus = new Bonus(creadorBonus->obtenerAncho(), creadorBonus->obtenerAlto(),
			id, creadorBonus->getNombreColor(), creadorBonus->getRutaImagen(),
			x, y, creadorBonus->getIndexZ(), log, Bonus::ESCUDO);

		entidades.push_back(unBonus);
	}
	else if (nombre.compare(BONUS_INVENCIBILIDAD) == 0)
	{
		Bonus* creadorBonus = (Bonus*)generadorEntidades.at(BONUS_INVENCIBILIDAD); //Saca un bonus pasa sacarle la informacion

		Bonus* unBonus = new Bonus(creadorBonus->obtenerAncho(), creadorBonus->obtenerAlto(),
			id, creadorBonus->getNombreColor(), creadorBonus->getRutaImagen(),
			x, y, creadorBonus->getIndexZ(), log, Bonus::INVENCIBILIDAD);

		entidades.push_back(unBonus);
	}
	else if (nombre.compare(ANILLOS) == 0)
	{
		Anillos* creadorAnillo = (Anillos*)generadorEntidades.at(ANILLOS); //Saca un anillo pasa sacarle la informacion

		Anillos* unAnillo = new Anillos(creadorAnillo->getAncho(), creadorAnillo->getAlto(),
			id, creadorAnillo->getNombreColor(), creadorAnillo->getRutaImagen(),
			x, y, creadorAnillo->getIndexZ(), log);

		entidades.push_back(unAnillo);
		anillos.push_back(unAnillo);
	}
	//Agregar mas cosas que reciba del servidor...
	return;
}

void ConstructorEntidades::quitarEntidad(std::string nombre, int id)
{
	//El cliente la quita al recibir un mensaje del servidor
	std::list<Entidad*>::iterator iter;
	for(iter = entidades.begin(); iter != entidades.end(); iter++)
	{
		if ((*iter)->getId() == id)
		{
			delete (*iter);
			entidades.erase(iter);
			return;
		}
	}
}

void ConstructorEntidades::generarBonus(int ancho, int alto,
		std::string color, std::string rutaImagen, int indexZ)
{
	//Genera bonus en posiciones y cantidades aleatorias
	srand(time(NULL));
	//Agrego bonus de Escudo
	int cantidadBonus = Util::numeroRandom(3);
	int y = limiteAlto - alto;

	for(int i = 0; i < cantidadBonus; i++)
	{
		//Divide el escenario en partes iguales del doble del ancho del bonus para que no se superpongan
		//Y al sumarle 2*ancho hago que caiga en una de esas divisiones
		int x = Util::numeroRandom(limiteAncho/(2*ancho)) * (2*ancho);
		Bonus* nuevoBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, x, y, indexZ, log, Bonus::ESCUDO);
		entidades.push_back(nuevoBonus);
	}

	//Agrego bonus de Anillos
	cantidadBonus = Util::numeroRandom(3);
	for(int i = 0; i < cantidadBonus; i++)
	{
		int x = Util::numeroRandom(limiteAncho/(2*ancho)) * (2*ancho);
		Bonus* nuevoBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, x, y, indexZ, log, Bonus::RING);
		entidades.push_back(nuevoBonus);
	}

	//Agrego bonus de Anillos
	cantidadBonus = Util::numeroRandom(3);
	for(int i = 0; i < cantidadBonus; i++)
	{
		int x = Util::numeroRandom(limiteAncho/(2*ancho)) * (2*ancho);
		Bonus* nuevoBonus = new Bonus(ancho, alto, generarId(), color, rutaImagen, x, y, indexZ, log, Bonus::INVENCIBILIDAD);
		entidades.push_back(nuevoBonus);
	}

}

void ConstructorEntidades::cargarImagenesPiedra(SDL_Renderer *renderizador){


	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	//cout<<"LLEGA1"<<endl;
		//this->log->addLogMessage("[CARGAR IMAGENES] Iniciado.",2);
		list<Piedra*>::iterator pos;

		for(pos = piedra.begin(); pos != piedra.end(); pos++)

		  {

			if ((*pos)->tieneRutaImagen())
			{

				(*pos)->cargarImagen(renderizador, log);
				//this->log->setModulo("CONSTRUCTOR ENTIDADES");
				//this->log->addLogMessage("[CARGAR IMAGENES] Imagen cargada en ruta: "+(*pos)->getRutaImagen(),3);
			}

		}
	//	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	//	this->log->addLogMessage("[CARGAR IMAGENES] Terminado.",2);

  //}
}

void ConstructorEntidades::mostrarPiedras(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ){
	list<Piedra*>::iterator pos;

		for(pos = piedra.begin();pos != piedra.end(); pos++)
		{
			//if ((*pos)->indexZes(indexZ))
				//{
				  (*pos)->dibujar(renderizador, camara);
				//}
		}
}
}//Namespace
