TARGET = Ofes

CPPFILES  = $(wildcard ./src/*.cpp)
CPPFILES += $(wildcard ./src/**/*.cpp)
CPPFILES += $(wildcard ./src/**/**/*.cpp)

CFILES  = $(wildcard ./src/*.c)
CFILES += $(wildcard ./src/**/*.c)
CFILES += $(wildcard ./src/**/**/*.c)

OBJS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

INCDIR = ./include
CFLAGS = -O0 -g -G0 -Wall -DSQLITE_OS_OTHER=1 -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION=0 -no-crt0
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lstdc++ -lpsprtc

BUILD_PRX=1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = $(TARGET)

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak