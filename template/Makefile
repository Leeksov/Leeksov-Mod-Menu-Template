# export THEOS = /opt/theos # you can export your theos path for don't get some error on iOS & Linux
# THEOS_DEVICE_IP = 192.168.31.69 -p 2222 # you can install your package in your device in local network
# THEOS_PACKAGE_SCHEME = rootless # uncomment this for compile for rootless
ifeq ($(THEOS_PACKAGE_SCHEME),rootless)
THEOS_PACKAGE_DIR = rootless
else
THEOS_PACKAGE_DIR = rootful
endif
TARGET = iphone:clang:latest:10.0
ARCHS  = arm64
DEBUG  = 0
FINALPACKAGE = 1
_NO_SUBSTRATE = 1
INSTALL_TARGET_PROCESSES = @@BINARYNAME@@
_IGNORE_WARNINGS = 1
MENU_SRC = Menu.mm
TWEAK_NAME = @@PROJECTNAME@@
PROJ_COMMON_FRAMEWORKS = UIKit Foundation Security QuartzCore CoreGraphics CoreText AudioToolbox Security CoreGraphics AVFoundation Accelerate
KITTYMEMORY_SRC = $(wildcard KittyMemory/*.cpp)
SCLALERTVIEW_SRC =  $(wildcard SCLAlertView/*.m)
$(TWEAK_NAME)_CFLAGS = -fobjc-arc
$(TWEAK_NAME)_CCFLAGS = -std=c++17 -fno-rtti -fno-exceptions -DNDEBUG -DkITTYMEMORY_DEBUG
$(TWEAK_NAME)_FILES = Tweak.xm $(MENU_SRC) $(KITTYMEMORY_SRC) $(SCLALERTVIEW_SRC)
$(TWEAK_NAME)_OBJ_FILES = KittyMemory/Deps/Keystone/libs-ios/arm64/libkeystone.a
$(TWEAK_NAME)_LIBRARIES += substrate
$(TWEAK_NAME)_FRAMEWORKS = $(PROJ_COMMON_FRAMEWORKS)
include $(THEOS)/makefiles/common.mk
ifeq ($(IGNORE_WARNINGS),1)
  $(TWEAK_NAME)_CFLAGS += -w
  $(TWEAK_NAME)_CCFLAGS += -w
endif
ifeq ($(_NO_SUBSTRATE), 1)
$(TWEAK_NAME)_CCFLAGS += -DkNO_SUBSTRATE
endif
include $(THEOS_MAKE_PATH)/tweak.mk
after-install::
  install.exec "killall -9 @@BINARYNAME@@ || :"
