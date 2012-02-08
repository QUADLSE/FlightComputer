################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/bsp/src/subdir.mk
-include src/board/LPCXpresso/subdir.mk
-include src/board/LPCXpresso/LPC17XX_CMSIS_Drivers/Drivers/source/subdir.mk
-include src/board/LPCXpresso/LPC17XX_CMSIS_Drivers/Core/CM3/DeviceSupport/NXP/LPC17xx/subdir.mk
-include src/board/LPCXpresso/LPC17XX_CMSIS_Drivers/Core/CM3/CoreSupport/subdir.mk
-include src/board/LPCXpresso/BSP/subdir.mk
-include src/app/subdir.mk
-include src/api/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: QUADLSE_OBC.axf

# Tool invocations
QUADLSE_OBC.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="QUADLSE_OBC.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "QUADLSE_OBC_Debug.ld" -o"QUADLSE_OBC.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) QUADLSE_OBC.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "QUADLSE_OBC.axf"; # arm-none-eabi-objcopy -O binary "QUADLSE_OBC.axf" "QUADLSE_OBC.bin" ; checksum -p LPC1769 -d "QUADLSE_OBC.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
