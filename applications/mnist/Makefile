ifndef MAKEFILE_TFLITE
define MAKEFILE_TFLITE
yes
endef

APP_ROOT := ..
CXXFILES += \
	main.cpp

INCPATH += \
	-I.

LD_FLAGS += \
	-lstdc++_nano

TARGET := mnist.mo

include ../tflite-mcu/Makefile.local
include $(APP_ROOT)/SDK/cplusplus/Makefile.local
include $(APP_ROOT)/SDK/Makefile.common

endif