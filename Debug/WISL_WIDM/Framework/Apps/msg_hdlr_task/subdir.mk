################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_data_object.c \
../WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_hdlr_task.c 

OBJS += \
./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_data_object.o \
./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_hdlr_task.o 

C_DEPS += \
./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_data_object.d \
./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_hdlr_task.d 


# Each subdirectory must supply rules for building sources it contributes
WISL_WIDM/Framework/Apps/msg_hdlr_task/%.o: ../WISL_WIDM/Framework/Apps/msg_hdlr_task/%.c WISL_WIDM/Framework/Apps/msg_hdlr_task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Drivers/IOIF/IOIF_I2C/Inc" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/BM1422AGMV/Inc" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/ICM20608G/Inc" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Drivers/BSP/BumbleBee" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Drivers/IOIF/Inc" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Framework/Apps/imu_ctrl_task" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Framework/Apps/msg_hdlr_task" -I"C:/Users/Seung-WonYun/Documents/GitHub/WIDM_A10_TEST/WISL_WIDM/Framework/Lib/Inc" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-WISL_WIDM-2f-Framework-2f-Apps-2f-msg_hdlr_task

clean-WISL_WIDM-2f-Framework-2f-Apps-2f-msg_hdlr_task:
	-$(RM) ./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_data_object.d ./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_data_object.o ./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_hdlr_task.d ./WISL_WIDM/Framework/Apps/msg_hdlr_task/msg_hdlr_task.o

.PHONY: clean-WISL_WIDM-2f-Framework-2f-Apps-2f-msg_hdlr_task

