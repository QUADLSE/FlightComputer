################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board/LPCXpresso/BSP/qPWM.c \
../src/board/LPCXpresso/BSP/qUART.c 

OBJS += \
./src/board/LPCXpresso/BSP/qPWM.o \
./src/board/LPCXpresso/BSP/qUART.o 

C_DEPS += \
./src/board/LPCXpresso/BSP/qPWM.d \
./src/board/LPCXpresso/BSP/qUART.d 


# Each subdirectory must supply rules for building sources it contributes
src/board/LPCXpresso/BSP/%.o: ../src/board/LPCXpresso/BSP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DMY_ADDRESS=0xAA -D__USE_CMSIS -D__REDLIB__ -DDEBUG -D__CODE_RED -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\board\LPCXpresso\LPC17XX_CMSIS_Drivers\Core\CM3\CoreSupport" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\board\LPCXpresso\LPC17XX_CMSIS_Drivers\Drivers\include" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\board\LPCXpresso\LPC17XX_CMSIS_Drivers\Core\CM3\DeviceSupport\NXP\LPC17xx" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\board\LPCXpresso\inc" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\api\inc" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\bsp\inc" -I"C:\Ezequiel\Tesis\localwork\test\QUADLSE_OBC\src\system" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


