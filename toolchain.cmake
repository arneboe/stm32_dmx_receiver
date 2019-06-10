SET(CMAKE_C_FLAGS   "-mthumb -fno-stack-protector -mcpu=cortex-m3 -mfloat-abi=soft -Wall -std=gnu99 -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-exceptions" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-mthumb -fno-stack-protector -mcpu=cortex-m3 -mfloat-abi=soft -Wall -std=c++17 -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-exceptions" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS "-mthumb -fno-stack-protector -mcpu=cortex-m3 -mfloat-abi=soft -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS "-u _printf_float -mcpu=cortex-m3 -fno-stack-protector -mthumb -mfloat-abi=soft -T${PROJECT_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld -lc -lm -lnosys -specs=nano.specs --specs=nosys.specs -Wl,--gc-sections" CACHE INTERNAL "executable linker flags")

#SET(CMAKE_MODULE_LINKER_FLAGS "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -specs=nano.specs --specs=nosys.specs -T${PROJECT_SOURCE_DIR}/STM32F746ZGTx_FLASH.ld -lc -lm -lnosys -Wl,--gc-sections" CACHE INTERNAL "module linker flags")
#SET(CMAKE_SHARED_LINKER_FLAGS "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -specs=nano.specs --specs=nosys.specs -T${PROJECT_SOURCE_DIR}/STM32F746ZGTx_FLASH.ld -lc -lm -lnosys -Wl,--gc-sections" CACHE INTERNAL "shared linker flags")



# Avoid known bug in linux giving:
#    arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm-eabi)

#Type of target generated for try_compile() calls using the source file signature
#This avoids running the linker and is intended for use with cross-compiling toolchains that cannot link without custom flags or linker scripts.
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
