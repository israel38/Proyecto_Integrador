################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d.c \
../synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d_8bit_palette.c \
../synergy/ssp/src/framework/sf_el_gx/sf_el_gx.c 

OBJS += \
./synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d.o \
./synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d_8bit_palette.o \
./synergy/ssp/src/framework/sf_el_gx/sf_el_gx.o 

C_DEPS += \
./synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d.d \
./synergy/ssp/src/framework/sf_el_gx/gx_display_driver_synergy_dave2d_8bit_palette.d \
./synergy/ssp/src/framework/sf_el_gx/sf_el_gx.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/framework/sf_el_gx/%.o: ../synergy/ssp/src/framework/sf_el_gx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy_cfg\ssp_cfg\bsp" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy_cfg\ssp_cfg\driver" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\bsp" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\bsp\cmsis\Include" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\driver\api" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\driver\instances" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\src" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\src\synergy_gen" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy_cfg\ssp_cfg\framework\el" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\framework\el" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\src\framework\el\tx" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy_cfg\ssp_cfg\framework" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\framework\api" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\framework\instances" -I"D:\Documentos\DIPLOMADO\GIT\Proyecto_Integrador\Code\DSE_Mabe_Cidec_Project\synergy\ssp\inc\framework\tes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


