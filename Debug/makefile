################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include WISL_WIDM/Framework/Lib/Src/subdir.mk
-include WISL_WIDM/Framework/Apps/msg_hdlr_task/subdir.mk
-include WISL_WIDM/Framework/Apps/imu_ctrl_task/subdir.mk
-include WISL_WIDM/Drivers/IOIF/Src/subdir.mk
-include WISL_WIDM/Drivers/IOIF/IOIF_I2C/Src/subdir.mk
-include WISL_WIDM/Drivers/BSP/ICM20608G/Src/subdir.mk
-include WISL_WIDM/Drivers/BSP/BumbleBee/subdir.mk
-include WISL_WIDM/Drivers/BSP/BM1422AGMV/Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := WIDM_A10_TEST
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
WIDM_A10_TEST.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
WIDM_A10_TEST.list \

OBJCOPY_BIN += \
WIDM_A10_TEST.bin \


# All Target
all: main-build

# Main-build Target
main-build: WIDM_A10_TEST.elf secondary-outputs

# Tool invocations
WIDM_A10_TEST.elf: $(OBJS) $(USER_OBJS) C:\Users\Seung-WonYun\STM32CubeIDE\workspace_1.8.0\WIDM_A10_TEST\STM32H750VBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "WIDM_A10_TEST.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Seung-WonYun\STM32CubeIDE\workspace_1.8.0\WIDM_A10_TEST\STM32H750VBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="WIDM_A10_TEST.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

WIDM_A10_TEST.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "WIDM_A10_TEST.list"
	@echo 'Finished building: $@'
	@echo ' '

WIDM_A10_TEST.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "WIDM_A10_TEST.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) WIDM_A10_TEST.bin WIDM_A10_TEST.elf WIDM_A10_TEST.list default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
