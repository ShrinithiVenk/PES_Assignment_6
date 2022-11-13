################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/BreakFastSerial_PES.c \
../source/CBFifo.c \
../source/CBFifo_test.c \
../source/Hexdump.c \
../source/UART.c \
../source/UI.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c 

C_DEPS += \
./source/BreakFastSerial_PES.d \
./source/CBFifo.d \
./source/CBFifo_test.d \
./source/Hexdump.d \
./source/UART.d \
./source/UI.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d 

OBJS += \
./source/BreakFastSerial_PES.o \
./source/CBFifo.o \
./source/CBFifo_test.o \
./source/Hexdump.o \
./source/UART.o \
./source/UI.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\board" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\source" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\drivers" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\CMSIS" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\utilities" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\BreakFastSerial_PES\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/BreakFastSerial_PES.d ./source/BreakFastSerial_PES.o ./source/CBFifo.d ./source/CBFifo.o ./source/CBFifo_test.d ./source/CBFifo_test.o ./source/Hexdump.d ./source/Hexdump.o ./source/UART.d ./source/UART.o ./source/UI.d ./source/UI.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sysclock.d ./source/sysclock.o

.PHONY: clean-source

