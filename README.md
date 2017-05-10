#  Taller de programación 1: 2017 1er Cuatrimestre, 2er tp.
#  Integrantes 
    Añez Johana 93042,
    Dimasi Patricia 79478,
    Ponce Julieta 96375,
    Quino Julián 94224,
    Villani Cristian 93358,

# Sistema Operativo 
  Linux, Ubuntu.
  
# Librerias
    SDL2 version 2.0.5, link : http://packages.ubuntu.com/search?keywords=sdl2
    SDL2_IMAGE version 2.0, link : https://www.libsdl.org/projects/SDL_image/
    Jannson, version 2.10, link : http://www.digip.org/jansson/releaseg++s/STL
    pthread, libreria standard de ubuntu
# Compilación por consola
    servidor:
       g++  src/serverMain.cpp src/Textura.cpp src/VistaSDL.cpp src/Circulo.cpp src/HiloEnviarCliente.cpp src/jentidades.cpp        src/Logger.cpp src/ConstructorEntidades.cpp src/Hilorecibir.cpp src/jventana.cpp src/AdministradorLatidoCliente.cpp src/Personaje.cpp src/jcuadrado.cpp src/ConexCliente.cpp src/ProcesadorCliente.cpp src/VariableCondicional.cpp src/Posicion.cpp src/jpruebas.cpp src/jconfiguracion.cpp src/Animacion.cpp src/ConexServidor.cpp src/Control.cpp src/Camara.cpp src/Hilo.cpp src/Hiloenviar.cpp src/parseadorJsonSer.cpp src/HilolatidoSer.cpp src/jservidor.cpp src/Rectangulo.cpp src/capas.cpp src/jcirculo.cpp src/HiloRecibirCliente.cpp src/parseadorJson.cpp src/ControlServidor.cpp src/jescenario.cpp src/Mensaje.cpp src/Paquete.cpp src/Sockets.cpp src/HiloConexion.cpp src/ControladorTeclas.cpp src/parseadorJsonCli.cpp src/jescenarioJuego.cpp src/jrectangulo.cpp src/Hilolatidocliente.cpp src/dimensiones.cpp src/JuegoServidor.cpp src/JuegoCliente.cpp src/Entidad.cpp -w -g -O0 -Wall -std=c++11 -lpthread -lSDL2 -lSDL2_image -ljansson -o servidor

    
    cliente:
    g++  src/Textura.cpp src/VistaSDL.cpp src/Circulo.cpp src/HiloEnviarCliente.cpp src/jentidades.cpp src/Logger.cpp src/ConstructorEntidades.cpp src/Hilorecibir.cpp src/jventana.cpp src/AdministradorLatidoCliente.cpp src/clientMain.cpp src/Personaje.cpp src/jcuadrado.cpp src/ConexCliente.cpp src/ProcesadorCliente.cpp src/VariableCondicional.cpp src/Posicion.cpp src/jpruebas.cpp src/jconfiguracion.cpp src/Animacion.cpp src/ConexServidor.cpp src/Control.cpp src/Camara.cpp src/Hilo.cpp src/Hiloenviar.cpp src/parseadorJsonSer.cpp src/HilolatidoSer.cpp src/jservidor.cpp src/Rectangulo.cpp src/capas.cpp src/jcirculo.cpp src/HiloRecibirCliente.cpp src/parseadorJson.cpp src/ControlServidor.cpp src/jescenario.cpp src/Mensaje.cpp src/Paquete.cpp src/Sockets.cpp src/HiloConexion.cpp src/ControladorTeclas.cpp src/parseadorJsonCli.cpp src/jescenarioJuego.cpp src/jrectangulo.cpp src/Hilolatidocliente.cpp src/dimensiones.cpp src/JuegoServidor.cpp src/JuegoCliente.cpp src/Entidad.cpp -w -g -O0 -Wall -std=c++11 -lpthread -lSDL2 -lSDL2_image -ljansson -o cliente
     
# Ejecución
    ./servidor
    ./cliente
1 es el nivel del logger, puede ser 2 o 3.
Si no se agrega ese parámetro, o es incorrecto, por default toma el valor 2.
