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
       make servidor

    
    cliente:
        make cliente
# Ejecución
    ./servidor
    ./cliente
    
1 es el nivel del logger, puede ser 2 o 3.
Si no se agrega ese parámetro, o es incorrecto, por default toma el valor 2.
Al ejecutar el cliente y el servidor, al iniciar pide ingresar el nombre del archivo de configuración de cada uno.
El nombre de los archivos son :
    configuracion/servidor.json
    configuracion/cliente.json

Si se ingresa mal el nombre de los archivos, el programa toma uno por defecto.
