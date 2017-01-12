################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/StdPeriph/src/misc.c \
../libs/StdPeriph/src/stm32f10x_adc.c \
../libs/StdPeriph/src/stm32f10x_bkp.c \
../libs/StdPeriph/src/stm32f10x_can.c \
../libs/StdPeriph/src/stm32f10x_cec.c \
../libs/StdPeriph/src/stm32f10x_crc.c \
../libs/StdPeriph/src/stm32f10x_dac.c \
../libs/StdPeriph/src/stm32f10x_dbgmcu.c \
../libs/StdPeriph/src/stm32f10x_dma.c \
../libs/StdPeriph/src/stm32f10x_exti.c \
../libs/StdPeriph/src/stm32f10x_flash.c \
../libs/StdPeriph/src/stm32f10x_fsmc.c \
../libs/StdPeriph/src/stm32f10x_gpio.c \
../libs/StdPeriph/src/stm32f10x_i2c.c \
../libs/StdPeriph/src/stm32f10x_iwdg.c \
../libs/StdPeriph/src/stm32f10x_pwr.c \
../libs/StdPeriph/src/stm32f10x_rcc.c \
../libs/StdPeriph/src/stm32f10x_rtc.c \
../libs/StdPeriph/src/stm32f10x_sdio.c \
../libs/StdPeriph/src/stm32f10x_spi.c \
../libs/StdPeriph/src/stm32f10x_tim.c \
../libs/StdPeriph/src/stm32f10x_usart.c \
../libs/StdPeriph/src/stm32f10x_wwdg.c 

OBJS += \
./libs/StdPeriph/src/misc.o \
./libs/StdPeriph/src/stm32f10x_adc.o \
./libs/StdPeriph/src/stm32f10x_bkp.o \
./libs/StdPeriph/src/stm32f10x_can.o \
./libs/StdPeriph/src/stm32f10x_cec.o \
./libs/StdPeriph/src/stm32f10x_crc.o \
./libs/StdPeriph/src/stm32f10x_dac.o \
./libs/StdPeriph/src/stm32f10x_dbgmcu.o \
./libs/StdPeriph/src/stm32f10x_dma.o \
./libs/StdPeriph/src/stm32f10x_exti.o \
./libs/StdPeriph/src/stm32f10x_flash.o \
./libs/StdPeriph/src/stm32f10x_fsmc.o \
./libs/StdPeriph/src/stm32f10x_gpio.o \
./libs/StdPeriph/src/stm32f10x_i2c.o \
./libs/StdPeriph/src/stm32f10x_iwdg.o \
./libs/StdPeriph/src/stm32f10x_pwr.o \
./libs/StdPeriph/src/stm32f10x_rcc.o \
./libs/StdPeriph/src/stm32f10x_rtc.o \
./libs/StdPeriph/src/stm32f10x_sdio.o \
./libs/StdPeriph/src/stm32f10x_spi.o \
./libs/StdPeriph/src/stm32f10x_tim.o \
./libs/StdPeriph/src/stm32f10x_usart.o \
./libs/StdPeriph/src/stm32f10x_wwdg.o 

C_DEPS += \
./libs/StdPeriph/src/misc.d \
./libs/StdPeriph/src/stm32f10x_adc.d \
./libs/StdPeriph/src/stm32f10x_bkp.d \
./libs/StdPeriph/src/stm32f10x_can.d \
./libs/StdPeriph/src/stm32f10x_cec.d \
./libs/StdPeriph/src/stm32f10x_crc.d \
./libs/StdPeriph/src/stm32f10x_dac.d \
./libs/StdPeriph/src/stm32f10x_dbgmcu.d \
./libs/StdPeriph/src/stm32f10x_dma.d \
./libs/StdPeriph/src/stm32f10x_exti.d \
./libs/StdPeriph/src/stm32f10x_flash.d \
./libs/StdPeriph/src/stm32f10x_fsmc.d \
./libs/StdPeriph/src/stm32f10x_gpio.d \
./libs/StdPeriph/src/stm32f10x_i2c.d \
./libs/StdPeriph/src/stm32f10x_iwdg.d \
./libs/StdPeriph/src/stm32f10x_pwr.d \
./libs/StdPeriph/src/stm32f10x_rcc.d \
./libs/StdPeriph/src/stm32f10x_rtc.d \
./libs/StdPeriph/src/stm32f10x_sdio.d \
./libs/StdPeriph/src/stm32f10x_spi.d \
./libs/StdPeriph/src/stm32f10x_tim.d \
./libs/StdPeriph/src/stm32f10x_usart.d \
./libs/StdPeriph/src/stm32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
libs/StdPeriph/src/%.o: ../libs/StdPeriph/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../libs/misc/include" -I"../include" -I"../libs/CMSIS/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


