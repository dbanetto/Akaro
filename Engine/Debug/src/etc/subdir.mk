################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/etc/AreaMap.cpp \
../src/etc/Camera.cpp \
../src/etc/Timer.cpp \
../src/etc/battery.cpp \
../src/etc/colour.cpp \
../src/etc/env.cpp \
../src/etc/string.cpp 

OBJS += \
./src/etc/AreaMap.o \
./src/etc/Camera.o \
./src/etc/Timer.o \
./src/etc/battery.o \
./src/etc/colour.o \
./src/etc/env.o \
./src/etc/string.o 

CPP_DEPS += \
./src/etc/AreaMap.d \
./src/etc/Camera.d \
./src/etc/Timer.d \
./src/etc/battery.d \
./src/etc/colour.d \
./src/etc/env.d \
./src/etc/string.d 


# Each subdirectory must supply rules for building sources it contributes
src/etc/%.o: ../src/etc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


