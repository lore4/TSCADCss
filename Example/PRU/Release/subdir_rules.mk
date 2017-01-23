################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: PRU Compiler'
	"C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/bin/clpru" -v3 -O2 --include_path="C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/include" --include_path="../../../../../include" --include_path="../../../../../include/am335x" --define="am3359" --define="pru0" --display_error_number --diag_wrap=off --diag_warning=225 --hardware_mac=on --endian=little --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


