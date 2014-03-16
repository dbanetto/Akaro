################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/states/GameState.cpp \
../src/states/GameStateManager.cpp \
../src/states/MenuState.cpp 

OBJS += \
./src/states/GameState.o \
./src/states/GameStateManager.o \
./src/states/MenuState.o 

CPP_DEPS += \
./src/states/GameState.d \
./src/states/GameStateManager.d \
./src/states/MenuState.d 


# Each subdirectory must supply rules for building sources it contributes
src/states/%.o: ../src/states/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


