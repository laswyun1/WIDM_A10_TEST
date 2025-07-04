################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WISL_WIDM/Drivers/IOIF/Src/ioif_fdcan.c \
../WISL_WIDM/Drivers/IOIF/Src/ioif_gpio.c \
../WISL_WIDM/Drivers/IOIF/Src/ioif_tim.c 

OBJS += \
./WISL_WIDM/Drivers/IOIF/Src/ioif_fdcan.o \
./WISL_WIDM/Drivers/IOIF/Src/ioif_gpio.o \
./WISL_WIDM/Drivers/IOIF/Src/ioif_tim.o 

C_DEPS += \
./WISL_WIDM/Drivers/IOIF/Src/ioif_fdcan.d \
./WISL_WIDM/Drivers/IOIF/Src/ioif_gpio.d \
./WISL_WIDM/Drivers/IOIF/Src/ioif_tim.d 


# Each subdirectory must supply rules for building sources it contributes
WISL_WIDM/Drivers/IOIF/Src/%.o: ../WISL_WIDM/Drivers/IOIF/Src/%.c WISL_WIDM/Drivers/IOIF/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Drivers/IOIF/IOIF_I2C/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/BM1422AGMV/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/ICM20608G/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/BumbleBee" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Drivers/IOIF/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Framework/Apps/imu_ctrl_task" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Framework/Apps/msg_hdlr_task" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.8.0/WIDM_A10_TEST/WISL_WIDM/Framework/Lib/Inc" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-WISL_WIDM-2f-Drivers-2f-IOIF-2f-Src

clean-WISL_WIDM-2f-Drivers-2f-IOIF-2f-Src:
	-$(RM) ./WISL_WIDM/Drivers/IOIF/Src/ioif_fdcan.d ./WISL_WIDM/Drivers/IOIF/Src/ioif_fdcan.o ./WISL_WIDM/Drivers/IOIF/Src/ioif_gpio.d ./WISL_WIDM/Drivers/IOIF/Src/ioif_gpio.o ./WISL_WIDM/Drivers/IOIF/Src/ioif_tim.d ./WISL_WIDM/Drivers/IOIF/Src/ioif_tim.o

.PHONY: clean-WISL_WIDM-2f-Drivers-2f-IOIF-2f-Src

