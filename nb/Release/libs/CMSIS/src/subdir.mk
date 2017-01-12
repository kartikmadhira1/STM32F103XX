################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/CMSIS/src/core_cm3.c \
../libs/CMSIS/src/startup_cm.c \
../libs/CMSIS/src/startup_stm32f10x.c \
../libs/CMSIS/src/system_stm32f10x.c \
../libs/CMSIS/src/vectors_stm32f10x.c 

OBJS += \
./libs/CMSIS/src/core_cm3.o \
./libs/CMSIS/src/startup_cm.o \
./libs/CMSIS/src/startup_stm32f10x.o \
./libs/CMSIS/src/system_stm32f10x.o \
./libs/CMSIS/src/vectors_stm32f10x.o 

C_DEPS += \
./libs/CMSIS/src/core_cm3.d \
./libs/CMSIS/src/startup_cm.d \
./libs/CMSIS/src/startup_stm32f10x.d \
./libs/CMSIS/src/system_stm32f10x.d \
./libs/CMSIS/src/vectors_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
libs/CMSIS/src/%.o: ../libs/CMSIS/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../libs/misc/include" -I"../include" -I"../libs/CMSIS/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


