################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"../AM335x_PRU.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"../../../../../lib/rpmsg_lib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
PRU_RPMsg_Echo_Interrupt1.out \

EXE_OUTPUTS__QUOTED += \
"PRU_RPMsg_Echo_Interrupt1.out" \

BIN_OUTPUTS += \
PRU_RPMsg_Echo_Interrupt1.hex \

BIN_OUTPUTS__QUOTED += \
"PRU_RPMsg_Echo_Interrupt1.hex" \


# All Target
all: PRU_RPMsg_Echo_Interrupt1.out

# Tool invocations
PRU_RPMsg_Echo_Interrupt1.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: PRU Linker'
	"C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/bin/clpru" -v3 -O2 --define="am3359" --define="pru0" --display_error_number --diag_wrap=off --diag_warning=225 --hardware_mac=on --endian=little -z -m"PRU_RPMsg_Echo_Interrupt1.map" --stack_size=0x100 --heap_size=0x100 -i"C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/lib" -i"C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/include" --reread_libs --define=PRU_CORE=1 --warn_sections --diag_wrap=off --display_error_number --xml_link_info="PRU_RPMsg_Echo_Interrupt1_linkInfo.xml" --rom_model -o "PRU_RPMsg_Echo_Interrupt1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

PRU_RPMsg_Echo_Interrupt1.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: PRU Hex Utility'
	"C:/ti/ccs/ccsv7/tools/compiler/ti-cgt-pru_2.1.4/bin/hexpru"  -o "PRU_RPMsg_Echo_Interrupt1.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" 
	-$(RM) "main.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

