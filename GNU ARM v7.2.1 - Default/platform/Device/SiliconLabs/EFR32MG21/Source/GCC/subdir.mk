################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.c 

OBJS += \
./platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.o 

C_DEPS += \
./platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.d 


# Each subdirectory must supply rules for building sources it contributes
platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.o: ../platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DHAL_CONFIG=1' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__StackLimit=0x20000000' '-DEFR32MG21A020F1024IM32=1' -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/CMSIS/Include" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emlib/src" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/app/bluetooth/common/util" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/common/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/nvm3/src" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/Device/SiliconLabs/EFR32MG21/Include" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/hardware/kit/common/drivers" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/hardware/kit/common/halconfig" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/protocol/bluetooth/ble_stack/inc/soc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/hardware/kit/common/bsp" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/service/sleeptimer/src" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/sleep/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/nvm3/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/protocol/bluetooth/ble_stack/inc/common" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/halconfig/inc/hal-config" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/service/sleeptimer/config" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/sleep/src" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/service/sleeptimer/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/emdrv/uartdrv/inc" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/Device/SiliconLabs/EFR32MG21/Source/GCC" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/Device/SiliconLabs/EFR32MG21/Source" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/hardware/kit/EFR32MG21_BRD4180A/config" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals" -I"/Users/clfilho/SimplicityStudio/Tigo/MG21Peripherals/platform/bootloader" -Og -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.d" -MT"platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


