################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.c 

OBJS += \
./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.o 

C_DEPS += \
./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.d 


# Each subdirectory must supply rules for building sources it contributes
WISL_WIDM/Drivers/BSP/ICM20608G/Src/%.o WISL_WIDM/Drivers/BSP/ICM20608G/Src/%.su WISL_WIDM/Drivers/BSP/ICM20608G/Src/%.cyclo: ../WISL_WIDM/Drivers/BSP/ICM20608G/Src/%.c WISL_WIDM/Drivers/BSP/ICM20608G/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/BM1422AGMV" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/BM1422AGMV/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/BM1422AGMV/Src" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/BumbleBee" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/ICM20608G" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/ICM20608G/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/BSP/ICM20608G/Src" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/IOIF" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/IOIF/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Drivers/IOIF/Src" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Apps" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Apps/imu_ctrl_task" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Apps/msg_hdlr_task" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Lib" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Lib/Inc" -I"C:/Users/Seung-WonYun/STM32CubeIDE/workspace_1.13.0/WIDM_CM_TEST/WISL_WIDM/Framework/Lib/Src" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-WISL_WIDM-2f-Drivers-2f-BSP-2f-ICM20608G-2f-Src

clean-WISL_WIDM-2f-Drivers-2f-BSP-2f-ICM20608G-2f-Src:
	-$(RM) ./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.cyclo ./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.d ./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.o ./WISL_WIDM/Drivers/BSP/ICM20608G/Src/bsp_icm20608G.su

.PHONY: clean-WISL_WIDM-2f-Drivers-2f-BSP-2f-ICM20608G-2f-Src

