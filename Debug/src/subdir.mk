################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Logger.cpp \
../src/Mensaje.cpp \
../src/PruebaLogger.cpp \
../src/Sonictp.cpp 

OBJS += \
./src/Logger.o \
./src/Mensaje.o \
./src/PruebaLogger.o \
./src/Sonictp.o 

CPP_DEPS += \
./src/Logger.d \
./src/Mensaje.d \
./src/PruebaLogger.d \
./src/Sonictp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


