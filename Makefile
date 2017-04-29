OBJSCLI = src/capas.cpp src/Circulo.cpp src/ConstructorEntidades.cpp src/Control.cpp src/Camara.cpp src/dimensiones.cpp src/Entidad.cpp src/jcirculo.cpp src/jconfiguracion.cpp src/jentidades.cpp src/jescenario.cpp src/jescenarioJuego.cpp src/jpruebas.cpp src/jrectangulo.cpp src/jventana.cpp src/Logger.cpp src/Mensaje.cpp src/parseadorJson.cpp src/jcuadrado.cpp src/Rectangulo.cpp src/Personaje.cpp src/Textura.cpp src/VistaSDL.cpp src/ConexServidor.cpp src/ConexCliente.cpp src/Sockets.cpp src/jservidor.cpp src/clientMain.cpp src/Hilo.cpp src/Animacion.cpp src/ControladorTeclas.cpp src/parseadorJsonCli.cpp src/Hiloenviar.cpp src/Hilorecibir.cpp src/HiloRecibirCliente.cpp src/HiloEnviarCliente.cpp src/JuegoCliente.cpp src/JuegoServidor.cpp src/ControlServidor.cpp src/Paquete.cpp

OBJSSERV = src/capas.cpp src/Circulo.cpp src/ConstructorEntidades.cpp src/Control.cpp src/Camara.cpp src/dimensiones.cpp src/Entidad.cpp src/jcirculo.cpp src/jconfiguracion.cpp src/jentidades.cpp src/jescenario.cpp src/jescenarioJuego.cpp src/jpruebas.cpp src/jrectangulo.cpp src/jventana.cpp src/Logger.cpp src/Mensaje.cpp src/parseadorJson.cpp src/jcuadrado.cpp src/Rectangulo.cpp src/Personaje.cpp src/Textura.cpp src/VistaSDL.cpp src/ConexServidor.cpp src/ConexCliente.cpp src/Sockets.cpp src/jservidor.cpp src/serverMain.cpp src/Hilo.cpp src/Animacion.cpp src/ControladorTeclas.cpp src/parseadorJsonSer.cpp src/Hilorecibir.cpp src/Hiloenviar.cpp src/JuegoServidor.cpp src/ControlServidor.cpp src/Paquete.cpp

CC = g++ 

COMPILER_FLAGS = -w -g -O0 -Wall
 
LINKER_FLAGS_CLIENT = -std=c++11 -lpthread -lSDL2 -lSDL2_image -ljansson
LINKER_FLAGS_SERVER = -std=c++11 -lpthread -lSDL2 -lSDL2_image -ljansson

OBJCLI_NAME = cliente
OBJSERV_NAME = servidor

cliente: $(OBJSCLI)
	$(CC) $(OBJSCLI) $(COMPILER_FLAGS) $(LINKER_FLAGS_CLIENT) -o $(OBJCLI_NAME)

servidor: $(OBJSERV)
	$(CC) $(OBJSSERV) $(COMPILER_FLAGS) $(LINKER_FLAGS_SERVER) -o $(OBJSERV_NAME)

clean:
	rm -rf *.o $(OBJCLI_NAME) $(OBJSERV_NAME)
