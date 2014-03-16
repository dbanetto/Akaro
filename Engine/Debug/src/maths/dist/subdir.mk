################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/maths/dist/normal.cpp \
../src/maths/dist/triangular.cpp 

OBJS += \
./src/maths/dist/normal.o \
./src/maths/dist/triangular.o 

CPP_DEPS += \
./src/maths/dist/normal.d \
./src/maths/dist/triangular.d 


# Each subdirectory must supply rules for building sources it contributes
src/maths/dist/%.o: ../src/maths/dist/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


