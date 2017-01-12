################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include libs/misc/src/subdir.mk
-include libs/StdPeriph/src/subdir.mk
-include libs/CMSIS/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
stepper.bin \

SECONDARY_LIST += \
stepper.lst \

SECONDARY_SIZE += \
stepper.siz \


# All Target
all: stepper.elf secondary-outputs

# Tool invocations
stepper.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"stepper.map" -o "stepper.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

stepper.bin: stepper.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy "stepper.elf" -O binary  "stepper.bin"
	@echo 'Finished building: $@'
	@echo ' '

stepper.lst: stepper.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump "stepper.elf" --source --all-headers --demangle --line-numbers --wide > "stepper.lst"
	@echo 'Finished building: $@'
	@echo ' '

stepper.siz: stepper.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size  --format=berkeley "stepper.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(S_UPPER_DEPS) stepper.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
