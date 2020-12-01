################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SSD1306_library/ssd1306.c \
../SSD1306_library/ssd1306_fonts.c \
../SSD1306_library/ssd1306_tests.c 

OBJS += \
./SSD1306_library/ssd1306.o \
./SSD1306_library/ssd1306_fonts.o \
./SSD1306_library/ssd1306_tests.o 

C_DEPS += \
./SSD1306_library/ssd1306.d \
./SSD1306_library/ssd1306_fonts.d \
./SSD1306_library/ssd1306_tests.d 


# Each subdirectory must supply rules for building sources it contributes
SSD1306_library/ssd1306.o: ../SSD1306_library/ssd1306.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../SSD1306_library -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SSD1306_library/ssd1306.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SSD1306_library/ssd1306_fonts.o: ../SSD1306_library/ssd1306_fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../SSD1306_library -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SSD1306_library/ssd1306_fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SSD1306_library/ssd1306_tests.o: ../SSD1306_library/ssd1306_tests.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../SSD1306_library -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SSD1306_library/ssd1306_tests.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

