################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lnk_msp430g2553.cmd 

CFG_SRCS += \
../main.cfg 

C_SRCS += \
../ADC_module.c \
../Communication.c \
../Interpreter.c \
../PWM_module.c \
../TASK_manager.c \
../fuzzy.c \
../main.c 

OBJS += \
./ADC_module.obj \
./Communication.obj \
./Interpreter.obj \
./PWM_module.obj \
./TASK_manager.obj \
./fuzzy.obj \
./main.obj 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

C_DEPS += \
./ADC_module.pp \
./Communication.pp \
./Interpreter.pp \
./PWM_module.pp \
./TASK_manager.pp \
./fuzzy.pp \
./main.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_SRCS__QUOTED += \
"configPkg\compiler.opt" \
"configPkg\linker.cmd" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"ADC_module.pp" \
"Communication.pp" \
"Interpreter.pp" \
"PWM_module.pp" \
"TASK_manager.pp" \
"fuzzy.pp" \
"main.pp" 

OBJS__QUOTED += \
"ADC_module.obj" \
"Communication.obj" \
"Interpreter.obj" \
"PWM_module.obj" \
"TASK_manager.obj" \
"fuzzy.obj" \
"main.obj" 

C_SRCS__QUOTED += \
"../ADC_module.c" \
"../Communication.c" \
"../Interpreter.c" \
"../PWM_module.c" \
"../TASK_manager.c" \
"../fuzzy.c" \
"../main.c" 

CFG_SRCS__QUOTED += \
"../main.cfg" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 


