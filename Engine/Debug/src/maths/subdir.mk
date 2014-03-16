################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/maths/Point.cpp \
../src/maths/area.cpp \
../src/maths/rect.cpp \
../src/maths/vector.cpp 

OBJS += \
./src/maths/Point.o \
./src/maths/area.o \
./src/maths/rect.o \
./src/maths/vector.o 

CPP_DEPS += \
./src/maths/Point.d \
./src/maths/area.d \
./src/maths/rect.d \
./src/maths/vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/maths/%.o: ../src/maths/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


