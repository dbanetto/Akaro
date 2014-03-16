################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/input/InputManager.cpp \
../src/input/InputProvider.cpp \
../src/input/KBProvider.cpp \
../src/input/PS3Provider.cpp 

OBJS += \
./src/input/InputManager.o \
./src/input/InputProvider.o \
./src/input/KBProvider.o \
./src/input/PS3Provider.o 

CPP_DEPS += \
./src/input/InputManager.d \
./src/input/InputProvider.d \
./src/input/KBProvider.d \
./src/input/PS3Provider.d 


# Each subdirectory must supply rules for building sources it contributes
src/input/%.o: ../src/input/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


