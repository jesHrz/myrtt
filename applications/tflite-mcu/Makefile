ifndef MAKEFILE_TFLITE
define MAKEFILE_TFLITE
yes
endef

APP_ROOT := ..
CFILES += main.c
LD_FLAGS += -lstdc++_nano
TARGET := tflite.mo

include ./Makefile.local
include $(APP_ROOT)/SDK/cplusplus/Makefile.local
include $(APP_ROOT)/SDK/Makefile.common

endif