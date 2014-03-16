################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/graphics/Sprite.cpp \
../src/graphics/Texture.cpp \
../src/graphics/TextureManager.cpp \
../src/graphics/drawable.cpp 

OBJS += \
./src/graphics/Sprite.o \
./src/graphics/Texture.o \
./src/graphics/TextureManager.o \
./src/graphics/drawable.o 

CPP_DEPS += \
./src/graphics/Sprite.d \
./src/graphics/Texture.d \
./src/graphics/TextureManager.d \
./src/graphics/drawable.d 


# Each subdirectory must supply rules for building sources it contributes
src/graphics/%.o: ../src/graphics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


