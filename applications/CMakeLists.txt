cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(GCC_PATH "/opt/gcc-arm-none-eabi-10-2020-q4-major")
set(GCC_PREFIX "${GCC_PATH}/bin/arm-none-eabi-")
set(CMAKE_C_COMPILER "${GCC_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${GCC_PREFIX}g++")
set(CMAKE_ASM_COMPILER "${GCC_PREFIX}gcc")
set(STRIP "${GCC_PREFIX}strip")
set(SIZE "${GCC_PREFIX}size")

set(CMAKE_C_FLAGS "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=soft -ffunction-sections -fdata-sections -Wall -mlong-calls -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "-Woverloaded-virtual -fno-exceptions -fno-rtti  -Wl,--gc-sections,-z,max-page-size=0x4 -nostartfiles -static-libgcc -shared -e main")

enable_language(C ASM)

if (DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -gdwarf-2 -g")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Os")
endif()

if (DEFINED APP)
    set(APP_TARGET "${APP}.mo")
else()
    message(FATAL_ERROR "set -DAPP=<app-name>")
endif()

project(${APP})

include_directories(newlib/include)
add_definitions("-DRT_USING_NEWLIB" "-DSTM32F746xx" "-D__RTTHREAD__")

aux_source_directory(${APP} APP_SRCS)
aux_source_directory(newlib NEWLIB_SRCS)

add_executable("${APP_TARGET}" ${APP_SRCS} ${NEWLIB_SRCS})
target_link_libraries("${APP_TARGET}" -lc)

add_custom_target(strip
    COMMAND ${STRIP} -R .hash ${APP_TARGET}
    COMMAND ${SIZE} ${APP_TARGET}
)