OBJSCLI = $(shell find src -type f -name *.cpp ! -name serverMain.cpp ! -name Sonictp.cpp)
OBJSSERV = $(shell find src -type f -name *.cpp ! -name clientMain.cpp ! -name Sonictp.cpp)

CC = g++ 

COMPILER_FLAGS = -w -g -O0 -Wall
 
LINKER_FLAGS_CLIENT = -std=c++11 -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -ljansson
LINKER_FLAGS_SERVER = -std=c++11 -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -ljansson

OBJCLI_NAME = cliente
OBJSERV_NAME = servidor

cliente: $(OBJSCLI)
	$(CC) $(OBJSCLI) $(COMPILER_FLAGS) $(LINKER_FLAGS_CLIENT) -o $(OBJCLI_NAME)

servidor: $(OBJSERV)
	$(CC) $(OBJSSERV) $(COMPILER_FLAGS) $(LINKER_FLAGS_SERVER) -o $(OBJSERV_NAME)

clean:
	rm -rf *.o $(OBJCLI_NAME) $(OBJSERV_NAME)
