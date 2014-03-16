################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/Button.cpp \
../src/ui/Label.cpp 

OBJS += \
./src/ui/Button.o \
./src/ui/Label.o 

CPP_DEPS += \
./src/ui/Button.d \
./src/ui/Label.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/%.o: ../src/ui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


