################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include source/src/subdir.mk
-include freertos/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: critical\ blinky.axf

# Tool invocations
critical\ blinky.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/joyal/Documents/MCUXpresso_11.1.1_3241/workspace/lpc_chip_175x_6x/Debug" -L"/home/joyal/Documents/MCUXpresso_11.1.1_3241/workspace/lpc_board_nxp_lpcxpresso_1769/Debug" -Xlinker -Map="critical blinky.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "freertos_blinky_Debug.ld" -o "critical blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) "critical blinky.axf"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "critical blinky.axf"; # arm-none-eabi-objcopy -v -O binary "critical blinky.axf" "critical blinky.bin" ; # checksum -p LPC1769 -d "critical blinky.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
